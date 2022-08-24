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
#include "plotRealTime.h"
#include <iostream>
#include <thread>

using namespace std;

int main() {

    TransistorBlinker tb("TransistorBlinker");

    plotRealTime prt(0.01, 300);
    prt.addEntry([&] () {return tb.R1.p[1].I();}, "R1 current", "blue");
    prt.addEntry([&] () {return tb.R4.p[1].I();}, "R4 current", "red" );
//    prt.addEntry([&] () {return tb.Q1.B.U();}, "Q1 Basis", "blue");
//    prt.addEntry([&] () {return tb.Q2.B.U();}, "Q2 Basis", "red" );


    try {
        PowerSupply ps(tb.VCC, tb.GND);
        ps.setVoltage(9.0);
        ps.switchOn();

        prt.start();


        for (int i=0; i < 100; ++i) {
            //cout << tb.D1.p[2].I() << " " << tb.D2.p[2].I() << "      ";
            cout << tb.D1.on() << " " << tb.D2.on() << endl;
            //cout << tb.Q2.B.U() << endl;
            this_thread::sleep_for(100ms);
        }

        ps.switchOff();
    } catch (SimCadException &e) {
        cerr << e << endl;
    }

    prt.stop();
}

