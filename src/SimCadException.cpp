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

#include "SimCadException.h"

// ostream operator for all SimCad exceptions
std::ostream & operator << (std::ostream & os, const SimCadException & rhs) {
    return rhs.toString(os);
}

std::ostream & shortCircuitException::toString(std::ostream & os) const {
    os << "** Short Circuit Exception in Net " << _net->getName() << " **" << std::endl;
    os << _net << std::endl;
    return os;
}

std::ostream & updateInUseException::toString(std::ostream & os) const {
    os << "** Update-In-Use Exception in Pin " << _pin->getName() << " **" << std::endl;
    os << *_pin << std::endl;
    return os;
}
