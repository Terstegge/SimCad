#ifndef _SW_SPST_H_
#define _SW_SPST_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class SW_SPST : public Named {

public:
    Narray<Pin, 3> p;
    bool  is_on    = false;
    Pin * weak_pin = nullptr;

    SW_SPST(const string & name) : Named(name), NAME(p)
    {
    }

    void on() {
    	if (is_on) return;
    	is_on = true;
    	if (isStrong(p[1])) {
    	    weak_pin = &p[2];
    	    p[2]     = (State)p[1];
    	} else if (isStrong(p[2])) {
    	    weak_pin = &p[1];
    	    p[1]     = (State)p[2];
    	}
    }

    void off() {
    	if (!is_on) return;
    	is_on     = false;
    	*weak_pin = NC;
    }
};

#endif // _SW_SPST_H_
