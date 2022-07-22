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
#include "_74LS165.h"
#include "BusRef.h"

TEST(_74xx, LS165)
{
    _74LS165 ic("74LS165");

    Pin & nLD  = ic.p[1];
    Pin & CLK  = ic.p[2];
    Pin & nQ   = ic.p[7];
    Pin & Q    = ic.p[9];
    Pin & SER  = ic.p[10];
    Pin & INH  = ic.p[15];

    BusRef DATA( {&ic.p[6],  &ic.p[5],  &ic.p[4],  &ic.p[3],
                  &ic.p[14], &ic.p[13], &ic.p[12], &ic.p[11]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    // Test Load and Shift
    nLD = HIGH;
    CLK = LOW;
    SER = LOW;
    INH = LOW;
    for (int i = 0; i < 256; ++i) {
        // Load value
        DATA = i;
        nLD = LOW;
        nLD = HIGH;
        // Shift value out
        int result = 0;
        for (int s = 0; s < 8; ++s) {
            result |= (Q ? 256 : 0);
            result >>= 1;
            CLK = HIGH;
            CLK = LOW;
        }
        ASSERT_TRUE( i == result );
    }
    // Power down
    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &Q, &nQ }) );
}
