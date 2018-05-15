#pragma once

#include "Equipment.h"

class Equipment_Interior
	: public Equipment
{
public:
	Equipment_Interior(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Equipment(position, rotation, json)
	{}
};