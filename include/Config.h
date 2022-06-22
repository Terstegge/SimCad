///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
#ifndef _INCLUDE_CONFIG_H_
#define _INCLUDE_CONFIG_H_

#include <limits>

#define INF     std::numeric_limits<double>::infinity()

#define SUPPLY_VOLTAGE (double)5.0
#define SUPPLY_GROUND  (double)0.0

#define HIGH true
#define LOW  false

#endif // _INCLUDE_CONFIG_H_
