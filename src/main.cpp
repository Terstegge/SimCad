#include <iostream>
using namespace std;
#include <cassert>

#include "ShortCircuitEx.h"
#include "test.h"

int main()
{
    test t("test");

    t.GND    = 0;
    t.VCC    = 1;
    
    t.D      = 0;
    t.SRCLK  = 0;
    t.nSRCLR = 1;
    
    t.RCLK   = 0;
    t.nOE    = 1;

    // Load 0x1234
    int val = 0x1111;
    for (int i=15; i >= 0; --i) {
        t.D = (val & (1<<i)) != 0;
        t.SRCLK = 1;
        t.SRCLK = 0;
    }

    // Load output register
    t.RCLK = 1;
    t.RCLK = 0;
    
    // Enable output
    t.nOE  = 0;
    
    cout << hex << t.Q << " " << endl;
}
