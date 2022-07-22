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
#include "_74LS253.h"
#include "BusRef.h"

TEST(_74xx, LS253)
{
    _74LS253 ic("74LS253");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    Pin & nEa = ic.p[1];
    Pin & nEb = ic.p[15];

    Pin & Za = ic.p[7];
    Pin & Zb = ic.p[9];

    BusRef Ia( {&ic.p[6],  &ic.p[5],  &ic.p[4],  &ic.p[3]} );
    BusRef Ib( {&ic.p[10], &ic.p[11], &ic.p[12], &ic.p[13]} );

    BusRef S( {&ic.p[14], &ic.p[2]} );


    for (int e=0; e < 4; ++e) {
        for (int s=0; s < 4; ++s) {
            for (int i=0; i < 16; ++i) {
                nEa = (bool)(e & 1);
                nEb = (bool)(e & 2);
                S  = s;
                Ia = i;
                Ib = i;

                if (nEa == LOW) {
                    ASSERT_TRUE( Za == (bool)(i & (1 << s)) );
                } else {
                    ASSERT_TRUE( Za.isNC() );
                }

                if (nEb == LOW) {
                    ASSERT_TRUE( Zb == (bool)(i & (1 << s)) );
                } else {
                    ASSERT_TRUE( Zb.isNC() );
                }

            }
        }
    }

    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &Za, &Zb }) );
}
