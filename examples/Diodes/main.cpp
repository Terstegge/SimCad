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
#include "Diodes.h"
#include "ShortCircuitEx.h"

#include <iostream>
using namespace std;

int main() {

    Diodes d("Diodes");

    try {
        // Power up
        cout << "**** Power up..." << endl;
        d.GND = SUPPLY_GROUND;
        d.VCC = SUPPLY_VOLTAGE;

        cout << d.TP_A << endl;
        cout << d.TP_B << endl;
        cout << d.TP_C << endl;

        cout << d.R1.p[1].I() << endl;
        cout << d.R1.p[2].I() << endl;

        cout << d.D1.p[2].I() << endl;
        cout << d.D1.p[1].I() << endl;

        cout << d.R2.p[1].I() << endl;
        cout << d.R2.p[2].I() << endl;

        cout << d.D2.p[2].I() << endl;
        cout << d.D2.p[1].I() << endl;

        cout << d.VCC.I() << endl;
        cout << d.GND.I() << endl;

        cout << d.D3.on() << endl;
        cout << d.D3.C << endl;
        d.SW1.setOn(true);
        cout << d.D3.on() << endl;
        cout << d.D3.C << endl;

//        d.B.getNet()->update();
//
//        for (double U=0.0; U < 5.0; U+= 0.1) {
//            cout << "U: " << U << " " << d.A.getNet()->Isum(U) << endl;
//        }

        d.C1.start();

//        for (int i=0; i < 10000000; ++i) {
//        	cout << d.Uc << "     " << "\r";
//        }
        d.Vplus  = 2.0;
        d.Vminus = -5.0;
        cout << d.Ur << endl;

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

