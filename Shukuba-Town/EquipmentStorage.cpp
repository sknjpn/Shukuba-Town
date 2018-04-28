#include "EquipmentStorage.h"

namespace skn
{
	EquipmentStorage::EquipmentStorage(s3d::JSONValue json)
		: Equipment(json)
		, m_inventry(json[U"size"].get<int>())
	{

	}
}