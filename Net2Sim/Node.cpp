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
#include "Node.h"

Node * Node::find_Node(const char * name)
{
    // Check for this Node
    if (_name == std::string(name)) {
        return this;
    } else {
        for(Node & child : _children) {
        	// Recursive search
            Node * p = child.find_Node(name);
            if (p) return p;
        }
    }
    return nullptr;
}


string Node::get_attr(const char * name)
{
    for(Node & child : _children) {
        if (child._name == std::string(name)) {
            return child._value;
        }
    }
    throw ParseException(string(name) + " not found!");
}


void Node::set_attr(const char * name, const char * value)
{
    for(Node & child : _children) {
        if (child._name == string(name)) {
            child._value = value;
            return;
        }
    }
    throw ParseException(string(name) + " not found!");
}


int Node::count_attr(const char * name)
{
    int count = 0;
    for(Node & child : _children) {
        if (child._name == std::string(name)) {
            count++;
        }
    }
    return count;
}
