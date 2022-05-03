///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2021  A. Terstegge
///////////////////////////////////////////////
// The class 'Pin' models a single pin (either as part
// of an electronic component  or stand-alone). It is
// always associated to a Net (a new Net is created in
// the constructor). A Pin can either be an ideal voltage
// source or a Pin driving a specific I(U) characteristic.
// A Pin can have an update-function, which is always
// called when the associated Net changes its state.
//
#ifndef _INCLUDE_PIN_H_
#define _INCLUDE_PIN_H_

// DIGISIM includes
#include "Net.h"
// Base classes
#include "Named.h"
// Standard includes
#include <functional>
#include <string>

// Type definition for a I(U) characteristic
using IFUNC = std::function<double(double)>;

class Pin : public Named {

	// Net is our friend and might change _netPtr or _Uw.
    friend class Net;
    // TwoPole is our friend and might change _Idrv.
    friend class TwoPole;
    // Gate is our friend and might change _Idrv, _Uvs, _isVS.
    template<int N> friend class Gate;
    friend class ISOURCE;

private:
    // Pointer to the associated Net. Note that this pointer is always
    // valid, because a Pin will always create its own Net in the CTOR.
    // When Pins are (electrically) connected, this pointer might change.
    // _netPtr is only changed internally (e.g. with the connect_to()
    // function), so there is no public setter.
    Net * _netPtr;

    // Attributes used if this Pin is a voltage source. In this case,
    // the attribute _isVS will be set to true, and _Uvs will store the
    // voltage value. _Idrv will not be used.
    double  _Uvs;
    bool    _isVS;

    // The I(U) driving function, which describes the contribution of
    // this Pin within its Net. If the function is not set, the Pin is
    // either not connected or a voltage source.
    IFUNC   _Idrv;

    // Helper method to set _Idrv and to update the Net afterwards.
    void setIDrv(IFUNC f, NetSet * nset = nullptr);

    // The associated update function, which is called when the associated
    // Net changes its voltage/state.
    UFUNC   _update;

public:

    // Pin constructor.
    Pin(const std::string & name="");

    // No assignment, no copy for now...
    Pin & operator = (const Pin & p) = delete;
    Pin              (const Pin & p) = delete;

    // Electrically connect two pins. If both Pins are members of the
    // same Net, this method has no effect. Otherwise, all Pins of the
    // Net which contains p will be merged into the Net of this Pin.
    void connect_to(Pin & p);

    // Getter for the Net pointer
    inline Net * getNet() const { return _netPtr; }

    // Set this Pin to drive an ideal Voltage Source (VS).
    void setDrvVS(double u, NetSet * nset = nullptr);

    // Set this Pin to drive an ideal Voltage Source with either
    // SUPPLY_VOLTAGE or 0 volts. This method is used in digital circuits.
    void setDrvBool(bool b, NetSet * nset = nullptr);

    // Set this Pin to a 'not connected' state (NC).
    void setDrvNC(NetSet * nset = nullptr);

    // Getters to check if Pin is driving a voltage source
    // or is not connected.
    inline bool isDrvVS() const { return  _isVS; }
    inline bool isDrvNC() const { return !_isVS && !_Idrv; }

    // Operators for easily setting a voltage source by assigning
    // a double or boolean value.
    inline void operator = (double f) { setDrvVS(f);   }
    inline void operator = (bool b)   { setDrvBool(b); }

    // Attach a processing function to this Pin. This method will be
    // called when the associated Net has changed its value/state.
    inline void attach(UFUNC u) {
        _update = u;
    }

    // Safely call the _update() method.
    inline void update(NetSet * nset) {
        if (_update) _update(nset);
    }

    // Methods checking the Net state
    /////////////////////////////////
    inline bool isGND()     const { return _netPtr->isGND(); }
    inline bool isVCC()     const { return _netPtr->isVCC(); }
    inline bool isNC()      const { return _netPtr->isNC();  }
    inline bool isVS()      const { return _netPtr->isVS();  }
    inline operator bool () const { return _netPtr->operator bool(); }

    // Electrical values
    ////////////////////
    double U() const;
    double R() const;
    double I() const;

    // Stream output operator
    friend std::ostream & operator << (std::ostream & os, const Pin & p);

    // Flag controlling the stream output. If set, the driving state
    // is used in the <<-operator for the next operation. The flag is
    // then reset automatically.
    static bool _show_drive_state;
};

// Manipulator to output the driving state
inline std::ostream &drive(std::ostream &out) {
	Pin::_show_drive_state = true;
	return out;
}

#endif // _INCLUDE_PIN_H_
