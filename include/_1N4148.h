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
// Low-level implementation of a diode, which
// is simulated without a voltage drop:
// If current could flow (A is positive or K is
// negative), the state change is propagated to
// the respective 'other' side, setting both,
// A and K, to the same state.
//
#ifndef _1N4148_H_
#define _1N4148_H_

#include "TwoPole.h"
#include "R.h"

#include <iostream>
using namespace std;

class _1N4148 : public TwoPole {
public:
    Pin & K, & A;
    
    _1N4148(const string & name="") : TwoPole(name, R1), K(p[1]), A(p[2])
    {
        // Attach handlers
        K.attach([this](NetSet * nets) {
            k = K.getInpState();
            a = A.getInpState();
            cout << endl;
            cout << _name << " K handler ";
            cout << "A: " << a << " (EVS " << R::getEVS(&A) << ") ";
            cout << "K: " << k << " (EVS " << R::getEVS(&K) << ")";
            cout << endl;

            if (k == NC) return;

            if (a == NC)
            {
                k.setR( TP_R );
                A.setDrvState( k, nets);
                return;
            }

            if (calculate()) {
                if (k != NC) k.setR( TP_R );
                cout << "Setting A to " << k << endl;
                A.setDrvState( k, nets);

                if (K.getDrvState() == NC) {
                    if (a != NC) a.setR( TP_R );
                    K.setDrvState(a, nets);
                }

            } else {
                A.setDrvState( NC, nets);
            }            
        });
        A.attach([this](NetSet * nets) {
            k = K.getInpState();
            a = A.getInpState();
            cout << endl;
            cout << _name << " A handler ";
            cout << "A: " << a << " (EVS " << R::getEVS(&A) << ") ";
            cout << "K: " << k << " (EVS " << R::getEVS(&K) << ")";
            cout << endl;

            if (a == NC) return;

            if (k == NC)
            {
                a.setR( TP_R );
                K.setDrvState( a, nets);
                return;
            }



            if (calculate()) {
                if (a != NC) a.setR( TP_R );
                cout << "Setting K to " << a << endl;
                K.setDrvState( a, nets);

                if (A.getDrvState() == NC) {
                    if (k != NC) k.setR( TP_R );
                    A.setDrvState(k, nets);
                }

            } else {
                K.setDrvState( NC, nets);
            }
        });
    }

    bool calculate() {

        if (_name == "CNT.D1") cout << "CALC: " << a << " " << k << endl;

        State EVS_A = R::getEVS(&A);
        State EVS_K = R::getEVS(&K);

        float Ri = EVS_A.getR() + EVS_K.getR();
        float Ul = EVS_A.getU() - EVS_K.getU();

//        cout << "EVS A:" << R::getEVS(&A) << " EVS K:" <<  R::getEVS(&K) << endl;

        if (Ul < 0.0) return false;
        float Ik = Ul / Ri;
        
        // Check which resistance to use
        float Ir = Ik * (1 - Us/Ul);
        float Is = Us / R1;

//        cout << "Ir: " << Ir << " Is: " << Is << endl;

        if (Ir <= Is) {
            // Use R1 for voltages up to Us
            TP_R = R1;
            cout << "nonconductive R:" << TP_R << endl;
            return true;
        }
        
        float t = Us * (R2 - R1);
        TP_R  = R1 * R2 * Ik - t;
        TP_R /= R1 * Ri * Ik + t;
        TP_R *= Ri;

        cout << "normal! R:" << TP_R << endl;

        return true;
    }

private:
    State k;
    State a;
    // Diode configuration
    float R1 = 280;	// Resistance up to Us
    float R2 = 1;	// Resistance from Us on
    float Us = 0.7;	// Forward voltage
};

#endif // _1N4148_H_

