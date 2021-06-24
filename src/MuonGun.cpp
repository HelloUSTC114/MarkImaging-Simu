#include "MuonGun.h"

#include "TRandom.h"
#include "TMath.h"
#include <iostream>

MuonGun *&MuonGun::CurrentGun()
{
    static MuonGun *currentGun = new MuonGun();
    return currentGun;
}

void MuonGun::GenerateOne()
{
    double rnd1 = gRandom->Uniform();
    double theta = TMath::ACos(TMath::Power(1 - rnd1, 1.0 / 3));

    double rnd2 = gRandom->Uniform();
    double phi = rnd2 * TMath::Pi() * 2;

    double rnd3 = gRandom->Uniform();
    auto xRange = gImaSpace->GetRange(0);
    double x = xRange.first + (xRange.second - xRange.first) * rnd3;

    double rnd4 = gRandom->Uniform();
    auto yRange = gImaSpace->GetRange(1);
    double y = yRange.first + (yRange.second - yRange.first) * rnd4;

    auto zRange = gImaSpace->GetRange(2);
    double z = zRange.second;

    fLine.SetMagThetaPhi(1, TMath::Pi() - theta, phi);
    fPoint.SetXYZ(x, y, z);

    std::cout << theta << '\t' << phi << '\t' << x << '\t' << y << '\t' << z << std::endl;
}