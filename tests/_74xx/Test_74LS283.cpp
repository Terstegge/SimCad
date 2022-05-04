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
#include "_74LS283.h"
#include "BusRef.h"

TEST(_74xx, LS283)
{
    _74LS283 ic("74LS283");

    Pin & Cin  = ic.p[7];

    BusRef A( {&ic.p[5],  &ic.p[3],  &ic.p[14],  &ic.p[12]} );
    BusRef B( {&ic.p[6],  &ic.p[2],  &ic.p[15],  &ic.p[11]} );
    // Carry out is integrated in Q Bus for easier testing!
    BusRef Q( {&ic.p[4],  &ic.p[1],  &ic.p[13],  &ic.p[10], &ic.p[9]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    // Test adder without carry in
    Cin = LOW;
    for (int a=0; a < 16; a++) {
        for (int b=0; b < 16; b++) {
            A = a;
            B = b;
            ASSERT_TRUE( Q == (a+b));
        }
    }

    // Test adder with carry in
    Cin = HIGH;
    for (int a=0; a < 16; a++) {
        for (int b=0; b < 16; b++) {
            A = a;
            B = b;
            ASSERT_TRUE( Q == (a+b+1));
        }
    }

    // Power down
    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[4],  &ic.p[1],
                                                      &ic.p[13], &ic.p[10], &ic.p[9] }) );
}
