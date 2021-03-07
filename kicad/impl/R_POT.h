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
