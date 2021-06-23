#include <map>
#include <algorithm>
#include "TMath.h"
#include "TH3D.h"

// Judge linear number of the voxel
struct VoxelID
{
    UInt_t fID3D[3]; // Give 3D ID
};

class ImaSpace
{
public:
    UInt_t SetGlobalXMax(UInt_t xmax) { fXMax = xmax; }
    UInt_t SetGlobalYMax(UInt_t ymax) { fYMax = ymax; }
    UInt_t SetGlobalZMax(UInt_t zmax) { fZMax = zmax; }

    UInt_t GetGlobalXMax() { return fXMax; }
    UInt_t GetGlobalYMax() { return fYMax; }
    UInt_t GetGlobalZMax() { return fZMax; }

    static ImaSpace *&CurrentImaSpace()
    {
        static ImaSpace *currentImaSpace = new ImaSpace();
        return currentImaSpace;
    }

private:
    UInt_t fXMax = 0, fYMax = 0, fZMax = 0;
};

#define gImaSpace (ImaSpace::CurrentImaSpace())

class ObjectPosition
{
public:
    bool AddObject(VoxelID id, double lambda); // Can only add material one voxel by one

    TH3D *GetHistogram();
private:
    std::map<VoxelID, double> objMap; // Map voxel id to lambda in particle emission poisson distribution
};


