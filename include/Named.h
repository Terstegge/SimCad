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
// Simple base class to provide a name to a object.
//
#ifndef _NAMED_H_
#define _NAMED_H_

#include <string>
using std::string;

#define NAME(var) var(_name + "." + #var)

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
