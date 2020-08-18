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
// A Pin can have a update function, which is called
// whenever the associated Net changes its value.
//
#ifndef _PIN_H_
#define _PIN_H_

#include "Named.h"
#include "Part.h"
#include "State.h"
#include "Net.h"

#include <iostream>
using std::ostream;

#include <functional>
using std::function;

#include <string>
using std::string;

class Pin : public Named {
public:

    // Pin constructor.
    Pin(const string & name="", State s = NC)
    : Named(name), _drv_state(NC),
      _net(Net::create_net(name, this)),_partPtr(nullptr)  { }

    // No assignment, no copy
    Pin & operator = (const Pin & p) = delete;
    Pin              (const Pin & p) = delete;

    // Attach a processing function to this pin
    // (usually the input pins of a circuit).
    inline void attach(function<void(NetSet *)> u) {
        _update = u;
    }

    // Helper-method to safely call the _update() method.
    // When the State of the connected Net changes, this
    // Net will call this method to trigger a new calculation
    // of some logic function.
    inline void update(NetSet * nets) {
        if (_update) _update(nets);
    }

    // Connect two pins. This is done by merging
    // the two Nets which belong to the two Pins.
    // If both Pins are members of the same Net,
    // this method has no effect.
    void connect_to(Pin & p);

    // Operators to modify the drive state of
    // a Pin. The parameter can be a bool (for
    // easier use with logic functions) or a
    // State. Internally, setDrvState() is called
    // iteratively, and every iteration reports a
    // new set of Nets which need to be updated.
    inline void operator = (bool val) {
        (*this) = State(val);
    }
    void operator = (State s);

    // Set driving state from a boolean or State.
    // These methods will not recurse via the whole
    // circuit when a valid NetSet is given. The
    // method then will report the next level
    // of Nets to be updated, which are stored in
    // the parameter 'nets'.
    // When nets is a nullptr, the method will
    // recursively update the whole circuit.
    inline void setDrvState(bool val, NetSet * nets) {
        (*this).setDrvState( State(val), nets );
    }
    void setDrvState(State s, NetSet * nets);


    // Get the input state of a Pin
    inline State getInpState() const {
        return _net->getState();
    }

    // Get the driving state of this Pin
    inline State getDrvState() const {
        return _drv_state;
    }

    // Get input state as boolean. This is
    // mostly used for input pins without a
    // three-state mode.
    inline operator bool () const {
        return getInpState();
    }

    // Get input state as State. This is
    // mostly used for input pins with a
    // three-state mode.
    inline operator State () const {
        return getInpState();
    }

    // Return the Net pointer
    inline NetPtr getNet() {
        return _net;
    }

    // Set the Net pointer
    inline void setNet(NetPtr p) {
        _net = p;
    }

    // Return the Net pointer
    inline Part * getPartPtr() {
        return _partPtr;
    }

    // Set the Net pointer
    inline void setPartPtr(Part * p) {
        _partPtr = p;
    }

    // The stream output operator will insert the input state
    // of the Pin to the ostream. This is what is most often
    // interesting for the user in case of input Pins.
    // For output Pins, the operator will typically show the
    // driving state of the Pin, because normally only one Pin
    // is driving a Net.
    friend ostream & operator << (ostream & os, const Pin & p) {
        os << p.getName() << ":" << p.getInpState();
        return os;
    }

private:

    State   _drv_state;                 // The driving state of this Pin
    NetPtr  _net;                       // The associated Net
    function<void(NetSet *)> _update;   // The associated update function
    Part *  _partPtr;                   // Pointer to the related Part
};

#endif // _PIN_H_
