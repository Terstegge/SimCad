#include "R_POT.h"

#include <iostream>
using namespace std;

R_POT::R_POT(std::string name, double r) : R_POT_skel(name), _R_tot(r) {
    setPercent(50);
}

void R_POT::setPercent(double p) {
    // Check percent values
    if (p > 100.0) p = 100.0;
    if (p <   0.0) p =   0.0;

    // Set R values without updating
    R1._R = (100.0 - p) / 100.0 * _R_tot;
    R2._R = (        p) / 100.0 * _R_tot;

    R1.update();
    R2.update();
}

