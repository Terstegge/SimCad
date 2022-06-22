#include "SimpleNet2.h"
#include "SimCadException.h"

#include <iostream>
using namespace std;

int main() {

    SimpleNet2 sn2("SN2");

    try {
        // Power up
        cout << "********** Setting GND" << endl;
        sn2.GND = SUPPLY_GROUND;
        sn2.V1.update();
        sn2.V2.update();
        sn2.I1.update();

        cout << "Pin status:" << endl;
        cout << sn2.V1.p[1] << endl;
        cout << sn2.V1.p[2] << endl;
        cout << sn2.V2.p[1] << endl;
        cout << sn2.V2.p[2] << endl;
        cout << sn2.I1.p[1] << endl;
        cout << sn2.I1.p[2] << endl;
        cout << sn2.R1.p[1] << endl;
        cout << sn2.R1.p[2] << endl;
        cout << sn2.R2.p[1] << endl;
        cout << sn2.R2.p[2] << endl;
        cout << sn2.R3.p[1] << endl;
        cout << sn2.R3.p[2] << endl;
        cout << sn2.R4.p[1] << endl;
        cout << sn2.R4.p[2] << endl;
        cout << sn2.R5.p[1] << endl;
        cout << sn2.R5.p[2] << endl;
        cout << sn2.R6.p[1] << endl;
        cout << sn2.R6.p[2] << endl;
        cout << sn2.R7.p[1] << endl;
        cout << sn2.R7.p[2] << endl;
        cout << sn2.R8.p[1] << endl;
        cout << sn2.R8.p[2] << endl;
        cout << sn2.GND     << endl;
        cout << endl << endl;

        cout << "Pin drive status:" << endl;
        cout << drive << sn2.V1.p[1] << endl;
        cout << drive << sn2.V1.p[2] << endl;
        cout << drive << sn2.V2.p[1] << endl;
        cout << drive << sn2.V2.p[2] << endl;
        cout << drive << sn2.I1.p[1] << endl;
        cout << drive << sn2.I1.p[2] << endl;
        cout << drive << sn2.R1.p[1] << endl;
        cout << drive << sn2.R1.p[2] << endl;
        cout << drive << sn2.R2.p[1] << endl;
        cout << drive << sn2.R2.p[2] << endl;
        cout << drive << sn2.R3.p[1] << endl;
        cout << drive << sn2.R3.p[2] << endl;
        cout << drive << sn2.R4.p[1] << endl;
        cout << drive << sn2.R4.p[2] << endl;
        cout << drive << sn2.R5.p[1] << endl;
        cout << drive << sn2.R5.p[2] << endl;
        cout << drive << sn2.R6.p[1] << endl;
        cout << drive << sn2.R6.p[2] << endl;
        cout << drive << sn2.R7.p[1] << endl;
        cout << drive << sn2.R7.p[2] << endl;
        cout << drive << sn2.R8.p[1] << endl;
        cout << drive << sn2.R8.p[2] << endl;
        cout << drive << sn2.GND     << endl;

    } catch (SimCadException &e) {
        cerr << e << endl;
    }
}

