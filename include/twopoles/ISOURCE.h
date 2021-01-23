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
// A generic voltage source for simulation.
// p[1] is the negative pin.
// p[2] is the positive pin,
//
#ifndef INCLUDE_ISOURCE_H_
#define INCLUDE_ISOURCE_H_

#include "TwoPole.h"

class ISOURCE : public TwoPole {
public:

    ISOURCE(const std::string & name, float i) : TwoPole(name) {
        this->G = 0;
//        p[1].Id =  i;
//        p[2].Id = -i;
    }

};

#endif /* INCLUDE_VSOURCE_H_ */
