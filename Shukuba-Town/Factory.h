#pragma once

#include "Transform.h"

namespace skn
{
	class Job;
	class Item;
	class Building;
	class Equipment;

	class Factory
	{
	public:
		static Job*			make_job(Building* building, s3d::JSONValue json);
		static Item*		make_item(s3d::JSONValue json);
		static Building*	make_building(const Position& position, const Rotation& rotation, s3d::JSONValue json);
		static Equipment*	make_equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json);
	};
}