#include "EquipmentStorage.h"

namespace skn
{
	EquipmentStorage::EquipmentStorage(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Equipment(position, rotation, json)
		, m_inventry(json[U"size"].get<int>())
	{

	}
}