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
//  (c) 2021  A. Terstegge
//
///////////////////////////////////////////////
//
#ifndef _INCLUDE_NET_H_
#define _INCLUDE_NET_H_

#include "Named.h"
#include "Config.h"
#include "Element.h"

#include <vector>
using std::vector;

#include <set>
#include <memory>
#include <string>
#include <iostream>

class Pin;
class Net;

//typedef std::shared_ptr<Net> NetPtr;
typedef Net* NetPtr;
//typedef std::set<NetPtr>     NetSet;

class Net : public Named, public Element {
public:
    // Global counter for the number of Nets
    static int _no_nets;

    // Factory method: Create a new Net and add a first Pin
    static NetPtr create_net(std::string n) {
        return NetPtr(new Net(n));
    }

    Net(const std::string & name) : Named(name),
          U(_U), Gi(_Gi), Id(_Id), Gs(_Gs),
         _U(0), _Gi(0),  _Id(0),  _Gs(0)
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
    void merge_net(NetPtr n, NetPtr o);

    // This method first calculates the new state of
    // the Net. If it changed, update() is called on every
    // Pin in the Net.
    // This method scans through all Pins in the Net
    // and calculates the resulting State. If a
    // short circuit is detected, a exception is
    // thrown.
    void update(ElementSet * esp) override;

    // Update the current Net and all Subnets
    void update();

    inline bool isGND() const {
        return (_U == 0.0) && (_Gi == INF);
    }
    inline bool isVCC() const {
        return (_U == SUPPLY_VOLTAGE) && (_Gi == INF);
    }
    inline bool isNC() const {
        return _Gi == 0.0 && _Id == 0.0;
    }
    inline bool isVS() const {
        return _Gi == INF;
    }
    inline operator bool () const {
        return isNC() ? true : _U > (SUPPLY_VOLTAGE/2);
    }

    // Output operator for a Net
    friend class Pin;
    friend std::ostream & operator << (std::ostream & os, const NetPtr net);

    const double &  U;
    const double &  Gi;
    const double &  Id;
    const double &  Gs;

private:
    vector<Pin *>   _pins;

    double          _U;
    double          _Gi;
    double          _Id;
    double          _Gs;
};

#endif // _NET_H_
