#include <iostream>
using namespace std;
#include <cassert>

#include "ShortCircuitEx.h"
#include "test.h"

int main()
{
    try {
    
    test t("test");

    t.GND    = 0;
    t.VCC    = 1;
    
    t.D      = 0;
//    t.SRCLK  = 0;
//    t.nSRCLR = 1;
    
    t.RCLK   = 0;
    t.nOE    = 1;


    for (int val=0; val < 0x1000; ++val) {

        cout << hex << val << "\r";
        
        // Load value
        for (int i=15; i >= 0; --i) {
            t.D = (val & (1<<i)) != 0;
            t.CLK1.PRESS();
            t.CLK1.RELEASE();
        }

        // Load output register
        t.RCLK = 1;
        t.RCLK = 0;

        t.nOE = 0;
        assert(val == t.Q);
        t.nOE = 1;

        t.CLR1.PRESS();
        t.CLR1.RELEASE();

        // Load output register
        t.RCLK = 1;
        t.RCLK = 0;

        t.nOE = 0;
        assert(0 == t.Q);
        t.nOE = 1;

    }

    } catch(short_circuit_exception & e) {
        cerr << e << endl;
    }
}

