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
#include "D_LATCH.h"

TEST(base_parts, D_LATCH)
{
    D_LATCH ff("D_LATCH");

    Pin & D   = ff.p[1];
    Pin & CLK = ff.p[2];
    Pin & nS  = ff.p[3];
    Pin & nR  = ff.p[4];
    Pin &  Q  = ff.p[5];
    Pin & nQ  = ff.p[6];

    // Power up
    ff.p[0] = SUPPLY_GROUND;
    ff.p[7] = SUPPLY_VOLTAGE;

    // Test Set/Reset
    nS = HIGH;
    nR = HIGH;
    for (int i = 0; i < 10; ++i) {
        nS = LOW;   // Set
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        nS = HIGH;
        nR = LOW;   // Reset
        ASSERT_TRUE(  Q == LOW  );
        ASSERT_TRUE( nQ == HIGH );
        nR = HIGH;
    }
    // Test special case nS=nR=LOW
    nS = LOW;
    nR = LOW;
    ASSERT_TRUE(  Q == HIGH );
    ASSERT_TRUE( nQ == HIGH );
    nS = HIGH;
    nR = HIGH;

    // Test D input
    CLK = LOW;
    for (int i = 0; i < 10; ++i) {
        // Test setting with D
        D   = HIGH;
        CLK = HIGH; // Set
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        CLK = LOW;
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        // Test resetting with D
        D   = LOW;
        CLK = HIGH; // Reset
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        CLK = LOW;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Power down
    ff.p[7] = SUPPLY_GROUND;
    ASSERT_TRUE(  Q.isNC() );
    ASSERT_TRUE( nQ.isNC() );
}
