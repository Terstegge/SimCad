#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS153.h"
#include "BusRef.h"

TEST(Series_74, LS153)
{
    _74LS153 ic("74LS153");

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
                    ASSERT_TRUE( Za == 0 );
                }

                if (nEb == LOW) {
                    ASSERT_TRUE( Zb == (bool)(i & (1 << s)) );
                } else {
                    ASSERT_TRUE( Zb == 0 );
                }

            }
        }
    }

    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &Za, &Zb }) );
}
