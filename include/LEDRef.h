/////////////////////////////////////////////////
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
/////////////////////////////////////////////////
//
#ifndef _LEDREF_H_
#define _LEDREF_H_

#include "Narray.h"
#include "Named.h"
#include "LED.h"
#include <vector>
#include <iomanip>

using std::setw;
using std::setfill;
using std::oct;
#include <sstream>
using std::ostringstream;

class LEDRef : public std::vector<LED *> {
public:
	LEDRef(vector<LED *> v) : std::vector<LED *>(v) { }

	operator unsigned int () const {
		unsigned int res = 0, mask = 1;
		for (size_t i=0; i < this->size(); ++i) {
			if ((*this)[i]->on()) res |= mask;
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
