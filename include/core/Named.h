///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
// Simple class to provide a name to an object.
// The name will be set in the CTOR and should
// not be modified afterwards. So there is only
// a getter for the name!
//
#ifndef _INCLUDE_NAMED_H_
#define _INCLUDE_NAMED_H_

#include <string>

// Helper macro to call the CTOR of 'named' objects.
// The macro expects the variable 'name' to contain
// the name of the parent object, and adds the
// variable name to it. Additional constructor
// parameters are piped through.
#define NAME(var, ...)  var(name + "." + #var, ##__VA_ARGS__)

class Named {
public:
    Named(const std::string & n) {
        _name = n;
    }

    const std::string & getName() const {
        return _name;
    }

protected:
    std::string _name;
};

#endif // _INCLUDE_NAMED_H_
