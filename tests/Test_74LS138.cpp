#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS138.h"
#include "BusRef.h"

TEST(Series_74, LS138)
{
    _74LS138 ic("74LS138");

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    BusRef A( {&ic.p[1], &ic.p[2], &ic.p[3]} );

    BusRef E( {&ic.p[4], &ic.p[5], &ic.p[6]} );

    BusRef O( {&ic.p[15], &ic.p[14], &ic.p[13], &ic.p[12],
               &ic.p[11], &ic.p[10], &ic.p[9],  &ic.p[7]} );

    for (int e=0; e < 8; ++e) {
        for (int a=0; a < 8; ++a) {
            E = e;
            A = a;
            if (e == 4) {
                ASSERT_TRUE( O == ( (1 << a) ^ 0xff) );
            } else {
                ASSERT_TRUE( O == 0xff );
            }
        }
    }

    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[7],  &ic.p[9],  &ic.p[10], &ic.p[11],
                                                      &ic.p[12], &ic.p[13], &ic.p[14], &ic.p[15] }) );
}
