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
// Low-level implementation of a resistor, which
// will propagate a state change as the respective
// weak state to the 'other' side.
//
#ifndef _R_H_
#define _R_H_

#include "TwoPole.h"

#include <iostream>
using namespace std;

class R : public TwoPole {

public:
    R(const string & name, float r) : TwoPole(name, r)
    {
        // Attach handlers
        p[1].attach([this](NetSet * nets) {
            handler(p[1], p[2], nets);
        });
        p[2].attach([this](NetSet * nets) {
            handler(p[2], p[1], nets);
        });
    }

    void handler(Pin & local, Pin & remote, NetSet * nets) {
        State local_s = local.getInpState();
        // Set the resistance and report it to 'other' side
        if (local_s  != NC) local_s.setR( TP_R );
        if (_name == "CNT.R19" || _name == "CNT.R20" || _name == "CNT.R21")
        cout << "------------------ Driving " << remote.getName() << "to " << local_s << endl;
        remote.setDrvState( local_s, nets );
    }




    // Get Equivalent Voltage Source (EVS)
    static State getEVS(Pin * pin) {
        float G = 0.0;
        float Ik = 0.0;

        // Step into the net
        NetPtr net = pin->getNet();
        for (Pin * pp : net->_pins) {
//            if (pp->getName() == "CNT.R19.p[2]") cout << "foo" << endl;
            // Skip over entry Pin
            if (pp == pin)  continue;
            // Immediately return strong Pins
            State s = pp->getDrvState();
            if (s.isStrong()) return s;
            // Only process TwoPoles
            Part * part = pp->getPartPtr();
            if (!part) continue;
            TwoPole * tp = dynamic_cast<TwoPole*>(part);
            if (!tp) continue;
            // Get other side of resistor
            Pin * other = tp->other(pp);
            // Skip TwoPols which are not driven remotely
            State other_s = other->getInpState();
//            if (pp->getName() == "CNT.R19.p[2]") cout << "foo2" << endl;

            if (other_s == NC) continue;

//            if (pp->getName() == "CNT.R19.p[2]") cout << "foo3" << endl;

            if (other_s.isStrong()) {
//                cout << "STRONG value!" << endl;
                float g = 1.0/(tp->TP_R);
                G  += g;
                Ik += g * other_s.getU();
            } else {
                // Normal processing
//                cout << "Normal value" << endl;
                State evs = getEVS(other);
                float g = 1.0 / (tp->TP_R + evs.getR());
                G  += g;
                Ik += g * evs.getU();
            }
        }
        State result;
        result.setNC(false);
        result.setR( 1. / G);
        result.setU( (Ik == 0.0 & G == 0.0) ? 0.0 : (Ik / G));
        return result;
    }

};

#endif // _R_H_



#if 0
            // Make sure the update is always only in
            // one direction during one transaction.
            if ((Net::_id == id) && (Net::_id != 0)) {
                if (_name == rn) cout << "p1 SKIPPED" << endl;
                return;
            }
            id = Net::_id;
#endif

#if 0
            // Make sure the update is always only in
            // one direction during one transaction.
            if ((Net::_id == id) && (Net::_id != 0)) {
                if (_name == rn) cout << "p2 SKIPPED" << endl;
                return;
            }
            id = Net::_id;

//        if (remote_s.isStrong()) {
//            if (_name == rn) cout << "Skip Strong..." << endl;
//            return;
//        }

//        if (_name == rn) cout << "A1:" << (local_s.getU() == remote_s.getU()) << endl;
//        if (_name == rn) cout << "A2:" << (fabs(local_s.getR() - remote_s.getR() - _val) < 1e-2) << endl;
//        if (_name == rn) cout << "A3:" << (remote.getDrvState() == NC) << endl;

//        State s = remote_s;
//        s.add_R(_val);
//        if (_name == rn) cout << "A3:" << s << local_s << endl;

//        if ( (local_s.getU() == remote_s.getU())  &&
//             (fabs(local_s.getR() - remote_s.getR() - _val) < 1e-2)  ) {  // NEU!
//        if ((local_s.getU() == remote_s.getU()) && (remote.getDrvState() == NC)) {
//            if (_name == rn) cout << "** Same voltage" << endl;
//            return;
//        }



#endif


#if 0
        if (remote_s == NC) {
            if (_name == rn) cout << "** NC!!!" << endl;
            // Other pin is not yet connected
            if (local_s != NC) local_s.setR(_val);  // add_R
            remote.setDrvState( local_s, nets );
            return;
        }


        if (_name == rn) cout << "** Normal" << endl;
        if (local_s != NC) local_s.setR(_val ); // setR
        remote.setDrvState( local_s, nets );
#endif
