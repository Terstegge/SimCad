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
// connected to each other). A Pin has an update function,
// which is called whenever the associated Net changes its
// value.
//
#ifndef INCLUDE_PIN_H
#define INCLUDE_PIN_H

#include "Named.h"
#include "Part.h"
#include "Net.h"

#include <iostream>
#include <functional>
#include <string>
#include <limits>

#define INF std::numeric_limits<float>::infinity()

#define SUPPLY_VOLTAGE 5.0
#define SUPPLY_GROUND  0.0

class Pin : public Named {
public:
    // Pin constructor.
    Pin(const std::string & name="");

    // No assignment, no copy for now...
    Pin & operator = (const Pin & p) = delete;
    Pin              (const Pin & p) = delete;

    // Connect two pins. If both Pins are members of
    // the same Net, this method has no effect.
    void connect_to(Pin & p);

    // Methods dealing with driving state
    void setDrvState(float u, float g, float i, NetSet *nets);

    inline void setDrvVS(float u, NetSet *nets = nullptr) {
        setDrvState(u, INF, 0, nets);
    }
    inline void setDrvNC(NetSet * nets) {
        setDrvState(0.0, 0.0, 0.0, nets);
    }
    inline void setDrvBool(bool b, NetSet * nets) {
        setDrvVS(b ? 5.0 : 0.0, nets);
    }
    bool isDrvNC() const {
        return (Ud == 0.0) && (Gd == 0.0) && (Id == 0.0);
    }
    void operator = (float f) {
        setDrvVS(f);
    }


    // Methods dealing with the NET state
    inline float U() const {
        return _netPtr ? _netPtr->U : Ud;
    }
    inline float Gi() const {
        return _netPtr ? _netPtr->Gi : Gd;
    }
    float I() const {
        if (Gd == INF) {
            float i = 0;
            int cnt = 0;
            for (Pin * p : _netPtr->_pins) {
                if (p->Gd == INF) {
                    cnt++;
                } else {
                    i += p->I();
                }
            }
            return -i / cnt;
        } else {
            return (Ud - U()) * Gd;
        }
    }
    inline bool isGND() const {
        return (U() == 0.0) && (Gi() == INF);
    }
    inline bool isVCC() const {
        return (U() == 5.0) && (Gi() == INF);
    }
    inline bool isNC() const {
        return Gi() == 0.0;
    }
    inline operator bool () const {
        return isNC() ? true : U() > (SUPPLY_VOLTAGE/2);
    }

    // Getter/Setter for Net pointer
    inline NetPtr getNetPtr() const { return _netPtr; }
//    inline void setNetPtr(NetPtr p) { _netPtr = p;    }

    // Getter/Setter for Part pointer
    inline Part * getPartPtr() const { return _partPtr; }
    inline void setPartPtr(Part * p) { _partPtr = p;    }

    // Attach a processing function to this pin
    // (usually the input pins of a circuit).
    inline void attach(std::function<void(NetSet *)> u) {
        _update = u;
    }

    // Helper-method to safely call the _update() method.
    // When the State of the connected Net changes, this
    // Net will call this method to trigger a new calculation
    // of some (logic) function.
    inline void update(NetSet * nets) {
        if (_update) _update(nets);
    }

    // Friend and output operator
    friend class Net;
    friend class TwoPole;
    friend std::ostream & operator << (std::ostream & os, const Pin & p);

    // Flag controlling the stream output.
    // If set, the driving state is used.
    static bool _drv;

private:
    float Ud;           // Driving voltage
    float Gd;           // Driving conductivity
    float Id;           // Driving current

    NetPtr  _netPtr;    // The associated Net
    Part *  _partPtr;   // Pointer to the related Part

    // The associated update function
    std::function<void(NetSet *)> _update;
};

// Manipulator to output the driving state
inline std::ostream &drive(std::ostream &out) {
    Pin::_drv = true;
    return out;
}

#endif // INCLUDE_PIN_H
