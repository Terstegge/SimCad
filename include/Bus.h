/*
 * Bus.h
 *
 *  Created on: 26.12.2019
 *      Author: andreas
 */

#ifndef _BUS_H_
#define _BUS_H_

#include "Narray.h"
#include "Named.h"
#include "Pin.h"

#include <iomanip>
using std::setw;
using std::setfill;
using std::oct;

#include <sstream>
using std::ostringstream;

template<size_t N>
class Bus : public Narray<Pin, N> {
public:

    Bus(const string & n="") : Narray<Pin, N>(n) { }

    // No assignment, no copy
    Bus<N> & operator = (const Bus<N> & p) = delete;
    Bus<N>              (const Bus<N> & p) = delete;

    void operator = (unsigned int val) {
        NetSet net1;
        unsigned int mask = 1;
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].setDrvState((bool)(val & mask) , &net1);
            mask <<= 1;
        }
        // Iterate until no updates are necessary
        while (net1.size()) {
            NetSet net2;
            for (shared_ptr<Net> n : net1) {
                n->update(nullptr, &net2);
            }
            net1 = net2;
        }
    }

    void operator = (State s) {
        NetSet net1;
        // Set new drv state on all pins
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].setDrvState(s, &net1);
        }
        // Iterate until no updates are necessary
        while (net1.size()) {
            NetSet net2;
            for (shared_ptr<Net> n : net1) {
                n->update(nullptr, &net2);
            }
            net1 = net2;
        }
    }

    void operator = (Bus<N> & rhs) {
        NetSet net1;
        // Set new drv state on all pins
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].setDrvState(rhs[i].getInpState(), &net1);
        }
        // Iterate until no updates are necessary
        while (net1.size()) {
            NetSet net2;
            for (shared_ptr<Net> n : net1) {
                n->update(nullptr, &net2);
            }
            net1 = net2;
        }
    }

    operator unsigned int () const {
        unsigned int res = 0, mask = 1;
        for (size_t i=0; i < this->size(); ++i) {
            if ( (bool)(*this)[i] ) res |= mask;
            mask <<= 1;
        }
        return res;
    }

    string drv_state() const {
        ostringstream oss;
        for (size_t i=0; i < this->size(); ++i) {
            oss << (*this)[i].getInpState();
        }
        return oss.str();
    }

    void connect_to(Bus & bus) {
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].connect_to(bus[i]);
        }
    }

    template<size_t M>
    void connect_to(Bus<M> & bus, size_t offset) {
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].connect_to(bus[i+offset]);
        }
    }

    void attach(function<void(NetSet *)> u) {
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i].attach(u);
        }
    }

    friend ostream & operator << (ostream & os, const Bus & rhs) {
        os << rhs.getName() << ":";
        os << setw(4) << setfill('0') << oct << (unsigned int)rhs;
//        os << "(" << rhs.drv_state() << ")";
        return os;
    }

};

#endif // _BUS_H_
