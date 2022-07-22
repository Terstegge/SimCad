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
    throw Net2SimException(string(name) + " not found!");
}


void Node::set_attr(const char * name, const char * value)
{
    for(Node & child : _children) {
        if (child._name == string(name)) {
            child._value = value;
            return;
        }
    }
    throw Net2SimException(string(name) + " not found!");
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
