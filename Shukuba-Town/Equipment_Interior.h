#pragma once

#include "Equipment.h"

class Equipment_Interior
	: public Equipment
{
public:
	Equipment_Interior(const Position& position, const Rotation& rotation, JSONValue json)
		: Equipment(position, rotation, json)
	{}
};