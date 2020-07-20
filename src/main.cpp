#include <iostream>
using namespace std;
#include <cassert>

#include "_74LS283.h"
#include "AND2.h"
#include "Bus.h"
#include "Pin.h"

int main()
{
#if 0
    AND2 a;
    
    a.p[1] = true;
    a.p[2] = true;

    cout << a.p[3] << endl;
#endif    
    
    _74LS283 add;

    Bus<4> A, B, S;
    Pin C0, C4;
    
    A[0].connect_to( add.p[5] );
    A[1].connect_to( add.p[3] );
    A[2].connect_to( add.p[14] );
    A[3].connect_to( add.p[12] );

    B[0].connect_to( add.p[6] );
    B[1].connect_to( add.p[2] );
    B[2].connect_to( add.p[15] );
    B[3].connect_to( add.p[11] );

    S[0].connect_to( add.p[4] );
    S[1].connect_to( add.p[1] );
    S[2].connect_to( add.p[13] );
    S[3].connect_to( add.p[10] );

    C0.connect_to( add.p[7] ); 
    C4.connect_to( add.p[9] ); 

    C0 = false;
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            A  = i;
            B  = j;
            cout << i << " " << j << " " << S << " " << C4 << endl;
            assert(S == ((i+j) % 16));
        }
    }

    C0 = true;
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            A  = i;
            B  = j;
            cout << i << " " << j << " " << S << " " << C4 << endl;
            assert(S == ((i+j+1) % 16));
        }
    }
    
    
}

