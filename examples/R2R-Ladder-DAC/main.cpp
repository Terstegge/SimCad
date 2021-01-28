#include "R2R-Ladder-DAC.h"
#include "_74LS08.h"
#include "ShortCircuitEx.h"
#include "R.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {

        r2r.nCLR = SUPPLY_GROUND;
        r2r.CLK  = SUPPLY_GROUND;

        // Power up
        cout << "**** Power up..." << endl;
        r2r.GND = SUPPLY_GROUND;
        r2r.VCC = SUPPLY_VOLTAGE;

        r2r.nCLR = SUPPLY_VOLTAGE;

        cout << r2r.Q << "  " << r2r.OUT << endl;
        for (int i=0; i < 16; ++i) {
            r2r.CLK = SUPPLY_VOLTAGE;
            r2r.CLK = SUPPLY_GROUND;
            cout << r2r.Q << "  " << r2r.OUT << endl;
        }

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

