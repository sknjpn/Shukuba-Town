#include "EquipmentBed.h"

namespace skn
{
	EquipmentBed::EquipmentBed(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Equipment(position, rotation, json)
	{

	}
}