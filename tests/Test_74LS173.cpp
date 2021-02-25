#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_74LS173.h"
#include "BusRef.h"

TEST(Series_74, LS173)
{
    _74LS173 ic("74LS173");

    Pin & nM  = ic.p[1];
    Pin & nN  = ic.p[2];
    Pin & CLK = ic.p[7];
    Pin & nG1 = ic.p[9];
    Pin & nG2 = ic.p[10];
    Pin & CLR = ic.p[15];

    BusRef DATA( {&ic.p[14], &ic.p[13], &ic.p[12], &ic.p[11]} );
    BusRef Q   ( {&ic.p[3],  &ic.p[4],  &ic.p[5],  &ic.p[6]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up16(ic.p) );

    // Test Load and Clear
    nM  = LOW; // Output enable
    nN  = LOW;
    nG1 = LOW; // Enable load
    nG2 = LOW;
    CLR = LOW;
    CLK = LOW;
    for (int i=0; i < 16; ++i) {
        // Test load
        DATA = i;
        CLK = HIGH;
        ASSERT_TRUE( Q == i );
        CLK = LOW;
        ASSERT_TRUE( Q == i );
        // Test three state output
        nM = HIGH;
        ASSERT_TRUE( ic.p[3].isNC() );
        ASSERT_TRUE( ic.p[4].isNC() );
        ASSERT_TRUE( ic.p[5].isNC() );
        ASSERT_TRUE( ic.p[6].isNC() );
        nM = LOW;
        // Test clear
        CLR = HIGH;
        ASSERT_TRUE( Q == 0 );
        CLR = LOW;
        // Test disable load
        nG1 = HIGH;
        CLK = HIGH;
        CLK = LOW;
        ASSERT_TRUE( Q == 0 );
        nG1 = LOW;
    }

    // Power down
    ASSERT_TRUE( TestUtils::test_power_down16(ic.p, { &ic.p[3],  &ic.p[4],
                                                      &ic.p[5],  &ic.p[6] }) );
}
