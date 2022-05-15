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

// Bit patterns for the digits 0..9
//
//      AAAAA
//     F     B
//     F     B
//      GGGGG
//     E     C
//     E     C
//      DDDDD   DP
//
//  Bit  |7|6|5|4|3|2|1|0|
//  -----+-+-+-+-+-+-+-+-+
//       DP A B C D E F G
//

_7SEGMENT_CC::_7SEGMENT_CC(std::string name) : _7SEGMENT_CC_skel(name),
_value( { &G1, &F1, &E1, &D1, &C1, &B1, &A1, &DP1 } )
{
}

char _7SEGMENT_CC::to_char() {
    char c = '?';
    switch((int)_value) {
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
        case 0x77: c = 'A'; break;
        case 0x1f: c = 'b'; break;
        case 0x4e: c = 'C'; break;
        case 0x3d: c = 'd'; break;
        case 0x4f: c = 'E'; break;
        case 0x47: c = 'F'; break;
    }
    return c;
}

std::ostream & operator << (std::ostream & os, _7SEGMENT_CC & d) {
    os << d.to_char();
    return os;
}
