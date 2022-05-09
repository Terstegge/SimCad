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
#include "_7SEGMENT_CC.h"

_7SEGMENT_CC::_7SEGMENT_CC(std::string name) : _7SEGMENT_CC_skel(name),
	_value( { &G1, &F1, &E1, &D1, &C1, &B1, &A1, &DP1 } )
{
}

std::ostream & operator << (std::ostream & os, const _7SEGMENT_CC & d) {
	char c = '?';
	switch((int)d._value) {
		case 0x00: c = ' '; break;
		case 0x01: c = '-'; break;
		case 0x7e: c = '0'; break;
		case 0x30: c = '1'; break;
		case 0x6d: c = '2'; break;
		case 0x79: c = '3'; break;
		case 0x33: c = '4'; break;
		case 0x5b: c = '5'; break;
		case 0x5f: c = '6'; break;
		case 0x70: c = '7'; break;
		case 0x7f: c = '8'; break;
		case 0x7b: c = '9'; break;
	}
	os << c;
	return os;
}
