#include <iostream>
using namespace std;
#include <cassert>

#include "ShortCircuitEx.h"
#include "test.h"

int main()
{
    test t("test");

    try {
    
    t.GND    = 0;
    t.VCC    = 1;
    t.nCS1.on();

    cout << "Erasing FLASH" << endl;

    t.A = 0x5555;
    t.Q = 0xaa;
    t.nWE1.toggle();

    t.A = 0x2aaa;
    t.Q = 0x55;
    t.nWE1.toggle();

    t.A = 0x5555;
    t.Q = 0x80;
    t.nWE1.toggle();

    t.A = 0x5555;
    t.Q = 0xaa;
    t.nWE1.toggle();

    t.A = 0x2aaa;
    t.Q = 0x55;
    t.nWE1.toggle();

    t.A = 0x5000;
    t.Q = 0x10;
    t.nWE1.toggle();

    // Programming FLASH
    for (int i = 0; i < 524288; ++i) {
        t.A = 0x5555;
        t.Q = 0xaa;
        t.nWE1.toggle();

        t.A = 0x2aaa;
        t.Q = 0x55;
        t.nWE1.toggle();

        t.A = 0x5555;
        t.Q = 0xA0;
        t.nWE1.toggle();

        t.A = i;
        t.Q = i;
        t.nWE1.toggle();
    }
    
    } catch(short_circuit_exception & e) {
        cerr << e << endl;
    }
}

