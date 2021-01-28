#include "R2R-Ladder-DAC.h"
#include "_74LS08.h"
#include "ShortCircuitEx.h"
#include "R.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {
//        // Power up
        cout << "********** Setting GND" << endl;
        r2r.GND = SUPPLY_GROUND;
//        cout << "********** Setting VCC" << endl;
//        r2r.VCC = 15.0;
//        cout << "********** Setting VCCQ" << endl;
//        r2r.VCCQ = 5.6;

//
//        cout << "********** Result" << endl;
//        cout << r2r.OUT << endl;

//  //      cout << r2r.VCC << endl;
        cout << r2r.GND.getNetPtr() << endl;

//        cout << r2r.V1.p[2] << endl;
//        cout << r2r.V1.p[1] << endl;
//        cout << r2r.R1.p[1] << endl;
//        cout << r2r.R1.p[2] << endl;
//        cout << r2r.R2.p[1] << endl;
//        cout << r2r.R2.p[2] << endl;
//        cout << r2r.R3.p[1] << endl;
////        cout << r2r.R3.p[2] << endl;
//        cout << r2r.R4.p[1] << endl;
//        cout << r2r.R4.p[2] << endl;
//        cout << r2r.R5.p[1] << endl;
//        cout << r2r.R5.p[2] << endl;

//        cout << "Set I" << endl;
//
//        r2r.I1.setI(0.005);
//
//        cout << "Update GND" << endl;
//        r2r.GND.getNetPtr()->update(true);
//        cout << "CONTINUE!!" << endl;

//        cout << "Update I1.p[1]" << endl;
//        r2r.I1.p[1].getNetPtr()->update(true);


        cout << r2r.V1.p[1] << endl;
        cout << r2r.V1.p[2] << endl;
        cout << r2r.R1.p[1] << endl;
        cout << r2r.R1.p[2] << endl;
        cout << r2r.R2.p[1] << endl;
        cout << r2r.R2.p[2] << endl;
        cout << r2r.R3.p[1] << endl;
        cout << r2r.R3.p[2] << endl;
        cout << r2r.R4.p[1] << endl;
        cout << r2r.R4.p[2] << endl;
        cout << r2r.R5.p[1] << endl;
        cout << r2r.R5.p[2] << endl;

        cout << endl << endl;

        cout << drive << r2r.V1.p[1] << endl;
        cout << drive << r2r.V1.p[2] << endl;
        cout << drive << r2r.R1.p[1] << endl;
        cout << drive << r2r.R1.p[2] << endl;
        cout << drive << r2r.R2.p[1] << endl;
        cout << drive << r2r.R2.p[2] << endl;
        cout << drive << r2r.R3.p[1] << endl;
        cout << drive << r2r.R3.p[2] << endl;
        cout << drive << r2r.R4.p[1] << endl;
        cout << drive << r2r.R4.p[2] << endl;
        cout << drive << r2r.R5.p[1] << endl;
        cout << drive << r2r.R5.p[2] << endl;

        cout << r2r.R5.p[1].getNetPtr() << endl;
        cout << r2r.R5.p[2].getNetPtr() << endl;
        cout << r2r.R3.p[2].getNetPtr() << endl;
        cout << r2r.GND.getNetPtr() << endl;



        //
//        r2r.I1.p[1].getNetPtr()->update(true);
//
//        cout << "Hallo1" << endl;
//
//        cout << r2r.V1.p[2] << endl;
//        cout << r2r.V1.p[1] << endl;
//        cout << r2r.R1.p[1] << endl;
//        cout << r2r.R1.p[2] << endl;
//        cout << r2r.R2.p[1] << endl;
//        cout << r2r.R2.p[2] << endl;
//        cout << r2r.R3.p[1] << endl;
//        cout << r2r.R3.p[2] << endl;
//        cout << r2r.R4.p[1] << endl;
//        cout << r2r.R4.p[2] << endl;
//        cout << r2r.R5.p[1] << endl;
//        cout << r2r.R5.p[2] << endl;


        //
////        cout << r2r.VCC.getNetPtr()  << endl;
////        cout << r2r.GND.getNetPtr()  << endl;

//        cout << r2r.I1.p[1].getNetPtr() << endl;
//        cout << r2r.I1.p[2].getNetPtr() << endl;

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

