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
#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS541.h"
#include "BusRef.h"
#include "SimCadException.h"
#include <iostream>

using namespace std;

TEST(_74xx, LS541
) {
    _74LS541 ic("74LS541");

    try {
        // Power up
        ic.p[10] = SUPPLY_GROUND;
        ic.p[20] = SUPPLY_VOLTAGE;

        Pin &nEN1 = ic.p[1];
        Pin &nEN2 = ic.p[19];

        BusRef IN({&ic.p[2], &ic.p[3], &ic.p[4], &ic.p[5],
                   &ic.p[6], &ic.p[7], &ic.p[8], &ic.p[9]});
        BusRef OUT({&ic.p[18], &ic.p[17], &ic.p[16], &ic.p[15],
                    &ic.p[14], &ic.p[13], &ic.p[12], &ic.p[11]});

        // Test buffers
        nEN1 = LOW;
        nEN2 = LOW;

        for (int i = 0; i < 256; i++) {
            IN = i;
            ASSERT_TRUE(OUT == i);
        }

        // Test with not enabled
        IN.setDrvNC();

        nEN1 = HIGH;
        for (int i = 0; i < 256; i++) {
            IN = i;
            ASSERT_TRUE(OUT[0]->isNC());
            ASSERT_TRUE(OUT[1]->isNC());
            ASSERT_TRUE(OUT[2]->isNC());
            ASSERT_TRUE(OUT[3]->isNC());
            ASSERT_TRUE(OUT[4]->isNC());
            ASSERT_TRUE(OUT[5]->isNC());
            ASSERT_TRUE(OUT[6]->isNC());
            ASSERT_TRUE(OUT[7]->isNC());
        }

        // Test buffers
        nEN1 = LOW;

        for (int i = 0; i < 256; i++) {
            IN = i;
            ASSERT_TRUE(OUT == i);
        }

        // Switch off
        ic.p[20] = SUPPLY_GROUND;
    } catch (SimCadException &e) {
        cout << e << endl;
    }
}
