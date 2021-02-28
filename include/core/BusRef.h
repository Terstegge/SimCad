/*
 * Bus.h
 *
 *  Created on: 26.12.2019
 *      Author: andreas
 */

#ifndef _BUSREF_H_
#define _BUSREF_H_

#include "Narray.h"
#include "Named.h"
#include "Pin.h"

#include <vector>
#include <iomanip>
using std::setw;
using std::setfill;
using std::oct;

#include <sstream>
using std::ostringstream;

class BusRef : public std::vector<Pin *> {
public:

    BusRef(vector<Pin *> v) : std::vector<Pin *>(v) { }

    void operator = (unsigned int val) {
        ElementSet net1;
        unsigned int mask = 1;
        for (size_t i=0; i < this->size(); ++i) {
            (*this)[i]->setDrvBool((bool)(val & mask), &net1);
            mask <<= 1;
        }
        // Iterate until no updates are necessary
        while (net1.size()) {
            ElementSet net2;
            for (ElementPtr n : net1) {
                n->update(&net2);
            }
            net1 = net2;
        }
    }

//    void operator = (BusRef & rhs) {
//        NetSet net1;
//        // Set new drv state on all pins
//        for (size_t i=0; i < this->size(); ++i) {
//            (*this)[i]->setDrvState((*rhs[i]).getInpState(), net1);
//        }
//        // Iterate until no updates are necessary
//        while (net1.size()) {
//            NetSet net2;
//            for (std::shared_ptr<Net> n : net1) {
//                n->update(net2);
//            }
//            net1 = net2;
//        }
//    }

    operator unsigned int () const {
        unsigned int res = 0, mask = 1;
        for (size_t i=0; i < this->size(); ++i) {
            if ((bool)(*(*this)[i])) res |= mask;
            mask <<= 1;
        }
        return res;
    }

//    std::string drv_state() const {
//        ostringstream oss;
//        for (size_t i=0; i < this->size(); ++i) {
//            oss << (*(*this)[i]).getInpState();
//        }
//        return oss.str();
//    }

//    void connect_to(BusRef & bus) {
//        for (size_t i=0; i < this->size(); ++i) {
//            (*this)[i]->connect_to(*bus[i]);
//        }
//    }
//
//    template<size_t M>
//    void connect_to(Bus<M> & bus, size_t offset) {
//        for (size_t i=0; i < this->size(); ++i) {
//            (*this)[i]->connect_to(bus[i+offset]);
//        }
//    }

//    void attach(std::function<void(NetSet &)> u) {
//        for (size_t i=0; i < this->size(); ++i) {
//            (*this)[i]->attach(u);
//        }
//    }

//    friend std::ostream & operator << (std::ostream & os, const BusRef & rhs) {
////        os << rhs.getName() << ":";
//        os << setw(4) << setfill('0') << oct << (unsigned int)rhs;
////        os << "(" << rhs.drv_state() << ")";
//        return os;
//    }

};

#endif // _BUSREF_H_
