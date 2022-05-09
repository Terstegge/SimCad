#include "8bit-computer.h"
#include "ShortCircuitEx.h"

#include "prog_display.h"
#include <thread>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    _8bit_computer comp("comp");

    // Alias names for easier use

    // Controls for Clock Module
    SW_Push    & STEP = comp.SW1;
    SW_SPDT    & CLOCK_MODE  = comp.SW2;
    enum { RUN        = SW_SPDT::con21,
    	   SINGLE_STEP= SW_SPDT::con23 };

    SW_Push    & STORE       = comp.SW3;
    SW_SPDT    & RUN_MODE    = comp.SW5;

    SW_DIP_x08 & DATA        = comp.SW4;
    SW_DIP_x04 & ADDR        = comp.SW6;

    // Controls in the Output Module
    enum { UNSIGNED = SW_SPDT::con21,
    	   SIGNED   = SW_SPDT::con23 };
    SW_SPDT & OUTPUT_MODE = comp.SW7;


    SW_Push & RESET = comp.SW8;

    try {
    	// Program the display EEPROM
    	prog_display pd(comp.U42._mem);
    	pd.programEEPROM();

    	// Slow down the NE555 timer for
    	// display multiplexing
    	comp.C19.setCapacity(1e-6);
    	comp.C19.start();

    	// Set single step mode
    	CLOCK_MODE.set(SINGLE_STEP);

    	// Set unsigned display mode
    	OUTPUT_MODE.set(UNSIGNED);

    	// Power up
    	cout << "Power up ..." << endl;
    	comp.J1.GND  = SUPPLY_GROUND;
    	comp.J1.VBUS = SUPPLY_VOLTAGE;

    	// Put the computer in reset state
    	cout << "Reset ..." << endl;
    	RESET.press(true);

    	for(int i=0; i < 10000; ++i) {
    		cout << "'" << comp.U43 << comp.U44 << comp.U45 << comp.U46 << "'  " << "\r";
    		cout.flush();
    		this_thread::sleep_for(10ms);
    	}

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }

}

