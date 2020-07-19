/*
 * Named.h
 *
 *  Created on: 03.01.2020
 *      Author: andreas
 */

#include <string>
using std::string;

#ifndef _NAMED_H_
#define _NAMED_H_

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
