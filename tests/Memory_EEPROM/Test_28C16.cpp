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
//  (c) Andreas Terstegge
//
///////////////////////////////////////////////
//
#include "gtest/gtest.h"
#include "TestUtils.h"
#include "_28C16.h"
#include "BusRef.h"
#include "SimCadException.h"

TEST(Memory_EEPROM, 28C16)
{
    _28C16 ic("26C16");

    try {
        Pin & nCS  = ic.p[18];
        Pin & nOE  = ic.p[20];
        Pin & nWE  = ic.p[21];

        BusRef ADDR( {&ic.p[ 8], &ic.p[ 7], &ic.p[ 6], &ic.p[ 5], &ic.p[ 4],
                      &ic.p[ 3], &ic.p[ 2], &ic.p[ 1], &ic.p[23], &ic.p[22], &ic.p[19]} );
        BusRef DATA( {&ic.p[ 9], &ic.p[10], &ic.p[11], &ic.p[13],
                      &ic.p[14], &ic.p[15], &ic.p[16], &ic.p[17]} );

        // Power up
        ic.p[12] = SUPPLY_GROUND;
        ic.p[24] = SUPPLY_VOLTAGE;

        // Enable IC
        nCS = LOW;
        nOE = HIGH;
        nWE = HIGH;

        // Write Data
        for(int a=0; a < 2048; ++a) {
            ADDR = a;
            DATA = a & 0xff;
            nWE  = LOW;
            nWE  = HIGH;
        }

        // Read back Data
        DATA.setDrvNC();
        nOE = LOW;
        for(int a=0; a < 2048; ++a) {
            ADDR = a;
            ASSERT_TRUE( DATA  == (a & 0xff));
        }

        // Power down
        ic.p[24] = SUPPLY_GROUND;

    } catch (SimCadException &e) {
        std::cerr << e << std::endl;
    }
}
