///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
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
#include <mutex>
class Pin;
class Net;

// Type definition for a set of update-able objects
using NetSet = std::set<Net *>;
// Type definition for update functions
using UFUNC  = std::function<void(NetSet *)>;

class Net : public Named {

private:
    std::vector<Pin *>  _pins;
    double  _U;
    double  _Rg;
    int     _drivers;


public:
    std::mutex _mutex;
    static bool _enable_sc_exceptions;

    // Global counter for the number of Nets
    static int _no_nets;
    Net(const std::string & name) : Named(name),
          U(_U), _U(0.0), _Rg(INF), R(_Rg), _drivers(0)
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
        return (_U == 0.0) && isVS();
    }
    inline bool isVCC() const {
        return (_U == SUPPLY_VOLTAGE) && isVS();
    }
    inline bool isNC() const {
        return _Rg == INF;
    }
    inline bool isVS() const {
        return _Rg == 0.0;
    }
    inline operator bool () const {
        return isNC() ? true : _U > (SUPPLY_VOLTAGE/2);
    }
    inline bool hasDrivers() { return _drivers != 0; }

    // Output operator for a Net
    friend class Pin;
    friend std::ostream & operator << (std::ostream & os, const Net *  net);

    const double &  U;
    const double &  R;

    double Isum(double U, const Pin * p = nullptr) const;
    double IsumwVS(double U) const;

    double zero(std::function<double(double)> f);
    void show_driver();

//    inline double R() const {
//        return _Rg;
////        return U / Isum(U);
//    }

    double Rw(const Pin * p) const;

    double RwVS() const;

//    double R(Net *net=nullptr);

//    inline double Rd() const {
//        double dU = 0.2;
//        return dU / (Isum(U + dU/2.0) - Isum(U - dU/2.0));
//    }
};

#endif // _NET_H_
