#include "RS-flipflop.h"
#include "ShortCircuitEx.h"

int main() {

    RS_flipflop ff("RS-FF");

    try {    
    ff.VCC = HIGH;
    ff.GND = LOW;
    
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    ff.nS1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;
    
    ff.nR1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    ff.nS1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;
    
    ff.nR1.toggle();
    cout << ff.Q       << " " << ff.nQ      << endl;
    cout << ff.D1.on() << " " << ff.D2.on() << endl;

    } catch (short_circuit_exception & e) {
        cerr << e << endl;
    }
    
}

