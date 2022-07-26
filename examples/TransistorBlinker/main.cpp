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
#include "TransistorBlinker.h"
#include "PowerSupply.h"
#include "SimCadException.h"
#include <iostream>
#include <thread>

using namespace std;

int main() {

    TransistorBlinker tb("Diodes");

    try {
        PowerSupply ps(tb.VCC, tb.GND);
        ps.setVoltage(9.0);
        //PowerSupply::MIN_VOLTAGE = -9.0;
        ps.switchOn();


        cout << tb.OUT << endl;

        for (int i=0; i < 1000; ++i) {
            //cout << tb.D1.p[2].I() << " " << tb.D2.p[2].I() << "      ";
            cout << tb.D1.on() << " " << tb.D2.on() << endl;
            this_thread::sleep_for(100ms);
        }

        ps.switchOff();
    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

