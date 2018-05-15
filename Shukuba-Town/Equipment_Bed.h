#pragma once

#include "Equipment.h"

class Equipment_Bed
	: public Equipment
{
public:
	Equipment_Bed(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Equipment(position, rotation, json)
	{}
};