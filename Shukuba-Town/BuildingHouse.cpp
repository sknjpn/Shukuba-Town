#include "BuildingHouse.h"

namespace skn
{
	BuildingHouse::BuildingHouse(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Building(position, rotation, json)
	{

	}
}