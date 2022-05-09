//
// !This file was generated with ** Net2Sim **!
// !DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN!
//
#ifndef __74LS245_H_
#define __74LS245_H_

#include <string>
#include "Pin.h"
#include "Bus.h"
#include "BUF_G.h"	// 16 parts
#include "INH.h"	// 1 parts
#include "NOR.h"	// 1 parts
#include "R.h"		// 2 parts

class _74LS245 {
public:
    // Components
    R		R1;
    R		R2;
    BUF_G	U1;
    BUF_G	U2;
    BUF_G	U3;
    BUF_G	U4;
    BUF_G	U5;
    BUF_G	U6;
    BUF_G	U7;
    BUF_G	U8;
    INH<2>	U9;
    NOR<2>	U10;
    BUF_G	U11;
    BUF_G	U12;
    BUF_G	U13;
    BUF_G	U14;
    BUF_G	U15;
    BUF_G	U16;
    BUF_G	U17;
    BUF_G	U18;
    // Nets
    Pin  	Net__R1_Pad1_;
    Pin  	Net__R2_Pad2_;
    Bus<21>	p;

public:
    _74LS245(std::string name);
};

#endif	// __74LS245_H_
