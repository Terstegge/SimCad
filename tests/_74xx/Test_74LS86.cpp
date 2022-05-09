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
//  (c) Andreas Terstegge
//
///////////////////////////////////////////////
//
#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS86.h"

auto f_xor = [](bool a, bool b) { return a ^ b; };

TEST(_74xx, LS86)
{
    _74LS86 ic("74LS86");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up14(ic.p) );

    // Check gates
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[1],  ic.p[2],  ic.p[3],  f_xor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[4],  ic.p[5],  ic.p[6],  f_xor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[10], ic.p[9],  ic.p[8],  f_xor) );
    ASSERT_TRUE( TestUtils::test_gate2(ic.p[13], ic.p[12], ic.p[11], f_xor) );

    ASSERT_TRUE( TestUtils::test_power_down14(ic.p, {&ic.p[3], &ic.p[6], &ic.p[8], &ic.p[11]} ) );
}
