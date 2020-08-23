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
// The class 'Pin' models a single pin (either as part
// of a circuit or stand-alone). It has a driving state,
// and is associated to a Net (a set of Pins which are
// connected to each other).
// A Pin can have an update function, which is called
// whenever the associated Net changes its value.
//
#ifndef INCLUDE_PIN_H_
#define INCLUDE_PIN_H_

#include "Named.h"
#include "Part.h"
#include "State.h"
#include "Net.h"

#include <iostream>
#include <functional>
#include <string>

class Pin : public Named {
public:

    // Pin constructor.
    Pin(const std::string & name="") : Named(name),
        _netPtr (Net::create_net(name, this)),
        _partPtr(nullptr)
    {
    }

    // No assignment, no copy for now...
    Pin & operator = (const Pin & p) = delete;
    Pin              (const Pin & p) = delete;

    // Connect two pins. This is done by merging
    // the two Nets which belong to the two Pins.
    // If both Pins are members of the same Net,
    // this method has no effect.
    void connect_to(Pin & p);

    // Attach a processing function to this pin
    // (usually the input pins of a circuit).
    inline void attach(std::function<void(NetSet &)> u) {
        _update = u;
    }

    // Helper-method to safely call the _update() method.
    // When the State of the connected Net changes, this
    // Net will call this method to trigger a new calculation
    // of some (logic) function.
    inline void update(NetSet & nets) {
        if (_update) _update(nets);
    }

    // Get the input state of a Pin
    inline State getInpState() const {
        return _netPtr->getState();
    }

    // Get the Equivalent Voltage Source
    // (EVS) as seen from this Pin
    State getEVS();

    // Get the driving state of this Pin
    inline State getDrvState() const {
        return _drvState;
    }

    // Set driving state. This method will
    // report the next level of Nets to be
    // updated, which are stored in the
    // parameter 'nets'.
    void setDrvState(State s, NetSet & nets);

    // Getter/Setter for Net pointer
    inline NetPtr getNetPtr() {
        return _netPtr;
    }
    inline void setNetPtr(NetPtr p) {
        _netPtr = p;
    }

    // Getter/Setter for Part pointer
    inline Part * getPartPtr() {
        return _partPtr;
    }
    inline void setPartPtr(Part * p) {
        _partPtr = p;
    }

    // Operator support:
    // - The assignment operator modifies the driving state.
    // - The type conversion operators read out input state.
    void operator = (State s);

    inline operator State () const {
        return getInpState();
    }
    inline operator bool () const {
        return (bool)getInpState();
    }

    // Output stream operator
    friend std::ostream & operator << (std::ostream & os, const Pin & p) {
        os << p.getName() << ": " << p.getInpState();
        return os;
    }

private:
    std::function<void(NetSet &)> _update;  // The associated update function
    State   _drvState;                      // The driving state of this Pin
    NetPtr  _netPtr;                        // The associated Net
    Part *  _partPtr;                       // Pointer to the related Part
};

#endif // INCLUDE_PIN_H_
