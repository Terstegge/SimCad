#ifndef _LED_H_
#define _LED_H_

#include "_1N4148.h"

class LED : public _1N4148 {
public:
    LED(const string & name="") : _1N4148(name) { }
    
    bool on() {
        return A.getNet()->getCurrent() || K.getNet()->getCurrent();
    }

};

#endif // _LED_H_
