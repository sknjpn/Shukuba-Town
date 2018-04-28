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
		EquipmentStorage(s3d::JSONValue json);
	};
}