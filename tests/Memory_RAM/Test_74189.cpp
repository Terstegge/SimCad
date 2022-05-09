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
#include "_74189.h"
#include "BusRef.h"

TEST(Memory_RAM, 74189)
{
    _74189 ic("74189");

    Pin & nCS  = ic.p[2];
    Pin & nWE  = ic.p[3];

    BusRef ADDR( {&ic.p[1], &ic.p[15], &ic.p[14], &ic.p[13]} );
    BusRef DATA( {&ic.p[4], &ic.p[ 6], &ic.p[10], &ic.p[12]} );
    BusRef nOUT( {&ic.p[5], &ic.p[ 7], &ic.p[ 9], &ic.p[11]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    // Enable IC
    nCS = LOW;
    nWE = HIGH;
    // Write Data
    for(int a=0; a < 16; ++a) {
    	ADDR = a;
    	DATA = a;
    	nWE  = LOW;
    	nWE  = HIGH;
    }
    // Read back Data
    for(int a=0; a < 16; ++a) {
    	ADDR = a;
    	ASSERT_TRUE( (nOUT ^0xf) == a);
    }

    // Power down
    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[5],  &ic.p[7],
                                                      &ic.p[9],  &ic.p[11] }) );
}
