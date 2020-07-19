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
// A simple exception with a std::string info
//
#ifndef _PARSE_EXCEPTION_H_
#define _PARSE_EXCEPTION_H_

#include <string>
using std::string;

struct ParseException {
    std::string info;
    ParseException(string s) : info(s) { }
};

#endif // _PARSE_EXCEPTION_H_
