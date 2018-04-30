#include "EquipmentInterior.h"

namespace skn
{
	EquipmentInterior::EquipmentInterior(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Equipment(position, rotation, json)
	{

	}
}