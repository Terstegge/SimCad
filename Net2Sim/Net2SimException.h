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
