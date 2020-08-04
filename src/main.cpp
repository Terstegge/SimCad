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

    cout << "Writing 32KB RAM" << endl;
    for (int i = 0; i < 32768; ++i) {
        // Set and write data
        t.A   = i;
        t.Q   = i;
        t.nWE1.toggle();
    }

    t.Q = NC;

    cout << "Reading 32KB RAM" << endl;
    for (int i = 0; i < 32768; ++i) {
        // Read data
        t.A   = i;
        t.nOE1.press();
        assert(t.Q == (i % 256));
        assert(t.U1._mem[i] == (i % 256));
        t.nOE1.release();
        assert(t.Q == 255);
    }

    } catch(short_circuit_exception & e) {
        cerr << e << endl;
    }
}

