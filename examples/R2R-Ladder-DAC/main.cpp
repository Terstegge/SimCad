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

    for (int i=0; i < 16; ++i) {

        r2r.I1.press(i & 1);
        r2r.I2.press(i & 2);
        r2r.I3.press(i & 4);
        r2r.I4.press(i & 8);
        
        cout << r2r.Q << " " << r2r.OUT << endl;
    }

    } catch (short_circuit_exception & e) {
        cerr << e << endl;
    }
}

