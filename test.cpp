#include "ImaSpace.h"
#include <iostream>
#include <string>

#include "TCanvas.h"

int main()
{
    using namespace std;
    cout << "test" << endl;

    gImaSpace->SetGlobalNbins(0, 20);
    gImaSpace->SetGlobalNbins(1, 20);
    gImaSpace->SetGlobalNbins(2, 20);

    gImaSpace->SetRange(0, -10, 10);
    gImaSpace->SetRange(1, -10, 10);
    gImaSpace->SetRange(2, -10, 10);

    gImaSpace->Build();

    // cout << gImaSpace->GetHist() << endl;

    gObjPos->AddObject({9, 10, 10}, 20);
    gObjPos->AddObject({10, 10, 10}, 20);
    gObjPos->AddObject({11, 10, 10}, 20);
    gObjPos->AddObject({10, 9, 10}, 20);
    gObjPos->AddObject({10, 11, 10}, 20);
    gObjPos->AddObject({10, 10, 9}, 20);
    gObjPos->AddObject({10, 10, 11}, 20);
    gObjPos->AddObject({1, 1, 1}, 20);

    gImaSpace->DrawObject(gObjPos);

    auto c = new TCanvas("c", "c", 1);
    gImaSpace->GetHist()->Draw("GLOBOX");
    c->SaveAs("test.pdf");

    return 0;
}