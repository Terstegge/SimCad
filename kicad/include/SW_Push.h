#ifndef _SW_Push_H_
#define _SW_Push_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class SW_Push : public Named {

public:
    Narray<Pin, 3> p;
    bool  is_on  = false;
    Pin * nc_pin = nullptr;

    SW_Push(const string & name="") :
        Named(name), NAME(p)
    {
    }

    void PRESS() {
    	if (is_on) return;
    	is_on = true;
    	if ((State)p[1] != NC) {
    		p[2]   = (State)p[1];
    		nc_pin = &p[2];
    	} else if ((State)p[2] != NC) {
    		p[1]   = (State)p[2];
    		nc_pin = &p[1];
    	}
    }

    void RELEASE() {
    	if (!is_on) return;
    	is_on   = false;
    	*nc_pin = NC;
    }

};

#endif // _SW_Push_H_
