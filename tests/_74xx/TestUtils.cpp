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
#include "TestUtils.h"

bool TestUtils::test_power_up14(Bus<15> & p) {
    // Check Pins before power up
    for (int i = 1; i <= 14; ++i) {
        if (!p[i].isNC()) return false;
    }
    // Power up
    p[7]  = SUPPLY_GROUND;
    p[14] = SUPPLY_VOLTAGE;
    return true;
}

bool TestUtils::test_power_up16(Bus<17> & p) {
    // Check Pins before power up
    for (int i = 1; i <= 16; ++i) {
        if (!p[i].isNC()) return false;
    }
    // Power up
    p[8]  = SUPPLY_GROUND;
    p[16] = SUPPLY_VOLTAGE;
    return true;
}

bool TestUtils::test_power_up24(Bus<25> & p) {
    // Check Pins before power up
    for (int i = 1; i <= 24; ++i) {
        if (!p[i].isNC()) return false;
    }
    // Power up
    p[12] = SUPPLY_GROUND;
    p[24] = SUPPLY_VOLTAGE;
    return true;
}

bool TestUtils::test_power_down14(Bus<15> & p, std::initializer_list<Pin *> outputs) {
    // Power down
    p[14] = SUPPLY_GROUND;
    // Check output Pins
    for(Pin * o : outputs) {
        if(!o->isNC()) return false;
    }
    return true;
}

bool TestUtils::test_power_down16(Bus<17> & p, std::initializer_list<Pin *> outputs) {
    // Power down
    p[16] = SUPPLY_GROUND;
    // Check output Pins
    for(Pin * o : outputs) {
        if(!o->isNC()) return false;
    }
    return true;
}

bool TestUtils::test_power_down24(Bus<25> & p, std::initializer_list<Pin *> outputs) {
    // Power down
    p[24] = SUPPLY_GROUND;
    // Check output Pins
    for(Pin * o : outputs) {
        if(!o->isNC()) return false;
    }
    return true;
}

bool TestUtils::test_gate1(Pin & I, Pin & O,
        std::function<bool(bool)> f) {
    I = LOW;
    if (O != f(LOW)) return false;
    I = HIGH;
    if (O != f(HIGH)) return false;
    return true;
}


bool TestUtils::test_gate2(Pin & I1, Pin & I2, Pin & O,
        std::function<bool(bool,bool)> f) {
    for(int i=0; i<4; ++i) {
        bool v1 = i & 1;
        bool v2 = i & 2;
        I1 = v1;
        I2 = v2;
        if (O != f(v1,v2)) return false;
    }
    return true;
}

bool TestUtils::test_gate3(Pin & I1, Pin & I2, Pin & I3, Pin & O,
        std::function<bool(bool,bool, bool)> f) {
    for(int i=0; i<8; ++i) {
        bool v1 = i & 1;
        bool v2 = i & 2;
        bool v3 = i & 4;
        I1 = v1;
        I2 = v2;
        I3 = v3;
        if (O != f(v1,v2,v3)) return false;
    }
    return true;

}
