#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS151.h"
#include "BusRef.h"

TEST(Series_74, LS151)
{
    _74LS151 ic("74LS151");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    Pin &  Z = ic.p[5];
    Pin & nZ = ic.p[6];
    Pin & nE = ic.p[7];

    BusRef S( {&ic.p[11], &ic.p[10], &ic.p[9]} );

    BusRef I( {&ic.p[4],  &ic.p[3],  &ic.p[2],  &ic.p[1],
               &ic.p[15], &ic.p[14], &ic.p[13], &ic.p[12]} );

    for (int e=0; e < 2; ++e) {
        for (int s=0; s < 8; ++s) {
            for (int i=0; i < 256; ++i) {
                nE = (bool)(e & 1);
                S  = s;
                I  = i;

                if (nE == LOW) {
                    ASSERT_TRUE(  Z ==  (bool)(i & (1 << s)) );
                    ASSERT_TRUE( nZ == !(bool)(i & (1 << s)) );
                } else {
                    ASSERT_TRUE(  Z == 0 );
                    ASSERT_TRUE( nZ == 1 );
                }
            }
        }
    }

    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &Z, &nZ }) );
}
