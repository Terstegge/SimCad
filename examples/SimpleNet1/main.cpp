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
// See https://dk4ek.de/elektronik/netzw_l.pdf
//
#include "SimpleNet1.h"
#include "SimCadException.h"

#include <iostream>
using namespace std;

int main() {

    SimpleNet1 sn1("SN1");

    try {
        // Power up
        sn1.GND = 0.0;
        sn1.V1.update();
        sn1.I1.update();
        //sn1.GND.getNet()->update();

        cout << "Pin status:" << endl;
        cout << sn1.V1.p[1] << endl;
        cout << sn1.V1.p[2] << endl;
        cout << sn1.I1.p[1] << endl;
        cout << sn1.I1.p[2] << endl;
        cout << sn1.R1.p[1] << endl;
        cout << sn1.R1.p[2] << endl;
        cout << sn1.R2.p[1] << endl;
        cout << sn1.R2.p[2] << endl;
        cout << sn1.R3.p[1] << endl;
        cout << sn1.R3.p[2] << endl;
        cout << sn1.R4.p[1] << endl;
        cout << sn1.R4.p[2] << endl;
        cout << sn1.R5.p[1] << endl;
        cout << sn1.R5.p[2] << endl;
        cout << sn1.GND.getNet() << endl;
        cout << endl << endl;

        cout << "Pin drive status:" << endl;
        cout << drive << sn1.V1.p[1] << endl;
        cout << drive << sn1.V1.p[2] << endl;
        cout << drive << sn1.I1.p[1] << endl;
        cout << drive << sn1.I1.p[2] << endl;
        cout << drive << sn1.R1.p[1] << endl;
        cout << drive << sn1.R1.p[2] << endl;
        cout << drive << sn1.R2.p[1] << endl;
        cout << drive << sn1.R2.p[2] << endl;
        cout << drive << sn1.R3.p[1] << endl;
        cout << drive << sn1.R3.p[2] << endl;
        cout << drive << sn1.R4.p[1] << endl;
        cout << drive << sn1.R4.p[2] << endl;
        cout << drive << sn1.R5.p[1] << endl;
        cout << drive << sn1.R5.p[2] << endl;
        cout << drive << sn1.GND.getNet() << endl;

    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

