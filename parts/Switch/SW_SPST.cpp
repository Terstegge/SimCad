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
#include "SW_SPST.h"

SW_SPST::SW_SPST(const std::string & name) : R(name, INF) {
}

void SW_SPST::setOn(bool b) {
	_R = b ? 0 : INF;
	update();
}

void SW_SPST::toggle() {
	setOn(true);
	setOn(false);
}
