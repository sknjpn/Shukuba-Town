#pragma once

#include "Equipment.h"

namespace skn
{
	class EquipmentBed
		: public Equipment
	{
	public:
		EquipmentBed(s3d::JSONValue json);
	};
}