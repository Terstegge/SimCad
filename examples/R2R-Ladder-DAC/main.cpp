/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
#include "R2R_Ladder_DAC.h"
#include "SimCadException.h"
#include "PowerSupply.h"

#include <iostream>
using namespace std;

int main() {

    R2R_Ladder_DAC r2r("R2R");

    try {
        // Power up
        cout << "**** Power up..." << endl;
        PowerSupply ps(r2r.VCC, r2r.GND);
        ps.setVoltage(5.0);
        ps.switchOn();

        // Reset 74LS161
        cout << "**** Reset..." << endl;
        r2r.SW_CLR1.toggle();

        // Iterate over all 16 voltage steps
        for (int i=0; i < 16; ++i) {
            cout << r2r.Q << "  " << r2r.OUT << endl;
            r2r.SW_CLK1.toggle();
        }
        cout << r2r.Q << "  " << r2r.OUT << endl;

        // Set a specific value
        cout << "**** Set value to 13..." << endl;
        r2r.IN = 13;
        r2r.SW_LOAD1.press(true);
        r2r.SW_CLK1.toggle();
        r2r.SW_LOAD1.press(false);
        cout << r2r.Q << "  " << r2r.OUT << endl;

        // Power down
        cout << "**** Power down..." << endl;
        ps.switchOff();

    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

