#pragma once

#include "Equipment.h"

class Equipment_Bed
	: public Equipment
{
public:
	Equipment_Bed(const Position& position, const Rotation& rotation, JSONValue json)
		: Equipment(position, rotation, json)
	{}
};