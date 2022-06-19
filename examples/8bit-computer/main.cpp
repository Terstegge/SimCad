///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
// This is a complete simulation of the (famous) 8-bit computer
// designed by Ben Eater, based on the original KiCad-schematics
// (see https://eater.net/8bit)
// The unique thing about this simulation is, that every single
// component (ever R, C, LED, 74LSxx, NE555) is simulated in
// real-time and with realistic voltage and current values.
//
// The program running on this 8-bit computer is the Fibonacci
// number calculation (see below).
//
#include "Computer.h"
#include "SimCadException.h"
#include "BusRef.h"

#include "prog_display.h"
#include "prog_microcode.h"

#include <thread>
#include <iostream>
#include <iomanip>

using namespace std;

// Macros for the machine instructions
#define NOP        (0x00)
#define LDA(x)     (0x10 + x)
#define ADD(x)     (0x20 + x)
#define SUB(x)     (0x30 + x)
#define STA(x)     (0x40 + x)
#define LDI(x)     (0x50 + x)
#define JMP(x)     (0x60 + x)
#define JC(x)      (0x70 + x)
#define JZ(x)      (0x80 + x)
#define OUT        (0xE0)
#define HLT        (0xF0)

int main() {

    Computer comp("comp");

    // For the multiplexed 7-segment display, we attach a callback to
    // the Q output of U37 (the NE555 timer for multiplex clocking).
    // Whenever we have a rising edge on Q, we read out the segment
    // address (p13/p14 of U41), decoded the content of the selected
    // segment using the to_char() method and write the result to the
    // char-array 'Display'. Due to this process, the value of the
    // display is delayed and not immediately shown after the
    // OUT-command.
    char Display[5] = { ' ', ' ', ' ', ' ', 0 };
    //
    _7SEGMENT_CC * Segments[4] = {
        &comp.U46,  // Segment with addr 0 (ones)
        &comp.U45,  // Segment with addr 1 (tens)
        &comp.U44,  // Segment with addr 2 (hundreds)
        &comp.U43,  // Segment with addr 3 (sign)
    };
    // 
    BusRef addr({
        &comp.U41.p[14], // A0 
        &comp.U41.p[13]  // A1
    });
    // Attach a callback to the Q output of the NE555.
    // On all rising edges, read out the address of the
    // active segment and its content, and store the
    // result in the Display array.
    comp.U37.p[3].attach([&](NetSet * nset) {
        if ((bool)comp.U37.p[3]) {
            Display[3-addr] = Segments[addr]->to_char();
        }
    });

    // Program the EEPROMs (display and microcode)
    prog_display pd(comp.U42._mem);
    pd.programEEPROM();
    prog_microcode pm(comp.U50._mem, comp.U51._mem);
    pm.programEEPROMs();

    try {
        // Slow down the NE555 timer for display multiplexing.
        // The original frequency is approx. 718Hz, which is too
        // fast for the simulation. With 718nF, we get approx. 10Hz.
        comp.C19.setCapacity(718e-9);
        // Slow down the pulse generator in the RAM module. In the
        // original design we have RC=10us. With 20uF, we get 20ms.
        comp.C14.setCapacity(20e-6);

        // Set single step clock mode
        comp.CLK_MODE.set(CLK_MODE_STEP);
        // Set manual program  mode
        comp.PRGM_MODE.set(PROG_MODE_ON);
        // Set unsigned display mode
        comp.OUT_MODE.set(OUT_MODE_UNSIGNED);

        cout << "Power up ..." << endl;
        // We have to disable short circuit exceptions during
        // startup, because several 74LS245 buffers might write
        // to the bus simultaneously before the whole power-up
        // process is complete.
        Net::_enable_sc_exceptions = false;
        comp.J1.GND  = SUPPLY_GROUND;
        comp.J1.VBUS = SUPPLY_VOLTAGE;
        Net::_enable_sc_exceptions = true;
        // Start C thread (the thread which will handle the
        // (de)charging process of all capacitors in the schematic.
        C::start();

        /////////////////
        // The program //
        /////////////////

        int program[] = {
            /* 00 */     LDA    (13), // Get Fib n and ...
            /* 01 */     ADD    (14), // ... add Fib n+1
            /* 02 */     STA    (15), // Store the result (Fib n+2)
            /* 03 */     JC     (10), // Terminate if we get a carry
            /* 04 */     LDA    (14), // Shift the number Fib n+1 to n
            /* 05 */     STA    (13),
            /* 06 */     LDA    (15), // Shift the number Fib n+2 to n+1
            /* 07 */     STA    (14), 
            /* 08 */     OUT,         // Output Fib n+1 ...
            /* 09 */     JMP    (00), // ... and start over
            /* 10 */     HLT,
            /* 11 */              0,
            /* 12 */              0,
            /* 13 */              0,  // Fibonacci n
            /* 14 */              1,  // Fibonacci n+1
            /* 15 */              0   // Fibonacci n+2
        };

        // As in real life, toggle in the program using
        // the DIP switches and the STORE button.
        cout << "Toggle in Program ..." << endl;
        for (int i = 0; i < 16; ++i) {
            comp.ADDR.openSwitchesAt( i );
            comp.DATA.openSwitchesAt( program[i] );
            comp.STORE.toggle();
        }

        // Reset the computer to a defined state.
        cout << "Reset ..." << endl;
        comp.RESET.toggle();

        // Attach a handler to the HLT line, because we
        // also want to stop the simulation in this situation
        // by setting the variable 'running' to false.
        bool running = true;
        comp.Clock_HLT.attach([&] (NetSet * nset) {
            if (comp.Clock_HLT) running = false;
        });

        // For every falling edge of our main CLK signal,
        // show the CPU state
        comp.A_Register_CLK.attach([&] (NetSet * nset) {
            if (!(bool)comp.A_Register_CLK) {
                cout << comp << "OUT:'" << Display << "'" << endl;
            }
        });

        // Set the speed of the main clock
        comp.RV1.setPercent(95);
        // End manual program  mode
        comp.PRGM_MODE.set(PROG_MODE_OFF);
        // Set signed/unsigned display mode
        comp.OUT_MODE.set(OUT_MODE_UNSIGNED);

        // Run the program ... let the party begin :)
        cout << "Run the program ..." << endl;
        comp.CLK_MODE.set(CLK_MODE_RUN);

        // Our main loop. Do nothing else than wait until
        // the computer generates a HLT signal (see above).
        // Since the simulation is triggered by an internal
        // NE555 timer, we do not have to provide a clock
        // signal here.
        while (running) {
            this_thread::sleep_for(200ms);
        }
        // Show the final CPU state
        cout << comp << "OUT:'" << Display << "'" << endl;

        // End the thread for capacitor handling.
        C::stop();

    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

