#include "R2R-Ladder-DAC.h"
#include "ShortCircuitEx.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {
        // Power up
        cout << "**** Power up..." << endl;
        r2r.GND = SUPPLY_GROUND;
        r2r.VCC = SUPPLY_VOLTAGE;

        // Reset 74LS161
        r2r.SW_CLR1.setOn(true);
        r2r.SW_CLR1.setOn(false);

        // Iterate over all 16 voltage steps
        cout << r2r.Q << "  " << r2r.OUT << endl;
        for (int i=0; i < 16; ++i) {
            r2r.SW_CLK1.toggle();
            cout << r2r.Q << "  " << r2r.OUT << endl;
        }
    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

