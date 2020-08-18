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
// A simple exception with a std::string info
//
#ifndef _NET2SIM_EXCEPTION_H_
#define _NET2SIM_EXCEPTION_H_

#include <string>
using std::string;

struct Net2SimException {
    std::string info;
    Net2SimException(string s) : info(s) { }
};

#endif // _NET2SIM_EXCEPTION_H_
