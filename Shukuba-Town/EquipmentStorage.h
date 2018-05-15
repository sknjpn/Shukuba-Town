#pragma once

#include "Equipment.h"
#include "Inventry.h"

namespace skn
{
	class EquipmentStorage
		: public Equipment 
	{
		Inventry	m_inventry;

	public:
		EquipmentStorage(const Position& position, const Rotation& rotation, s3d::JSONValue json)
			: Equipment(position, rotation, json)
			, m_inventry(json[U"size"].get<int>())
		{}
	};
}