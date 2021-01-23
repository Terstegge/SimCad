#include "R2R-Ladder-DAC.h"
#include "_74LS08.h"
#include "ShortCircuitEx.h"
#include "R.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {
        // Power up
        cout << "********** Setting VCC" << endl;
        r2r.VCC = SUPPLY_VOLTAGE;
        cout << "********** Setting GND" << endl;
        r2r.GND = SUPPLY_GROUND;

        cout << "********** Result" << endl;
        cout << r2r.OUT << endl;
        cout << r2r.AAA << endl;
        cout << r2r.VCC << endl;
        cout << r2r.GND << endl;
        cout << r2r.R1.p[2] << endl;
        cout << r2r.R1.p[1] << endl;
        cout << r2r.R2.p[2] << endl;

//        cout << r2r.VCC.getNetPtr()  << endl;
//        cout << r2r.GND.getNetPtr()  << endl;

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

