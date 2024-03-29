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
#include "OP_AMP.h"
#include "PowerSupply.h"
#include "SimCadException.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace std::this_thread;

int main() {

    OP_AMP op("OP_AMP");

    try {
        // Power up
        cout << "Power up" << endl;
        PowerSupply::MIN_VOLTAGE = -5.0;
        PowerSupply::MAX_VOLTAGE =  5.0;
        op.minus_5V = -5.0;
        op.plus_5V  = +5.0;
        op.GND      =  0.0;

        cout << "Voltage follower:" << endl;
        for (double u=-2.0; u <= 2.1; u += 0.5) {
            op.Voltage_Follower_IN = u;
            cout << u << " V -> " << op.Voltage_Follower_OUT.U() << " V" << endl;
        }
        cout << endl;

        cout << "Non inverting amplifier (x 2):" << endl;
        for (double u=-2.0; u <= 2.1; u += 0.5) {
            op.Non_Inv_Ampl_IN = u;
            cout << u << " V -> " << op.Non_Inv_Ampl_OUT.U() << " V" << endl;
        }
        cout << endl;

        cout << "Inverting amplifier (x 2):" << endl;
        for (double u=-2.0; u <= 2.1; u += 0.5) {
            op.Inv_Ampl_IN = u;
            cout << u << " V -> " << op.Inv_Ampl_OUT.U() << " V" << endl;
        }
        cout << endl;


    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

