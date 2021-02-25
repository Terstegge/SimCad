#include "gtest/gtest.h"
#include "TestUtils.h"
#include "JK_FF.h"

TEST(Flipflops, JK_FF)
{
    JK_FF ff("JK_FF");

    Pin & J    = ff.p[1];
    Pin & nCLK = ff.p[2];
    Pin & K    = ff.p[3];
    Pin & nS   = ff.p[4];
    Pin & nR   = ff.p[5];
    Pin &  Q   = ff.p[6];
    Pin & nQ   = ff.p[7];

    // Power up
    ff.p[0] = SUPPLY_GROUND;
    ff.p[8] = SUPPLY_VOLTAGE;

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

    // Test J/K inputs
    nCLK = HIGH;
    for (int i = 0; i < 10; ++i) {
        // Test setting with J
        J    = HIGH;
        K    = LOW;
        nCLK = LOW; // Set
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        // Test resetting with K
        J    = LOW;
        K    = HIGH;
        nCLK = LOW; // Reset
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Test no change with J=K=0
    J = LOW;
    K = LOW;
    for (int i = 0; i < 10; ++i) {
        nCLK = LOW;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Test toggle with J=K=1
    J = HIGH;
    K = HIGH;
    for (int i = 0; i < 10; ++i) {
        // Set with toggle
        nCLK = LOW;
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        // Reset with toggle
        nCLK = LOW;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Power down
    ff.p[8] = SUPPLY_GROUND;
    ASSERT_TRUE(  Q.isNC() );
    ASSERT_TRUE( nQ.isNC() );
}
