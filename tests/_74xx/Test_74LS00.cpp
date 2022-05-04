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
#include "_74LS00.h"

auto f_nand = [](bool a, bool b) { return !(a && b); };

TEST(_74xx, LS00)
{
    _74LS00 ic("74LS00");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up14(ic.p) );

    // Check gates
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[1],  ic.p[2],  ic.p[3],  f_nand) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[4],  ic.p[5],  ic.p[6],  f_nand) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[10], ic.p[9],  ic.p[8],  f_nand) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[13], ic.p[12], ic.p[11], f_nand) );

    ASSERT_TRUE( TestUtils::test_power_down14(ic.p, {&ic.p[3], &ic.p[6], &ic.p[8], &ic.p[11]} ) );
}
