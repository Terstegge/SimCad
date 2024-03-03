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

Computer::Computer(std::string name) : _8bit_computer(name) ,
    STEP     (SW1),
    CLK_MODE (SW2),
    STORE    (SW3),
    DATA     (SW4),
    PRGM_MODE(SW5),
    ADDR     (SW6),
    OUT_MODE (SW7),
    RESET    (SW8),
    BUS  ({ &D8,  &D7,  &D6,  &D5,  &D4,  &D3,  &D2 , &D1  }),
    A    ({ &D17, &D16, &D15, &D14, &D13, &D12, &D11, &D10 }),
    B    ({ &D25, &D24, &D23, &D22, &D21, &D20, &D19, &D18 }),
    IR   ({ &D33, &D32, &D31, &D30, &D29, &D28, &D27, &D26 }),
    CF   ( D34 ),
    ZF   ( D35 ),
    ALU  ({ &D43, &D42, &D41, &D40, &D39, &D38, &D37, &D36 }),
    RAM  ({ &D51, &D50, &D49, &D48, &D47, &D46, &D45, &D44 }),
    MAR  ({ &D57, &D56, &D55, &D54 }),
    PC   ({ &D61, &D60, &D59, &D58 }),
    MS   ({ &D67, &D68, &D69 }),
    CTRL ({ &D85, &D84, &D83, &D82, &D81, &D80, &D79, &D78,
            &D77, &D76, &D75, &D74, &D73, &D72, &D71, &D70 })
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

