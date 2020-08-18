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
#ifndef _NAMED_H_
#define _NAMED_H_

#include <string>
using std::string;

#define NAME(var, ...)  var(name + "." + #var, ##__VA_ARGS__)

class Named {
public:
    Named(const string & n) {
        _name = n;
    }

    const string & getName() const {
        return _name;
    }

protected:
    string _name;
};

#endif // _NAMED_H_
