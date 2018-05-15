#pragma once

#include "Equipment.h"

namespace skn
{
	class EquipmentBed
		: public Equipment
	{
	public:
		EquipmentBed(const Position& position, const Rotation& rotation, s3d::JSONValue json)
			: Equipment(position, rotation, json)
		{}
	};
}