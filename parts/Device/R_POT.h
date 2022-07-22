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
#ifndef _R_POT_H_
#define _R_POT_H_

#include "R_POT_skel.h"

class R_POT : public R_POT_skel {
public:
    R_POT(std::string name, double r);
    void setPercent(double p);
    
private:
    double	_R_tot;
};

#endif	// _R_POT_H_
