///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
// The Net2Sim application will read a KiCad-generated
// Eeschema net-file, and convert it into a DigiSim
// compatible C++ header file, which can be used for
// a digital simulation of the original schematic.
//
#ifndef _NET2SIM_H_
#define _NET2SIM_H_

#include "Node.h"
#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::ofstream;
using std::vector;

// This struct is needed to store a
// single net entry from the Eeschema file
struct NetEntry {
    NetEntry(string n, string i, bool b)
    : base(n), index(i), isBus(b) { }
    string  base;   // base name of net
    string  index;  // index or empty if no index
    bool    isBus;  // belongs to a bus
};


class Net2Sim {
public:
    // The main Net2Sim program
    int main(int argc, char* argv[]);

private:
    // Convert a string to a valid
    // C++ identifier.
    void name2var(string & s);

    // The value in name is split into a trailing
    // index number (stored in idx) and the remainder
    // (stored in name).
    bool split_name_index(string & name, string & idx);

    void define_bus(string base, string index, bool isBus);
    void change_to_bus(string & net, vector<NetEntry> & found_nets);


    ofstream _out;
};

#endif // _NET2SIM_H_
