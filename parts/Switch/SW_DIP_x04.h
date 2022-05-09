/*
 * SW_DIP_x08.h
 *
 *  Created on: 07.05.2022
 *      Author: andreas
 */

#ifndef PARTS_SWITCH_SW_DIP_X04_H_
#define PARTS_SWITCH_SW_DIP_X04_H_

#include "SW_DIP_x04_skel.h"
#include <string>

class SW_DIP_x04 : public SW_DIP_x04_skel {
public:
	SW_DIP_x04(std::string name);

	void openSwitchesAt(int v);
	void closeSwitchesAt(int v);
};

#endif /* PARTS_SWITCH_SW_DIP_X04_H_ */
