#pragma once

#include "Equipment.h"

namespace skn
{
	class EquipmentInterior
		: public Equipment
	{
	public:
		EquipmentInterior(s3d::JSONValue json);
	};
}