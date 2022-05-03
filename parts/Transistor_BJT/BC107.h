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
#ifndef _INCLUDE_BC107_H_
#define _INCLUDE_BC107_H_

#include "Pin.h"
#include "Narray.h"

#include <iostream>
#include <string>
#include <cmath>

#include "_1N4148.h"
#include "R.h"

class BC107 : public Named {
public:
    Narray<Pin, 4> p;
    Pin &    B;
    Pin &    E;
    Pin &    C;

    BC107(const std::string & name)
    : Named(name), NAME(p),
      B(p[2]), E(p[1]), C(p[3]),
      NAME(_D_be), NAME(_R_ce, 50), calc(false)
    {
        // Setup the Basis-Emitter Diode
        B.connect_to(_D_be.A);
        E.connect_to(_D_be.C);
        // Setup Collector-Emitter Resistor
        C.connect_to(_R_ce.p[1]);
        E.connect_to(_R_ce.p[2]);

        // Attach handlers
        B.attach( [this](NetSet * nset) {
            calculate(nset);
        });
        E.attach( [this](NetSet * nset) {
            calculate(nset);
        });
        C.attach( [this](NetSet * nset) {
            calculate(nset);
        });
    }

    void calculate(NetSet * nset) {
        if (!calc) {
            calc = true;
            double Ib = _D_be.A.I();
            Ice_max   = Ib * beta;

            double Uce = C.U() - E.U();
            double Ice = _R_ce.p[1].I();

            if (Ice < 0.0) {
                _R_ce._R = 100000;
            } else if (Ice <= Ice_max) {
                _R_ce._R = 50;
            } else {
                _R_ce._R = Uce / Ice_max;
            }
            _R_ce.update();
            calc = false;
        } else {
            double Uce = C.U() - E.U();
            double Ice = _R_ce.p[1].I();

            if (fabs(Ice - Ice_max) < 1E-2) return;

            if (Ice < 0.0) {
                _R_ce._R = 100000;
            } else if (Ice <= Ice_max) {
                _R_ce._R = 50;
            } else {
                _R_ce._R = Uce / Ice_max;
            }
            C.update(nset);
            E.update(nset);
        }
    }

    //    	double Ib      = _D_be.A.I();
    //    	double Ice_max = Ib * beta;
    //    	double Uce_max = 50 * Ice_max;
    //
    //    	double Uce = C.U() - E.U();
    //    	double Ice = _R_ce.p[1].I();
    //
    ////    	cout << "Ib: " << Ib << "    Ice: " << Ice << endl;
    //
    //    	if (Ice < 0.0) {
    //    		_R_ce.setR(100000);
    //    	} else if (Ice <= Ice_max) {
    //    		_R_ce.setR(50);
    ////    		cout << getName() << " Rce set to" << 50 << endl ;
    //    	} else {
    //    		// double Rearly = (Uearly + Uce_max) / Ice_max;
    //    		double Rold = _R_ce.getR();
    //    		double Rnew = Uce / Ice_max; // (Ice_max + (Uce-Uce_max) / Rearly);
    //
    //    		if (fabs(Ice - Ice_max) > 1e-4) {
    ////        		cout << getName() << " Rce set to " << Rnew << endl ;
    //    			_R_ce.setR( Rnew );
    ////            	_R_ce.update();
    //    		}
    //    	}
    //
    ////    	cout << "Basis     current: " << Ib  << endl;
    ////    	cout << "Collector current: " << Ice << endl;
    //    }

private:
    _1N4148 _D_be;
    R       _R_ce;
    const double beta = 400;
    const double Uearly = 150;
    bool calc;
    double Ice_max;
};

#endif // _INCLUDE_BC107_H_
