/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
#include "Computer.h"
#include <utility>

Computer::Computer(std::string name) : _8bit_computer(std::move(name)) ,
    STEP     (STEP1),
    CLK_MODE (CLK_MODE1),
    STORE    (STORE1),
    DATA     (DATA1),
    PRGM_MODE(PRGM_MODE1),
    ADDR     (ADDR1),
    OUT_MODE (OUT_MODE1),
    RESET    (RESET1),
    BUS  ({ &D8,  &D7,  &D6,  &D5,  &D4,  &D3,  &D2 , &D1  }),
    A    ({ &D67, &D66, &D65, &D64, &D63, &D62, &D61, &D60 }),
    B    ({ &D75, &D74, &D73, &D72, &D71, &D70, &D69, &D68 }),
    IR   ({ &D54, &D53, &D52, &D51, &D50, &D49, &D48, &D47 }),
    CF   ( D76 ),
    ZF   ( D77 ),
    ALU  ({ &D85, &D84, &D83, &D82, &D81, &D80, &D79, &D78 }),
    RAM  ({ &D46, &D45, &D44, &D43, &D42, &D41, &D40, &D39 }),
    MAR  ({ &D38, &D37, &D36, &D35 }),
    PC   ({ &D59, &D58, &D57, &D56 }),
    MS   ({ &D16, &D15, &D14 }),
    CTRL ({ &D32, &D31, &D30, &D29, &D28, &D27, &D26, &D25,
            &D24, &D23, &D22, &D21, &D20, &D19, &D18, &D17 })
{
}

ostream & operator <<(ostream & os, const Computer & c) {
    if (c.MS ==0) os << endl; // Print a newline before every new instruction
    os << "MS:"     << dec << setw(1) << setfill('0') << (unsigned int)c.MS   << " ";
    os << "CTRL:0x" << hex << setw(4) << setfill('0') << (unsigned int)c.CTRL << " ";
    os << "IR:0x"   << hex << setw(2) << setfill('0') << (unsigned int)c.IR   << "  ";
    os << "MAR:0x"  << hex << setw(1) << setfill('0') << (unsigned int)c.MAR  << " ";
    os << "RAM:0x"  << hex << setw(2) << setfill('0') << (unsigned int)c.RAM  << "  ";
    os << "ALU:0x"  << hex << setw(2) << setfill('0') << (unsigned int)c.ALU  << " ";
    os << "BUS:0x"  << hex << setw(2) << setfill('0') << (unsigned int)c.BUS  << "  ";
    os << "PC:0x"   << hex << setw(1) << setfill('0') << (unsigned int)c.PC   << " ";
    os << "A:0x"    << hex << setw(2) << setfill('0') << (unsigned int)c.A    << " ";
    os << "B:0x"    << hex << setw(2) << setfill('0') << (unsigned int)c.B    << " ";
    os << "CF:"     << c.CF.on() << " ";
    os << "ZF:"     << c.ZF.on() << "  ";
    os << "OUT:'"   << c.Display << "'";
    
    // Output disassembly after first micro step
    if (c.MS == 0) {
        os << "  ";
        switch(c.RAM & 0xf0) {
            case 0x00: cout << "NOP"; break;
            case 0x10: cout << "LDA (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x20: cout << "ADD (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x30: cout << "SUB (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x40: cout << "STA (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x50: cout << "LDI (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x60: cout << "JMP (" << dec << (c.RAM & 0xf) << ")"; break;
            case 0x70: cout << "JC ("  << dec << (c.RAM & 0xf) << ")"; break;
            case 0x80: cout << "JZ ("  << dec << (c.RAM & 0xf) << ")"; break;
            case 0xE0: cout << "OUT"; break;
            case 0xF0: cout << "HLT"; break;
            default:   cout << "???"; break;
        }
    }
    return os;
}

