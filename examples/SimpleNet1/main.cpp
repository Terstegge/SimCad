#include "SimpleNet1.h"
#include "ShortCircuitEx.h"

#include <iostream>
using namespace std;

int main() {

    SimpleNet1 sn1("SN1");

    try {
        // Power up
        cout << "********** Setting GND" << endl;
        sn1.V1.ground();

        cout << "Pin status:" << endl;
        cout << sn1.V1.p[1] << endl;
        cout << sn1.V1.p[2] << endl;
        cout << sn1.I1.p[1] << endl;
        cout << sn1.I1.p[2] << endl;
        cout << sn1.R1.p[1] << endl;
        cout << sn1.R1.p[2] << endl;
        cout << sn1.R2.p[1] << endl;
        cout << sn1.R2.p[2] << endl;
        cout << sn1.R3.p[1] << endl;
        cout << sn1.R3.p[2] << endl;
        cout << sn1.R4.p[1] << endl;
        cout << sn1.R4.p[2] << endl;
        cout << sn1.R5.p[1] << endl;
        cout << sn1.R5.p[2] << endl;
        cout << endl << endl;

        cout << "Pin drive status:" << endl;
        cout << drive << sn1.V1.p[1] << endl;
        cout << drive << sn1.V1.p[2] << endl;
        cout << drive << sn1.I1.p[1] << endl;
        cout << drive << sn1.I1.p[2] << endl;
        cout << drive << sn1.R1.p[1] << endl;
        cout << drive << sn1.R1.p[2] << endl;
        cout << drive << sn1.R2.p[1] << endl;
        cout << drive << sn1.R2.p[2] << endl;
        cout << drive << sn1.R3.p[1] << endl;
        cout << drive << sn1.R3.p[2] << endl;
        cout << drive << sn1.R4.p[1] << endl;
        cout << drive << sn1.R4.p[2] << endl;
        cout << drive << sn1.R5.p[1] << endl;
        cout << drive << sn1.R5.p[2] << endl;

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }
}

