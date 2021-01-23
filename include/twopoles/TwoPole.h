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
// Base class for all kinds of two-poles (e.g.
// voltage/current sources or resistors and diodes).
//
#ifndef _INCLUDE_TWOPOLE_H_
#define _INCLUDE_TWOPOLE_H_

#include "Part.h"
#include "Pin.h"
#include "Narray.h"

class TwoPole : public Part {
public:

    TwoPole(const std::string & name) : Part(name), NAME(p) {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
        // Attach handlers
        p[1].attach([this](NetSet * nets) {
            NetPtr net = p[1].getNetPtr();
            // Set voltage
            if (net) {
                // Alternative :
//                p[2].Ud = net->U;
//                p[2].Gd = G;
                float gw = net->Gi - p[1].Gd;
                if (net->Gi == INF || p[1].Gd == 0.0 || gw == 0.0){
                    p[2].Ud = net->U;
                } else {
                    p[2].Ud = (net->Is - p[1].Ud * p[1].Gd - p[1].Id) / gw;
                }
                p[2].Gd = 1.0/(1.0/gw + 1.0/G);
            } else {
                p[2].Ud = p[1].Ud;
                p[2].Gd = p[1].Gd;
            }
            _p1_changed(nets);
        });

        p[2].attach([this](NetSet * nets) {
            NetPtr net = p[2].getNetPtr();
            // Set voltage
            if (net) {
//                p[1].Ud = net->U;
//                p[1].Gd = G;
                float gw = net->Gi - p[2].Gd;
                if (net->Gi == INF || p[2].Gd == 0.0 || gw == 0.0){
                    p[1].Ud = net->U;
                } else {
                    p[1].Ud = (net->Is - p[2].Ud * p[2].Gd - p[2].Id) / gw;
                }
                p[1].Gd = 1.0/(1.0/gw + 1.0/G);
            } else {
                p[1].Ud = p[2].Ud;
                p[1].Gd = p[2].Gd;
            }
            _p2_changed(nets);
        });
    }

    virtual ~TwoPole() {
    }

    virtual void p1_changed() {}
    virtual void p2_changed() {}

    void _p1_changed(NetSet * nets) {
        p1_changed();
        NetPtr n = p[2].getNetPtr();
        if (n) nets->insert(n);
    };

    void _p2_changed(NetSet * nets) {
        p2_changed();
        NetPtr n = p[1].getNetPtr();
        if (n) nets->insert(n);
    };


//protected:
    Narray<Pin, 3> p;

    float G;
};

#endif // _INCLUDE_TWOPOLE_H_
