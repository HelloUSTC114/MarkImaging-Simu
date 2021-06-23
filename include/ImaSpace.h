#ifndef IMASPACE_H
#define IMASPACE_H

#include <map>
#include <algorithm>
#include "TMath.h"
#include "TH3D.h"
class ObjectPosition;

struct VoxelID
{
    VoxelID(UInt_t x, UInt_t y, UInt_t z) { fID3D[0] = x, fID3D[1] = y, fID3D[2] = z; }
    UInt_t operator[](UInt_t i) { return fID3D[i]; }
    UInt_t fID3D[3]; // Give 3D ID
};
bool operator<(VoxelID id1, VoxelID id2);   // Compare two vodel ids. Larger if z value is bigger.

class ImaSpace
{
public:
    bool SetGlobalNbins(UInt_t dim, UInt_t Nbins);
    UInt_t GetGlobalNbins(UInt_t dim) { return fNbins[dim]; }
    bool SetRange(UInt_t dim, double min, double max);

    void Build(); // Build imaging space
    static ImaSpace *&CurrentImaSpace();

    VoxelID JudgeID(double pos[3]);      // Judge voxel id from 3D position
    void DrawObject(const ObjectPosition &obj); // Draw Object inside Imaging Space
    TH3D *GetHist() const { return fImaSpace; }

    ~ImaSpace();

private:
    UInt_t fNbins[3] = {0, 0, 0};
    std::pair<double, double> fRange[3] = {{0, 0}, {0, 0}, {0, 0}}; // Unit: mm

    bool fOccupied = 0;

    TH3D *fImaSpace = NULL;
};

#define gImaSpace (ImaSpace::CurrentImaSpace())

class ObjectPosition
{
    friend class ImaSpace;

public:
    bool AddObject(VoxelID id, double lambda); // Can only add material one voxel by one

    bool JudgeValid(VoxelID id);

private:
    std::map<VoxelID, double> objMap; // Map voxel id to lambda in particle emission poisson distribution
};

#endif