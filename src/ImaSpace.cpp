#include "ImaSpace.h"

bool operator<(VoxelID id1, VoxelID id2)
{
    if (id1.fID3D[2] < id2.fID3D[2])
    {
        return true;
    }
    if (id1.fID3D[2] > id2.fID3D[2])
    {
        return false;
    }

    if (id1.fID3D[1] < id2.fID3D[1])
    {
        return true;
    }
    if (id1.fID3D[1] < id2.fID3D[1])
    {
        return false;
    }

    if (id1.fID3D[0] < id2.fID3D[0])
    {
        return true;
    }
    if (id1.fID3D[0] < id2.fID3D[0])
    {
        return false;
    }
    return false;
}

// ImaSpace: define imaging space, where all objects are placed
ImaSpace *&ImaSpace::CurrentImaSpace()
{
    static ImaSpace *currentImaSpace = new ImaSpace();
    return currentImaSpace;
}

bool ImaSpace::SetGlobalNbins(UInt_t dim, UInt_t Nbins)
{
    if (fOccupied)
        return false;
    if (dim > 2)
        return false;
    fNbins[dim] = Nbins;
    return true;
}

bool ImaSpace::SetRange(UInt_t dim, double min, double max)
{
    if (fOccupied)
        return false;
    if (dim > 2)
        return false;
    fRange[dim].first = min;
    fRange[dim].second = max;
    return true;
}

VoxelID ImaSpace::JudgeID(double pos[3])
{
    if (!fOccupied || !fImaSpace)
    {
        return {0, 0, 0};
    }
    VoxelID temp(fImaSpace->GetXaxis()->FindBin(pos[0]), fImaSpace->GetYaxis()->FindBin(pos[1]), fImaSpace->GetZaxis()->FindBin(pos[2]));
    return temp;
}

void ImaSpace::Build()
{
    delete fImaSpace;

    fImaSpace = new TH3D("hImaSpace3D", "Imaging Space in 3D", fNbins[0], fRange[0].first, fRange[0].second, fNbins[1], fRange[1].first, fRange[1].second, fNbins[2], fRange[2].first, fRange[2].second);
    fOccupied = 1;
}

ImaSpace::~ImaSpace()
{
    // delete fImaSpace;
}

void ImaSpace::DrawObject(const ObjectPosition &obj)
{
    for (auto it = obj.objMap.begin(); it != obj.objMap.end(); it++)
    {
        fImaSpace->SetBinContent(it->first.fID3D[0], it->first.fID3D[1], it->first.fID3D[2], it->second);
    }
}

// ObjectPosition: Define where objects are placed
bool ObjectPosition::AddObject(VoxelID id, double lambda)
{
    auto flag = JudgeValid(id);
    if (!flag)
        return false;

    objMap.insert(std::pair<VoxelID, double>(id, lambda));
    return true;
}

bool ObjectPosition::JudgeValid(VoxelID id)
{
    if (id[0] >= gImaSpace->GetGlobalNbins(0) || id[1] >= gImaSpace->GetGlobalNbins(1) || id[2] >= gImaSpace->GetGlobalNbins(2))
    {
        return false;
    }
    else
        return true;
}
