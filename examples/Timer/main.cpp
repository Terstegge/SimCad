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

        t.C1.start();
        for(int i = 0; i < 10000; ++i) {
        	cout << "LED: " << t.D1.on() << "\r";
        	cout.flush();
        	this_thread::sleep_for(10ms);
        }
        t.C1.stop();

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

