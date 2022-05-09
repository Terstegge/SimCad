#include "Timer.h"
#include "ShortCircuitEx.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace std::this_thread;

int main() {

    Timer t("Timer");

    try {
        // Power up
        cout << "Power up" << endl;
        t.GND = 0.0;
        t.VCC = 5.0;
        // Start C-thread
        t.C1.start();
        // Put NE555 and 74LS161 in reset mode
        t.nRESET = 0.0;

        this_thread::sleep_for(1s);
    	cout << "Start Timer" << endl;
    	t.nRESET = 5.0;

        for(int i = 0; i < 10000; ++i) {
        	cout << "LED: " << t.D1.on() << " " << t.COUNT << "\r";
        	cout.flush();
        	this_thread::sleep_for(10ms);
        }
        // Stop C-thread
        t.C1.stop();

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

