#pragma once

#include "Equipment.h"

namespace skn
{
	class EquipmentInterior
		: public Equipment
	{
	public:
		EquipmentInterior(const Position& position, const Rotation& rotation, s3d::JSONValue json);
	};
}