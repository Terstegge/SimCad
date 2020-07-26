//
// This file was generated with ** Net2Sim **!
// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN!
//
#ifndef _ALU_H_
#define _ALU_H_

#include <string>
#include "Pin.h"
#include "Bus.h"
#include "_74LS153.h"	// 19 parts
#include "_74LS157.h"	// 3 parts
#include "_74LS283.h"	// 3 parts

class ALU {
private:
    _74LS153	U1;
    _74LS283	U2;
    _74LS153	U3;
    _74LS153	U4;
    _74LS157	U5;
    _74LS153	U6;
    _74LS153	U7;
    _74LS283	U8;
    _74LS153	U9;
    _74LS153	U10;
    _74LS157	U11;
    _74LS153	U12;
    _74LS153	U13;
    _74LS283	U14;
    _74LS153	U15;
    _74LS153	U16;
    _74LS157	U17;
    _74LS153	U18;
    _74LS153	U19;
    _74LS153	U20;
    _74LS153	U21;
    _74LS153	U22;
    _74LS153	U23;
    _74LS153	U24;
    _74LS153	U25;

public:
    Pin  	ADD;
    Bus<4>	ALU_4bit_0_ADD_OUT;
    Bus<4>	ALU_4bit_0_LOG_OUT;
    Bus<4>	ALU_4bit_1_ADD_OUT;
    Pin  	ALU_4bit_1_CARRY_IN;
    Bus<4>	ALU_4bit_1_LOG_OUT;
    Bus<4>	ALU_4bit_2_ADD_OUT;
    Pin  	ALU_4bit_2_CARRY_IN;
    Bus<4>	ALU_4bit_2_LOG_OUT;
    Bus<4>	ALU_OUT_0_;
    Bus<4>	ALU_OUT_1_;
    Bus<4>	ALU_OUT_2_;
    Pin  	BIT_IN;
    Pin  	CARRY_OUT;
    Bus<12>	DATA_IN;
    Pin  	GND;
    Pin  	SHIFT_OUT;
    Pin  	VCC;
    Bus<12>	_CTRL_D;
    Bus<12>	_MEM_MEM_IN;
    Bus<12>	_MEM_MEM_OUT;

    ALU(std::string n) :
        U1("U1"),
        U2("U2"),
        U3("U3"),
        U4("U4"),
        U5("U5"),
        U6("U6"),
        U7("U7"),
        U8("U8"),
        U9("U9"),
        U10("U10"),
        U11("U11"),
        U12("U12"),
        U13("U13"),
        U14("U14"),
        U15("U15"),
        U16("U16"),
        U17("U17"),
        U18("U18"),
        U19("U19"),
        U20("U20"),
        U21("U21"),
        U22("U22"),
        U23("U23"),
        U24("U24"),
        U25("U25")
    {
        ADD.connect_to(U11.p[1]);
        ADD.connect_to(U17.p[1]);
        ADD.connect_to(U5.p[1]);
        ALU_4bit_0_ADD_OUT[0].connect_to(U14.p[4]);
        ALU_4bit_0_ADD_OUT[0].connect_to(U17.p[3]);
        ALU_4bit_0_ADD_OUT[1].connect_to(U14.p[1]);
        ALU_4bit_0_ADD_OUT[1].connect_to(U17.p[6]);
        ALU_4bit_0_ADD_OUT[2].connect_to(U14.p[13]);
        ALU_4bit_0_ADD_OUT[2].connect_to(U17.p[10]);
        ALU_4bit_0_ADD_OUT[3].connect_to(U14.p[10]);
        ALU_4bit_0_ADD_OUT[3].connect_to(U17.p[13]);
        ALU_4bit_0_LOG_OUT[0].connect_to(U13.p[7]);
        ALU_4bit_0_LOG_OUT[0].connect_to(U14.p[6]);
        ALU_4bit_0_LOG_OUT[0].connect_to(U17.p[2]);
        ALU_4bit_0_LOG_OUT[1].connect_to(U14.p[2]);
        ALU_4bit_0_LOG_OUT[1].connect_to(U15.p[7]);
        ALU_4bit_0_LOG_OUT[1].connect_to(U17.p[5]);
        ALU_4bit_0_LOG_OUT[2].connect_to(U14.p[15]);
        ALU_4bit_0_LOG_OUT[2].connect_to(U16.p[7]);
        ALU_4bit_0_LOG_OUT[2].connect_to(U17.p[11]);
        ALU_4bit_0_LOG_OUT[3].connect_to(U14.p[11]);
        ALU_4bit_0_LOG_OUT[3].connect_to(U17.p[14]);
        ALU_4bit_0_LOG_OUT[3].connect_to(U18.p[7]);
        ALU_4bit_1_ADD_OUT[0].connect_to(U2.p[4]);
        ALU_4bit_1_ADD_OUT[0].connect_to(U5.p[3]);
        ALU_4bit_1_ADD_OUT[1].connect_to(U2.p[1]);
        ALU_4bit_1_ADD_OUT[1].connect_to(U5.p[6]);
        ALU_4bit_1_ADD_OUT[2].connect_to(U2.p[13]);
        ALU_4bit_1_ADD_OUT[2].connect_to(U5.p[10]);
        ALU_4bit_1_ADD_OUT[3].connect_to(U2.p[10]);
        ALU_4bit_1_ADD_OUT[3].connect_to(U5.p[13]);
        ALU_4bit_1_CARRY_IN.connect_to(U14.p[9]);
        ALU_4bit_1_CARRY_IN.connect_to(U2.p[7]);
        ALU_4bit_1_LOG_OUT[0].connect_to(U1.p[7]);
        ALU_4bit_1_LOG_OUT[0].connect_to(U2.p[6]);
        ALU_4bit_1_LOG_OUT[0].connect_to(U5.p[2]);
        ALU_4bit_1_LOG_OUT[1].connect_to(U2.p[2]);
        ALU_4bit_1_LOG_OUT[1].connect_to(U3.p[7]);
        ALU_4bit_1_LOG_OUT[1].connect_to(U5.p[5]);
        ALU_4bit_1_LOG_OUT[2].connect_to(U2.p[15]);
        ALU_4bit_1_LOG_OUT[2].connect_to(U4.p[7]);
        ALU_4bit_1_LOG_OUT[2].connect_to(U5.p[11]);
        ALU_4bit_1_LOG_OUT[3].connect_to(U2.p[11]);
        ALU_4bit_1_LOG_OUT[3].connect_to(U5.p[14]);
        ALU_4bit_1_LOG_OUT[3].connect_to(U6.p[7]);
        ALU_4bit_2_ADD_OUT[0].connect_to(U11.p[3]);
        ALU_4bit_2_ADD_OUT[0].connect_to(U8.p[4]);
        ALU_4bit_2_ADD_OUT[1].connect_to(U11.p[6]);
        ALU_4bit_2_ADD_OUT[1].connect_to(U8.p[1]);
        ALU_4bit_2_ADD_OUT[2].connect_to(U11.p[10]);
        ALU_4bit_2_ADD_OUT[2].connect_to(U8.p[13]);
        ALU_4bit_2_ADD_OUT[3].connect_to(U11.p[13]);
        ALU_4bit_2_ADD_OUT[3].connect_to(U8.p[10]);
        ALU_4bit_2_CARRY_IN.connect_to(U2.p[9]);
        ALU_4bit_2_CARRY_IN.connect_to(U8.p[7]);
        ALU_4bit_2_LOG_OUT[0].connect_to(U11.p[2]);
        ALU_4bit_2_LOG_OUT[0].connect_to(U7.p[7]);
        ALU_4bit_2_LOG_OUT[0].connect_to(U8.p[6]);
        ALU_4bit_2_LOG_OUT[1].connect_to(U11.p[5]);
        ALU_4bit_2_LOG_OUT[1].connect_to(U8.p[2]);
        ALU_4bit_2_LOG_OUT[1].connect_to(U9.p[7]);
        ALU_4bit_2_LOG_OUT[2].connect_to(U10.p[7]);
        ALU_4bit_2_LOG_OUT[2].connect_to(U11.p[11]);
        ALU_4bit_2_LOG_OUT[2].connect_to(U8.p[15]);
        ALU_4bit_2_LOG_OUT[3].connect_to(U11.p[14]);
        ALU_4bit_2_LOG_OUT[3].connect_to(U12.p[7]);
        ALU_4bit_2_LOG_OUT[3].connect_to(U8.p[11]);
        ALU_OUT_0_[0].connect_to(U17.p[4]);
        ALU_OUT_0_[0].connect_to(U19.p[11]);
        ALU_OUT_0_[0].connect_to(U19.p[6]);
        ALU_OUT_0_[0].connect_to(U20.p[3]);
        ALU_OUT_0_[0].connect_to(U25.p[4]);
        ALU_OUT_0_[1].connect_to(U17.p[7]);
        ALU_OUT_0_[1].connect_to(U19.p[10]);
        ALU_OUT_0_[1].connect_to(U19.p[4]);
        ALU_OUT_0_[1].connect_to(U20.p[13]);
        ALU_OUT_0_[1].connect_to(U21.p[5]);
        ALU_OUT_0_[2].connect_to(U17.p[9]);
        ALU_OUT_0_[2].connect_to(U19.p[12]);
        ALU_OUT_0_[2].connect_to(U21.p[11]);
        ALU_OUT_0_[2].connect_to(U21.p[6]);
        ALU_OUT_0_[2].connect_to(U22.p[3]);
        ALU_OUT_0_[3].connect_to(U17.p[12]);
        ALU_OUT_0_[3].connect_to(U21.p[10]);
        ALU_OUT_0_[3].connect_to(U21.p[4]);
        ALU_OUT_0_[3].connect_to(U22.p[13]);
        ALU_OUT_0_[3].connect_to(U23.p[5]);
        ALU_OUT_1_[0].connect_to(U21.p[12]);
        ALU_OUT_1_[0].connect_to(U23.p[11]);
        ALU_OUT_1_[0].connect_to(U23.p[6]);
        ALU_OUT_1_[0].connect_to(U24.p[3]);
        ALU_OUT_1_[0].connect_to(U5.p[4]);
        ALU_OUT_1_[1].connect_to(U20.p[5]);
        ALU_OUT_1_[1].connect_to(U23.p[10]);
        ALU_OUT_1_[1].connect_to(U23.p[4]);
        ALU_OUT_1_[1].connect_to(U24.p[13]);
        ALU_OUT_1_[1].connect_to(U5.p[7]);
        ALU_OUT_1_[2].connect_to(U19.p[3]);
        ALU_OUT_1_[2].connect_to(U20.p[11]);
        ALU_OUT_1_[2].connect_to(U20.p[6]);
        ALU_OUT_1_[2].connect_to(U23.p[12]);
        ALU_OUT_1_[2].connect_to(U5.p[9]);
        ALU_OUT_1_[3].connect_to(U19.p[13]);
        ALU_OUT_1_[3].connect_to(U20.p[10]);
        ALU_OUT_1_[3].connect_to(U20.p[4]);
        ALU_OUT_1_[3].connect_to(U22.p[5]);
        ALU_OUT_1_[3].connect_to(U5.p[12]);
        ALU_OUT_2_[0].connect_to(U11.p[4]);
        ALU_OUT_2_[0].connect_to(U20.p[12]);
        ALU_OUT_2_[0].connect_to(U21.p[3]);
        ALU_OUT_2_[0].connect_to(U22.p[11]);
        ALU_OUT_2_[0].connect_to(U22.p[6]);
        ALU_OUT_2_[1].connect_to(U11.p[7]);
        ALU_OUT_2_[1].connect_to(U21.p[13]);
        ALU_OUT_2_[1].connect_to(U22.p[10]);
        ALU_OUT_2_[1].connect_to(U22.p[4]);
        ALU_OUT_2_[1].connect_to(U24.p[5]);
        ALU_OUT_2_[2].connect_to(U11.p[9]);
        ALU_OUT_2_[2].connect_to(U22.p[12]);
        ALU_OUT_2_[2].connect_to(U23.p[3]);
        ALU_OUT_2_[2].connect_to(U24.p[11]);
        ALU_OUT_2_[2].connect_to(U24.p[6]);
        ALU_OUT_2_[3].connect_to(U11.p[12]);
        ALU_OUT_2_[3].connect_to(U23.p[13]);
        ALU_OUT_2_[3].connect_to(U24.p[10]);
        ALU_OUT_2_[3].connect_to(U24.p[4]);
        ALU_OUT_2_[3].connect_to(U25.p[5]);
        BIT_IN.connect_to(U14.p[7]);
        BIT_IN.connect_to(U19.p[5]);
        BIT_IN.connect_to(U24.p[12]);
        BIT_IN.connect_to(U25.p[3]);
        BIT_IN.connect_to(U25.p[6]);
        CARRY_OUT.connect_to(U8.p[9]);
        DATA_IN[0].connect_to(U13.p[2]);
        DATA_IN[10].connect_to(U10.p[2]);
        DATA_IN[11].connect_to(U12.p[2]);
        DATA_IN[1].connect_to(U15.p[2]);
        DATA_IN[2].connect_to(U16.p[2]);
        DATA_IN[3].connect_to(U18.p[2]);
        DATA_IN[4].connect_to(U1.p[2]);
        DATA_IN[5].connect_to(U3.p[2]);
        DATA_IN[6].connect_to(U4.p[2]);
        DATA_IN[7].connect_to(U6.p[2]);
        DATA_IN[8].connect_to(U7.p[2]);
        DATA_IN[9].connect_to(U9.p[2]);
        GND.connect_to(U1.p[1]);
        GND.connect_to(U1.p[8]);
        GND.connect_to(U10.p[1]);
        GND.connect_to(U10.p[8]);
        GND.connect_to(U11.p[15]);
        GND.connect_to(U11.p[8]);
        GND.connect_to(U12.p[1]);
        GND.connect_to(U12.p[8]);
        GND.connect_to(U13.p[1]);
        GND.connect_to(U13.p[8]);
        GND.connect_to(U14.p[8]);
        GND.connect_to(U15.p[1]);
        GND.connect_to(U15.p[8]);
        GND.connect_to(U16.p[1]);
        GND.connect_to(U16.p[8]);
        GND.connect_to(U17.p[15]);
        GND.connect_to(U17.p[8]);
        GND.connect_to(U18.p[1]);
        GND.connect_to(U18.p[8]);
        GND.connect_to(U19.p[15]);
        GND.connect_to(U19.p[1]);
        GND.connect_to(U19.p[8]);
        GND.connect_to(U2.p[8]);
        GND.connect_to(U20.p[15]);
        GND.connect_to(U20.p[1]);
        GND.connect_to(U20.p[8]);
        GND.connect_to(U21.p[15]);
        GND.connect_to(U21.p[1]);
        GND.connect_to(U21.p[8]);
        GND.connect_to(U22.p[15]);
        GND.connect_to(U22.p[1]);
        GND.connect_to(U22.p[8]);
        GND.connect_to(U23.p[15]);
        GND.connect_to(U23.p[1]);
        GND.connect_to(U23.p[8]);
        GND.connect_to(U24.p[15]);
        GND.connect_to(U24.p[1]);
        GND.connect_to(U24.p[8]);
        GND.connect_to(U25.p[1]);
        GND.connect_to(U25.p[8]);
        GND.connect_to(U3.p[1]);
        GND.connect_to(U3.p[8]);
        GND.connect_to(U4.p[1]);
        GND.connect_to(U4.p[8]);
        GND.connect_to(U5.p[15]);
        GND.connect_to(U5.p[8]);
        GND.connect_to(U6.p[1]);
        GND.connect_to(U6.p[8]);
        GND.connect_to(U7.p[1]);
        GND.connect_to(U7.p[8]);
        GND.connect_to(U8.p[8]);
        GND.connect_to(U9.p[1]);
        GND.connect_to(U9.p[8]);
        SHIFT_OUT.connect_to(U25.p[7]);
        VCC.connect_to(U1.p[16]);
        VCC.connect_to(U10.p[16]);
        VCC.connect_to(U11.p[16]);
        VCC.connect_to(U12.p[16]);
        VCC.connect_to(U13.p[16]);
        VCC.connect_to(U14.p[16]);
        VCC.connect_to(U15.p[16]);
        VCC.connect_to(U16.p[16]);
        VCC.connect_to(U17.p[16]);
        VCC.connect_to(U18.p[16]);
        VCC.connect_to(U19.p[16]);
        VCC.connect_to(U2.p[16]);
        VCC.connect_to(U20.p[16]);
        VCC.connect_to(U21.p[16]);
        VCC.connect_to(U22.p[16]);
        VCC.connect_to(U23.p[16]);
        VCC.connect_to(U24.p[16]);
        VCC.connect_to(U25.p[16]);
        VCC.connect_to(U3.p[16]);
        VCC.connect_to(U4.p[16]);
        VCC.connect_to(U5.p[16]);
        VCC.connect_to(U6.p[16]);
        VCC.connect_to(U7.p[16]);
        VCC.connect_to(U8.p[16]);
        VCC.connect_to(U9.p[16]);
        _CTRL_D[10].connect_to(U19.p[14]);
        _CTRL_D[10].connect_to(U20.p[14]);
        _CTRL_D[10].connect_to(U21.p[14]);
        _CTRL_D[10].connect_to(U22.p[14]);
        _CTRL_D[10].connect_to(U23.p[14]);
        _CTRL_D[10].connect_to(U24.p[14]);
        _CTRL_D[10].connect_to(U25.p[14]);
        _CTRL_D[11].connect_to(U19.p[2]);
        _CTRL_D[11].connect_to(U20.p[2]);
        _CTRL_D[11].connect_to(U21.p[2]);
        _CTRL_D[11].connect_to(U22.p[2]);
        _CTRL_D[11].connect_to(U23.p[2]);
        _CTRL_D[11].connect_to(U24.p[2]);
        _CTRL_D[11].connect_to(U25.p[2]);
        _CTRL_D[6].connect_to(U1.p[6]);
        _CTRL_D[6].connect_to(U10.p[6]);
        _CTRL_D[6].connect_to(U12.p[6]);
        _CTRL_D[6].connect_to(U13.p[6]);
        _CTRL_D[6].connect_to(U15.p[6]);
        _CTRL_D[6].connect_to(U16.p[6]);
        _CTRL_D[6].connect_to(U18.p[6]);
        _CTRL_D[6].connect_to(U3.p[6]);
        _CTRL_D[6].connect_to(U4.p[6]);
        _CTRL_D[6].connect_to(U6.p[6]);
        _CTRL_D[6].connect_to(U7.p[6]);
        _CTRL_D[6].connect_to(U9.p[6]);
        _CTRL_D[7].connect_to(U1.p[5]);
        _CTRL_D[7].connect_to(U10.p[5]);
        _CTRL_D[7].connect_to(U12.p[5]);
        _CTRL_D[7].connect_to(U13.p[5]);
        _CTRL_D[7].connect_to(U15.p[5]);
        _CTRL_D[7].connect_to(U16.p[5]);
        _CTRL_D[7].connect_to(U18.p[5]);
        _CTRL_D[7].connect_to(U3.p[5]);
        _CTRL_D[7].connect_to(U4.p[5]);
        _CTRL_D[7].connect_to(U6.p[5]);
        _CTRL_D[7].connect_to(U7.p[5]);
        _CTRL_D[7].connect_to(U9.p[5]);
        _CTRL_D[8].connect_to(U1.p[4]);
        _CTRL_D[8].connect_to(U10.p[4]);
        _CTRL_D[8].connect_to(U12.p[4]);
        _CTRL_D[8].connect_to(U13.p[4]);
        _CTRL_D[8].connect_to(U15.p[4]);
        _CTRL_D[8].connect_to(U16.p[4]);
        _CTRL_D[8].connect_to(U18.p[4]);
        _CTRL_D[8].connect_to(U3.p[4]);
        _CTRL_D[8].connect_to(U4.p[4]);
        _CTRL_D[8].connect_to(U6.p[4]);
        _CTRL_D[8].connect_to(U7.p[4]);
        _CTRL_D[8].connect_to(U9.p[4]);
        _CTRL_D[9].connect_to(U1.p[3]);
        _CTRL_D[9].connect_to(U10.p[3]);
        _CTRL_D[9].connect_to(U12.p[3]);
        _CTRL_D[9].connect_to(U13.p[3]);
        _CTRL_D[9].connect_to(U15.p[3]);
        _CTRL_D[9].connect_to(U16.p[3]);
        _CTRL_D[9].connect_to(U18.p[3]);
        _CTRL_D[9].connect_to(U3.p[3]);
        _CTRL_D[9].connect_to(U4.p[3]);
        _CTRL_D[9].connect_to(U6.p[3]);
        _CTRL_D[9].connect_to(U7.p[3]);
        _CTRL_D[9].connect_to(U9.p[3]);
        _MEM_MEM_IN[0].connect_to(U19.p[7]);
        _MEM_MEM_IN[10].connect_to(U24.p[7]);
        _MEM_MEM_IN[11].connect_to(U24.p[9]);
        _MEM_MEM_IN[1].connect_to(U19.p[9]);
        _MEM_MEM_IN[2].connect_to(U21.p[7]);
        _MEM_MEM_IN[3].connect_to(U21.p[9]);
        _MEM_MEM_IN[4].connect_to(U23.p[7]);
        _MEM_MEM_IN[5].connect_to(U23.p[9]);
        _MEM_MEM_IN[6].connect_to(U20.p[7]);
        _MEM_MEM_IN[7].connect_to(U20.p[9]);
        _MEM_MEM_IN[8].connect_to(U22.p[7]);
        _MEM_MEM_IN[9].connect_to(U22.p[9]);
        _MEM_MEM_OUT[0].connect_to(U13.p[14]);
        _MEM_MEM_OUT[0].connect_to(U14.p[5]);
        _MEM_MEM_OUT[10].connect_to(U10.p[14]);
        _MEM_MEM_OUT[10].connect_to(U8.p[14]);
        _MEM_MEM_OUT[11].connect_to(U12.p[14]);
        _MEM_MEM_OUT[11].connect_to(U8.p[12]);
        _MEM_MEM_OUT[1].connect_to(U14.p[3]);
        _MEM_MEM_OUT[1].connect_to(U15.p[14]);
        _MEM_MEM_OUT[2].connect_to(U14.p[14]);
        _MEM_MEM_OUT[2].connect_to(U16.p[14]);
        _MEM_MEM_OUT[3].connect_to(U14.p[12]);
        _MEM_MEM_OUT[3].connect_to(U18.p[14]);
        _MEM_MEM_OUT[4].connect_to(U1.p[14]);
        _MEM_MEM_OUT[4].connect_to(U2.p[5]);
        _MEM_MEM_OUT[5].connect_to(U2.p[3]);
        _MEM_MEM_OUT[5].connect_to(U3.p[14]);
        _MEM_MEM_OUT[6].connect_to(U2.p[14]);
        _MEM_MEM_OUT[6].connect_to(U4.p[14]);
        _MEM_MEM_OUT[7].connect_to(U2.p[12]);
        _MEM_MEM_OUT[7].connect_to(U6.p[14]);
        _MEM_MEM_OUT[8].connect_to(U7.p[14]);
        _MEM_MEM_OUT[8].connect_to(U8.p[5]);
        _MEM_MEM_OUT[9].connect_to(U8.p[3]);
        _MEM_MEM_OUT[9].connect_to(U9.p[14]);
    }
};

#endif	// _ALU_H_
