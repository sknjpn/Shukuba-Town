#pragma once

#include "Building.h"

namespace skn
{
	class BuildingHouse
		: public Building
	{
	public:
		BuildingHouse(s3d::JSONValue json);
	};
}
