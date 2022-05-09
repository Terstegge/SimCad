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
#include "_74LS245.h"
#include "BusRef.h"

TEST(_74xx, LS245)
{
    _74LS245 ic("74LS245");

    // Power up
    ic.p[10] = SUPPLY_GROUND;
    ic.p[20] = SUPPLY_VOLTAGE;

    Pin & AtoB = ic.p[ 1];
    Pin & nEN  = ic.p[19];

    BusRef A( {&ic.p[ 2],  &ic.p[ 3],  &ic.p[ 4],  &ic.p[ 5],
               &ic.p[ 6],  &ic.p[ 7],  &ic.p[ 8],  &ic.p[ 9]} );
    BusRef B( {&ic.p[18],  &ic.p[17],  &ic.p[16],  &ic.p[15],
               &ic.p[14],  &ic.p[13],  &ic.p[12],  &ic.p[11]} );

    // Test A to B
    nEN  = LOW;
    AtoB = HIGH;

    for (int i=0; i < 256; i++) {
    	A = i;
    	ASSERT_TRUE(B == i);
    }

    // Test B to A
    A.setDrvNC();
    AtoB = LOW;
    for (int i=0; i < 256; i++) {
    	B = i;
    	ASSERT_TRUE(A == i);
    }

    ic.p[20] = SUPPLY_GROUND;
}
