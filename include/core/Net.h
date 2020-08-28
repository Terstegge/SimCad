///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
/*
 * This file is part of the DigiSim Software -
 * a simulation package for digital circuits.
 *
 * (c) 2020 A. Terstegge
 *
 * The class 'Net' contain a list of connected Pins.
 * Single Pins can be added to a Net.
 * Another whole Net can be merged into a Net.
 *
 */

#ifndef _NET_H_
#define _NET_H_

#include "Named.h"
#include "State.h"

#include <vector>
using std::vector;

#include <set>
#include <memory>
#include <string>
#include <iostream>

class Pin;
class Net;

typedef std::shared_ptr<Net> NetPtr;
typedef std::set<NetPtr>     NetSet;

class Net : public Named {
public:

    // Global count of Short Circuits
    static int _short_circuit_count;

    // Global counter for the number of Nets
    static int _no_nets;

    // Factory method: Create a new Net and add a first Pin
    static std::shared_ptr<Net> create_net(std::string n, Pin * p) {
        Net * net = new Net(n);
        net->_pins.push_back(p);
        return std::shared_ptr<Net>(net);
    }

    Net(const std::string & name) : Named(name),
        _short_circuit(false)
    {
        ++_no_nets;
    }

    ~Net() {
        --_no_nets;
    }

    // Merge two Nets. The second parameter is the 'old' Net,
    // which entries are copied to our Pin vector. The first
    // parameter is the shared_ptr of this Net, which needs
    // to be set in the new Pin entries!
    void merge_net(NetPtr o, NetPtr n);


    // This method first calculates the new boolean state of
    // the Net. If it changed, update() is called on every
    // Pin in the Net. The method will return true if the
    // state has changed.
    bool update(NetSet * nets);


    // Return the current State of this Net.
    inline const State & getState() {
        return _state;
    }

    // Output operator for a Net
    friend std::ostream & operator << (std::ostream & os, const NetPtr net);

//private:

    // This method scans through all Pins in the Net
    // and calculates the resulting State. If a
    // short circuit is detected, a exception is
    // thrown.
    State calculate_state();

    vector<Pin *>   _pins;
    State           _state;
    bool            _short_circuit;

};

#endif // _NET_H_
