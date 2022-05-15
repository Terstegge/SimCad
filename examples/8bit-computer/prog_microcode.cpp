//
// This code is a modified version of the original Arduino sketch,
// which is for the microcode EEPROMs for the 8-bit breadboard computer.
// It includes support for a flags register with carry and zero flags
// See this video for more: https://youtu.be/Zg1NdPKoosU
//
#include "prog_microcode.h"

#include <iostream>
#include <cstring>
using namespace std;

// The 16 control signals
/////////////////////////
#define HLT 0b1000000000000000  // Halt clock
#define MI  0b0100000000000000  // Memory address register in
#define RI  0b0010000000000000  // RAM data in
#define RO  0b0001000000000000  // RAM data out
#define IO  0b0000100000000000  // Instruction register out
#define II  0b0000010000000000  // Instruction register in
#define AI  0b0000001000000000  // A register in
#define AO  0b0000000100000000  // A register out
#define EO  0b0000000010000000  // ALU out
#define SU  0b0000000001000000  // ALU subtract
#define BI  0b0000000000100000  // B register in
#define OI  0b0000000000010000  // Output register in
#define CE  0b0000000000001000  // Program counter enable
#define CO  0b0000000000000100  // Program counter out
#define J   0b0000000000000010  // Jump (program counter in)
#define FI  0b0000000000000001  // Flags in

#define FLAGS_Z0C0 0
#define FLAGS_Z0C1 1
#define FLAGS_Z1C0 2
#define FLAGS_Z1C1 3

#define JC  0b0111
#define JZ  0b1000

// Microcode template without flag processing
/////////////////////////////////////////////
uint16_t UCODE_TEMPLATE[16][8] = {
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0000 - NOP
  { MI|CO,  RO|II|CE,  IO|MI,  RO|AI,  0,           0, 0, 0 },   // 0001 - LDA
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|FI,    0, 0, 0 },   // 0010 - ADD
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|SU|FI, 0, 0, 0 },   // 0011 - SUB
  { MI|CO,  RO|II|CE,  IO|MI,  AO|RI,  0,           0, 0, 0 },   // 0100 - STA
  { MI|CO,  RO|II|CE,  IO|AI,  0,      0,           0, 0, 0 },   // 0101 - LDI
  { MI|CO,  RO|II|CE,  IO|J,   0,      0,           0, 0, 0 },   // 0110 - JMP
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0111 - JC
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1000 - JZ
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1001
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1010
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1011
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1100
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1101
  { MI|CO,  RO|II|CE,  AO|OI,  0,      0,           0, 0, 0 },   // 1110 - OUT
  { MI|CO,  RO|II|CE,  HLT,    0,      0,           0, 0, 0 },   // 1111 - HLT
};

prog_microcode::prog_microcode(uint8_t *eeprom_h, uint8_t *eeprom_l) :
        _eeprom_h(eeprom_h), _eeprom_l(eeprom_l) {
}

void prog_microcode::writeEEPROM(int address, uint8_t data) {
    // Both EEPROMS get the same data.
    // A7 serves as a 'switch' for lower/upper control bytes
    _eeprom_h[address] = data;
    _eeprom_l[address] = data;
}

void prog_microcode::programEEPROMs() {
    // Array for the complete microcode (both EEPROMs)
    uint16_t ucode[4][16][8];

    // ZF = 0, CF = 0
    memcpy(ucode[FLAGS_Z0C0], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));

    // ZF = 0, CF = 1
    memcpy(ucode[FLAGS_Z0C1], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
    ucode[FLAGS_Z0C1][JC][2] = IO|J;

    // ZF = 1, CF = 0
    memcpy(ucode[FLAGS_Z1C0], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
    ucode[FLAGS_Z1C0][JZ][2] = IO|J;

    // ZF = 1, CF = 1
    memcpy(ucode[FLAGS_Z1C1], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
    ucode[FLAGS_Z1C1][JC][2] = IO|J;
    ucode[FLAGS_Z1C1][JZ][2] = IO|J;

    cout << "Programming microcode EEPROM" << endl;

    // Program the 8 high-order bits of microcode into the first 128 bytes of EEPROM
    for (int address = 0; address < 1024; address += 1) {
      int flags       = (address & 0b1100000000) >> 8;
      int byte_sel    = (address & 0b0010000000) >> 7;
      int instruction = (address & 0b0001111000) >> 3;
      int step        = (address & 0b0000000111);

      if (byte_sel) {
        writeEEPROM(address, ucode[flags][instruction][step]);
      } else {
        writeEEPROM(address, ucode[flags][instruction][step] >> 8);
      }
    }
}

