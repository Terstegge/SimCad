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
#include "RS-flipflop.h"
#include "ShortCircuitEx.h"

#include <iostream>
using namespace std;

int main() {

    RS_flipflop ff("RS-FF");

    try {    
    ff.VCC = HIGH;
    ff.GND = LOW;

    cout << ff.A.getNet() << endl;
    cout << ff.B.getNet() << endl;
    
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    ff.nS1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;
    
    ff.nR1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    ff.nS1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;
    
    ff.nR1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    cout << ff.A.getNet() << endl;
    cout << ff.B.getNet() << endl;


    } catch (short_circuit_exception & e) {
        cerr << e << endl;
    }
    
}

