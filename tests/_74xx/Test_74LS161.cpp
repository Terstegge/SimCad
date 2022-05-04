///////////////////////////////////////////////
//
//  This file is part of
//     ___  ____  __  __  ___    __    ____
//    / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//    \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//    (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation package for electronic circuits
//
//  (c) 2022  Andreas Terstegge
//
///////////////////////////////////////////////
//
#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS161.h"
#include "BusRef.h"

TEST(_74xx, LS161)
{
    _74LS161 ic("74LS161");

    Pin & nCLR  = ic.p[1];
    Pin &  CLK  = ic.p[2];
    Pin &  ENP  = ic.p[7];
    Pin & nLOAD = ic.p[9];
    Pin &  ENT  = ic.p[10];
    Pin &  RCO  = ic.p[15];

    BusRef DATA( {&ic.p[3],  &ic.p[4],  &ic.p[5],  &ic.p[6]} );
    BusRef    Q( {&ic.p[14], &ic.p[13], &ic.p[12], &ic.p[11]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    // Test Load and Clear
    nCLR  = HIGH;
    nLOAD = HIGH;
    CLK   = LOW;
    for (int i = 0; i < 16; ++i) {
        // Load value (synchronous)
        DATA  = i;
        nLOAD = LOW;
        CLK   = HIGH;
        ASSERT_TRUE( Q == i );
        nLOAD = HIGH;
        CLK   = LOW;
        ASSERT_TRUE( Q == i );
        // Clear output (asynchronous)
        nCLR = LOW;
        ASSERT_TRUE( Q == 0 );
        nCLR = HIGH;
        ASSERT_TRUE( Q == 0 );
    }

    // Test counting
    ENP = HIGH; // Enable counting
    ENT = HIGH;
    for (int i = 1; i < 256; ++i) {
        int val = i & 0x0f;
        CLK = HIGH; // Count
        ASSERT_TRUE( Q   == val );
        ASSERT_TRUE( RCO == ( (val==0x0f) ? HIGH : LOW ));
        CLK = LOW;
        ASSERT_TRUE( Q   == val );
        ASSERT_TRUE( RCO == ( (val==0x0f) ? HIGH : LOW ));
    }
    // The counter stopped at value 0x0f (15)

    // Test disabled counting
    ENT = LOW; // disable counting and RCO
    for (int i = 0; i < 256; ++i) {
        CLK = HIGH;
        CLK = LOW;
        ASSERT_TRUE( Q   == 0x0f );
        ASSERT_TRUE( RCO == LOW  );
    }

    // Power down
    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[14],  &ic.p[13],
                                                      &ic.p[12],  &ic.p[11], &RCO }) );
}
