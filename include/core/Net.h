///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2021  A. Terstegge
///////////////////////////////////////////////
#ifndef _INCLUDE_NET_H_
#define _INCLUDE_NET_H_

#include "Named.h"
#include "Config.h"
#include <vector>
using std::vector;
#include <set>
#include <memory>
#include <string>
#include <iostream>
#include <functional>
class Pin;
class Net;

// Type definition for a set of update-able objects
using NetSet = std::set<Net *>;
// Type definition for update functions
using UFUNC  = std::function<void(NetSet *)>;

class Net : public Named {

private:
    std::vector<Pin *>  _pins;
    bool    _isNC;
    double  _U;
    bool    _isVS;
    int     _drivers;

public:
    // Global counter for the number of Nets
    static int _no_nets;
    Net(const std::string & name) : Named(name),
          U(_U), _U(0.0), _isVS(false), _isNC(true), _drivers(0)
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
    void merge_net(Net * n, Net * o);

    // This method first calculates the new state of
    // the Net. If it changed, update() is called on every
    // Pin in the Net.
    // This method scans through all Pins in the Net
    // and calculates the resulting State. If a
    // short circuit is detected, a exception is
    // thrown.
    void update(NetSet * nset);

    // Update the current Net and all Subnets
    void update();

    inline bool isGND() const {
        return (_U == 0.0) && _isVS;
    }
    inline bool isVCC() const {
        return (_U == SUPPLY_VOLTAGE) && _isVS;
    }
    inline bool isNC() const {
        return _isNC && !_isVS;
    }
    inline bool isVS() const {
        return _isVS;
    }
    inline operator bool () const {
        return isNC() ? true : _U > (SUPPLY_VOLTAGE/2);
    }
    inline bool hasDrivers() { return _drivers != 0; }

    // Output operator for a Net
    friend class Pin;
    friend std::ostream & operator << (std::ostream & os, const Net *  net);

    const double &  U;
    double Isum(double U, Pin * p = nullptr) const;
    int sgn(double v);
    double zero(std::function<double(double)> f);
    void show_driver();

    inline double R() const {
        return U / Isum(U);
    }

    inline double Rd() const {
        double dU = 0.2;
        return dU / (Isum(U + dU/2.0) - Isum(U - dU/2.0));
    }
};

#endif // _NET_H_
