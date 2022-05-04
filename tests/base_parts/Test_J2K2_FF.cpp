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
#include "J2K2_FF.h"

TEST(base_parts, J2K2_FF)
{
    J2K2_FF ff("J2K2_FF");

    Pin & J1   = ff.p[1];
    Pin & J2   = ff.p[2];
    Pin & nCLK = ff.p[3];
    Pin & K1   = ff.p[4];
    Pin & K2   = ff.p[5];
    Pin & nS   = ff.p[6];
    Pin & nR   = ff.p[7];
    Pin &  Q   = ff.p[8];
    Pin & nQ   = ff.p[9];

    // Power up
    ff.p[0]  = SUPPLY_GROUND;
    ff.p[10] = SUPPLY_VOLTAGE;

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
    J2   = HIGH; // Only use J1/K1 inputs
    K2   = HIGH;
    for (int i = 0; i < 10; ++i) {
        // Test setting with J
        J1   = HIGH;
        K1   = LOW;
        nCLK = LOW; // Set
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == HIGH );
        ASSERT_TRUE( nQ == LOW  );
        // Test resetting with K
        J1   = LOW;
        K1   = HIGH;
        nCLK = LOW; // Reset
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Test no change with J=K=0
    J1 = LOW;
    K1 = LOW;
    for (int i = 0; i < 10; ++i) {
        nCLK = LOW;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
        nCLK = HIGH;
        ASSERT_TRUE(  Q == LOW );
        ASSERT_TRUE( nQ == HIGH  );
    }

    // Test toggle with J=K=1
    J1 = HIGH;
    K1 = HIGH;
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
    ff.p[10] = SUPPLY_GROUND;
    ASSERT_TRUE(  Q.isNC() );
    ASSERT_TRUE( nQ.isNC() );
}
