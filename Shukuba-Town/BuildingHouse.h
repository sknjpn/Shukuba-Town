#pragma once

#include "Building.h"

namespace skn
{
	class BuildingHouse
		: public Building
	{
	public:
		BuildingHouse(const Position& position, const Rotation& rotation, s3d::JSONValue json)
			: Building(position, rotation, json)
		{}
	};
}
