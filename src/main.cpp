#include <iostream>
using namespace std;
#include <cassert>

#include "test.h"

int main()
{
    test t("test");

    t.GND = 0;
    t.VCC = 1;

    t.E1n = 0;
    t.E2n = 0;
    t.E3  = 1;
    
    for (int i=0; i < 8; ++i) {
        t.A = i;
        cout << t.O << endl;
    }

}

