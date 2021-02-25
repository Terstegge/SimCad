/*
 * TestUtils.h
 *
 *  Created on: 23.02.2021
 *      Author: andreas
 */

#ifndef TESTS_TESTUTILS_H_
#define TESTS_TESTUTILS_H_

#include <functional>
#include <initializer_list>
#include "Pin.h"
#include "Bus.h"

class TestUtils {
public:
    static bool test_power_up14(Bus<15> & pins);

    static bool test_power_up16(Bus<17> & pins);

    static bool test_power_down14(Bus<15> & pins, std::initializer_list<Pin *> outputs = {});

    static bool test_power_down16(Bus<17> & pins, std::initializer_list<Pin *> outputs = {});

    static bool test_gate1(Pin & I, Pin & O,
                           std::function<bool(bool)> f);

    static bool test_gate2(Pin & I1, Pin & I2, Pin & O,
                           std::function<bool(bool,bool)> f);

    static bool test_gate3(Pin & I1, Pin & I2, Pin & I3, Pin & O,
                           std::function<bool(bool,bool, bool)> f);

};

#endif /* TESTS_TESTUTILS_H_ */
