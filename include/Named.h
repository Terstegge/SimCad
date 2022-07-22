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
// Simple class to provide a name to an object.
// The name will be set in the CTOR and should
// not be modified afterwards. So there is only
// a getter for the name.
//
#ifndef INCLUDE_NAMED_H
#define INCLUDE_NAMED_H

#include <string>

// Helper macro to call the CTOR of 'named' objects.
// The macro expects the variable 'name' to contain
// the name of the parent object, and adds the
// variable name to it. Additional constructor
// parameters are piped through.
#define NAME(var, ...)  var(name + "." + #var, ##__VA_ARGS__)

class Named {
public:
    Named(const std::string & n) : _name(n) {
    }

    const std::string & getName() const {
        return _name;
    }

protected:
    std::string _name;
};

#endif // INCLUDE_NAMED_H
