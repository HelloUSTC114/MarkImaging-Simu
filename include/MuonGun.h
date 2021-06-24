#ifndef MUONGUN_H
#define MUONGUN_H

#include "ImaSpace.h"
#include "TVector3.h"

class MuonGun
{
public:
    void GenerateOne();
    TVector3 GetDirectrion() { return fLine; };
    TVector3 GetPosition() { return fPoint; };

    static MuonGun *&CurrentGun();

private:
    TVector3 fLine, fPoint;
};

#define gGun (MuonGun::CurrentGun())

#endif