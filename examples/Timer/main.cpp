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
#include "Timer.h"
#include "PowerSupply.h"
#include "SimCadException.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace std::this_thread;

int main() {

    Timer t("Timer");

    try {
        // Power up
        cout << "Power up" << endl;
        PowerSupply ps(t.VCC, t.GND);
        ps.setVoltage(5.0);
        ps.switchOn();

        // Put NE555 and 74LS161 in reset mode
        t.nRESET = 0.0;

        this_thread::sleep_for(1s);
        cout << "Start Timer" << endl;
        t.nRESET = 5.0;

        for(int i = 0; i < 10000; ++i) {
            cout << "  LED: " << t.D1.on() << " " << t.COUNT << "  \r";
            cout.flush();
            this_thread::sleep_for(10ms);
        }

        // Power down
        cout << "Power down" << endl;
        ps.switchOff();

    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

