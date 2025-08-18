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
#include "_74LS181.h"
#include "BusRef.h"

TEST(_74xx, LS181)
{
    _74LS181 ic("74LS181");

    Pin & nCin  = ic.p[7];
    Pin & M     = ic.p[8];
    Pin & AeqB  = ic.p[14];
    Pin & X     = ic.p[15];
    Pin & nCout = ic.p[16];
    Pin & Y     = ic.p[17];

    BusRef A( {&ic.p[2],  &ic.p[23],  &ic.p[21],  &ic.p[19]} );
    BusRef B( {&ic.p[1],  &ic.p[22],  &ic.p[20],  &ic.p[18]} );
    BusRef S( {&ic.p[6],  &ic.p[5],   &ic.p[4],   &ic.p[3]}  );
    BusRef F( {&ic.p[9],  &ic.p[10],  &ic.p[11],  &ic.p[13]} );

    // Power up
    ASSERT_TRUE( TestUtils::test_power_up24(ic.p) );

    // Logic functions
    auto MASK4 = [](int val){ return val & 0xf; };
    std::function<int(int, int)> logic_functions[16] = {
            [&](int A, int B) { return MASK4(      ~A  ); }, // NOT_A
            [&](int A, int B) { return MASK4( ~(A | B) ); }, // NOR
            [&](int A, int B) { return MASK4( ~(A | ~B)); }, // NOR_NOT
            [&](int A, int B) { return MASK4(       0  ); }, // NULL
            [&](int A, int B) { return MASK4( ~(A & B) ); }, // NAND
            [&](int A, int B) { return MASK4(      ~B  ); }, // NOT_B
            [&](int A, int B) { return MASK4(   A ^ B  ); }, // XOR
            [&](int A, int B) { return MASK4(   A & ~B ); }, // AND_NOT
            [&](int A, int B) { return MASK4( ~(A & ~B)); }, // NAND_NOT
            [&](int A, int B) { return MASK4( ~(A ^ B) ); }, // NXOR
            [&](int A, int B) { return MASK4(       B  ); }, // B
            [&](int A, int B) { return MASK4(   A & B  ); }, // AND
            [&](int A, int B) { return MASK4(      15  ); }, // ONES
            [&](int A, int B) { return MASK4(   A | ~B ); }, // OR_NOT
            [&](int A, int B) { return MASK4(   A | B  ); }, // OR
            [&](int A, int B) { return MASK4(       A  ); }, // A
    };

    // Test all logic functions
    M     = HIGH;  // Logic function
    nCin  = HIGH;  // no carry
    for(int func = 0; func < 16; func++) {
        S = func;
        for (int a=0; a < 16; a++) {
            for (int b = 0; b < 16; b++) {
                A = a;
                B = b;
                ASSERT_TRUE(F == logic_functions[func](a,b));
            }
        }
    }

    // Arithmetic functions
    std::function<int(int, int)> arithemtic_functions[16] = {
            [&](int A, int B) { return MASK4( ( A                 ) + !nCin ); },   // NULL
            [&](int A, int B) { return MASK4( ( A | B             ) + !nCin ); }, // AND_NOT
            [&](int A, int B) { return MASK4( ( A | ~B            ) + !nCin ); }, // NOR
            [&](int A, int B) { return MASK4( ( 15                ) + !nCin ); },   // NOT_A
            [&](int A, int B) { return MASK4( ( A + (A & ~B)      ) + !nCin ); }, // NOR_NOT
            [&](int A, int B) { return MASK4( ((A | B) + (A & ~B) ) + !nCin ); }, // XOR
            [&](int A, int B) { return MASK4( ( A - B - 1         ) + !nCin ); }, // NOT_B
            [&](int A, int B) { return MASK4( ((A & ~B) - 1       ) + !nCin ); }, // NAND
            [&](int A, int B) { return MASK4( ( A + (A & B)       ) + !nCin ); },   // AND
            [&](int A, int B) { return MASK4( ( A + B             ) + !nCin ); },   // B
            [&](int A, int B) { return MASK4( ((A | ~B) + (A & B) ) + !nCin ); }, // NXOR
            [&](int A, int B) { return MASK4( ((A & B) - 1        ) + !nCin ); }, // OR_NOT
            [&](int A, int B) { return MASK4( ( A + A             ) + !nCin ); },   // A
            [&](int A, int B) { return MASK4( ( A + (A | B)       ) + !nCin ); },   // OR
            [&](int A, int B) { return MASK4( ( A + (A | ~B)      ) + !nCin ); }, // NAND_NOT
            [&](int A, int B) { return MASK4( ( A - 1             ) + !nCin ); },   // ONES
    };

    // Test all arithmetic functions
    M = LOW;    // Arithmetic function
    for(int func = 0; func < 16; func++) {
        S = func;
        for (int a=0; a < 16; a++) {
            for (int b = 0; b < 16; b++) {
                A = a;
                B = b;
                // Test without carry
                nCin  = HIGH;
                ASSERT_TRUE(F == arithemtic_functions[func](a,b));
                // Test with carry
                nCin  = LOW;
                ASSERT_TRUE(F == arithemtic_functions[func](a,b));
            }
        }
    }

    // Power down
    ASSERT_TRUE( TestUtils::test_power_down24(ic.p,
                 { &ic.p[9],  &ic.p[10], &ic.p[11], &ic.p[13],
                   &ic.p[14], &ic.p[15], &ic.p[16], &ic.p[17] }) );
}
