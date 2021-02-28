/*
 * Element.h
 *
 *  Created on: 27.02.2021
 *      Author: andreas
 */

#ifndef INCLUDE_CORE_ELEMENT_H_
#define INCLUDE_CORE_ELEMENT_H_

#include <set>

class Element;

//typedef std::shared_ptr<Net> NetPtr;
typedef Element * ElementPtr;
typedef std::set<ElementPtr>  ElementSet;

class Element {
public:
    virtual ~Element() = default;
    virtual void update(ElementSet * nets) = 0;
};



#endif /* INCLUDE_CORE_ELEMENT_H_ */
