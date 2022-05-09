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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#include "SW_SPDT.h"


SW_SPDT::SW_SPDT(const std::string & name) : SW_SPDT_skel(name) {
}

void SW_SPDT::set(int c) {
	switch(c) {
	case con21: {
		if (R21._R == 0.0) {
			return;
		} else {
			R23._R = INF;
			R21._R = 0.0;
			R21.update();
			R23.update();
		}
		break;
	}
	case con23:
		if (R23._R == 0.0) {
			return;
		} else {
			R21._R = INF;
			R23._R = 0.0;
			R21.update();
			R23.update();
		}
		break;
	}
}
