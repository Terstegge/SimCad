/////////////////////////////////////////////////
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
/////////////////////////////////////////////////
//
// The Net2Sim application will read a KiCad-generated
// Eeschema net-file, and convert it into a SimCad
// compatible C++ class (*.h, *.cpp), which can be used
// for a digital simulation of the original circuit.
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

// Struct to hold component data
struct component_entry {
    string ref_base;
    string ref_idx;
    string part;
    string part_arg;
    string value;
};

// This struct is needed to store a
// single net entry from the Eeschema file
struct net_entry {
    net_entry(string n, string i, bool b) : base(n), index(i), isBus(b) { }
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
    static void name2var(string & s);

    // The value in name is split into a trailing
    // index number (stored in idx) and the remainder
    // (stored in name).
    static bool split_name_index(string & name, string & idx);

    void define_bus(vector<string> & names, const string& base, const string& index, bool isBus);
    static void change_to_bus(string & net, vector<net_entry> & found_nets);

    // Read a physical value (e.g. voltage, current, resistance) and
    // convert it to a double number.
    // Some examples:
    // 10.7V -> 10.7
    // 20mA  -> 0.02
    // 4k7   -> 4700
    // 2.4M  ->2400000
    static double readValue(const string& s);

    ofstream h_ofs, c_ofs;
};

#endif // _NET2SIM_H_
