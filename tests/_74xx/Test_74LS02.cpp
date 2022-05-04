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
#include "_74LS02.h"

auto f_nor = [](bool a, bool b) { return !(a || b); };

TEST(_74xx, LS02)
{
    _74LS02 ic("74LS02");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up14(ic.p) );

    // Check gates
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[3],  ic.p[2],  ic.p[1],  f_nor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[6],  ic.p[5],  ic.p[4],  f_nor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[8],  ic.p[9],  ic.p[10], f_nor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[11], ic.p[12], ic.p[13], f_nor) );

    ASSERT_TRUE( TestUtils::test_power_down14(ic.p, {&ic.p[1], &ic.p[4], &ic.p[10], &ic.p[13]} ) );
}
