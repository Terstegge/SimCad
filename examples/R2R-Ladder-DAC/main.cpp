#include "R2R-Ladder-DAC.h"
#include "ShortCircuitEx.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {    

    // Power up
    r2r.VCC  = HIGH;
    r2r.GND  = LOW;

    for (int i=0; i < 20; ++i) {

        if (i & 1) r2r.I1.press(); else r2r.I1.release();
        if (i & 2) r2r.I2.press(); else r2r.I2.release();
        if (i & 4) r2r.I3.press(); else r2r.I3.release();
        if (i & 8) r2r.I4.press(); else r2r.I4.release();
        
        cout << r2r.Q << " " << r2r.OUT << endl;
    }

    cout << endl << "EVS of OUT Pin: " << R::getEVS(&r2r.OUT) << endl;

    } catch (short_circuit_exception & e) {
        cerr << e << endl;
    }
}

