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
#include "_74LS157.h"
#include "BusRef.h"

TEST(_74xx, LS157)
{
    _74LS157 ic("74LS157");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    Pin & nE = ic.p[15];
    Pin &  S = ic.p[1];

    BusRef Z( {&ic.p[4],  &ic.p[7],  &ic.p[12],  &ic.p[9]} );

    BusRef I0( {&ic.p[2],  &ic.p[5],  &ic.p[14],  &ic.p[11]} );
    BusRef I1( {&ic.p[3],  &ic.p[6],  &ic.p[13],  &ic.p[10]} );

    for (int e=0; e < 2; ++e) {
        for (int s=0; s < 2; ++s) {
            for (int i0=0; i0 < 16; ++i0) {
                for (int i1=0; i1 < 16; ++i1) {
                    nE = (bool)(e & 1);
                    S  = (bool)(s & 1);
                    I0 = i0;
                    I1 = i1;

                    if (nE == LOW) {
                        ASSERT_TRUE( Z == ((s & 1) ? i1 : i0) );
                    } else {
                        ASSERT_TRUE( Z == 0);
                    }
                }
            }
        }
    }

    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[4],  &ic.p[7],  &ic.p[12],  &ic.p[9] }) );
}
