#include "OP_AMP.h"
#include "ShortCircuitEx.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace std::this_thread;

int main() {

    OP_AMP op("OP_AMP");

    try {
        // Power up
        cout << "Power up" << endl;
        op.GND      =  SUPPLY_GROUND;
        op.VCC      =  SUPPLY_VOLTAGE;
        op.plus_5V  = +SUPPLY_VOLTAGE;
        op.minus_5V = -SUPPLY_VOLTAGE;

        op.C1.start();
        op.C2.start();

        cout << "Setting Iplus" << endl;
        for (double u = -5; u <= 5; u += 0.2) {
            op.Iminus = u;
            cout << op.Iminus.Ud << " -> " << op.OUT.U() << endl;
        }
        //op.Iminus = 2.6;

        for(int i=0; i < 10000; ++i) {
//            cout << op.voltage.U() << " " << op.VC.U() << " " << op.Q.U() << " " << op.DIS.U() << " " << op.C2.p[2].I() << endl ;
//            cout << drive << op.C2.p[1] << endl;
//            cout << drive << op.C2.p[2] << endl;
            cout << i << " " << op.Q.U() << endl;
            sleep_for(std::chrono::milliseconds(10));
        }

        op.C1.stop();
        op.C2.stop();

    } catch (short_circuit_exception &e) {
        cerr << e << endl;
    }

    cout << "Hallo" << endl;
}

