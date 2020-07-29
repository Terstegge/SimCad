#include <iostream>
using namespace std;
#include <cassert>

#include "ShortCircuitEx.h"
#include "test.h"

int main()
{
    test t("test");

    try {

    t.GND   = 0;
    t.VCC   = 1;
    
    t.CLK   = 0;
    t.D     = 0;
    t.EP    = 1;
    t.ET    = 1;
    t.nCLR  = 1;
    t.nLOAD = 1;    

    // Load 10
    t.D     = 01234;
    t.nLOAD = 0;
    t.CLK   = 1;
    t.CLK   = 0;
    t.nLOAD = 1;
    cout << t.Q << " " << t.RCO << endl;

    // CLR
    t.nCLR  = 0;
    t.nCLR  = 1;
    cout << t.Q << " " << t.RCO << endl;

    for (int i = 0; i < 4096; ++i) {
        // Count
        t.CLK   = 1;
        cout << t.Q << " " << t.RCO << endl;
        t.CLK   = 0;
    }

    cout << t.U1.U6 << endl;

    } catch(short_circuit_exception & e) {
        cerr << e << endl;
    }
}
