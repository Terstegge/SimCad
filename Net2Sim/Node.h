///////////////////////////////////////////////
//
//  This file is part of
//     ___  ____  __  __  ___    __    ____
//    / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//    \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//    (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation package for electronic circuits
//
//  (c) Andreas Terstegge
//
///////////////////////////////////////////////
//
// Node represents a simple recursive structure
// with a name, a value and child elements of
// the same type Node.
//
#ifndef _NODE_H_
#define _NODE_H_

#include "Net2SimException.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class Node {
public:
    string         _name;
    string         _value;
    vector<Node>   _children;

    // Find a sub-Node with a specific name
    // in all available sub-trees. Returns
    // nullptr if not found, else a pointer
    // to the first matching Node.
    Node * find_Node(const char * name);

    // Find a Node with a specific name in
    // the child elements (only one level below),
    // and return the value. Throw an exception
    // if not found.
    string get_attr(const char * name);

    // Find a Node with a specific name in
    // the child elements (only one level below),
    // and set the value. Throw an exception
    // if not found.
    void set_attr(const char * name, const char * value);

    // Count children (only one level below) with
    // a specific name.
    int count_attr(const char * name);
};

#endif // _NODE_H_
