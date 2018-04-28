#include "Factory.h"

#include "Job.h"
#include "JobBaker.h"
#include "JobFarmer.h"

#include "Item.h"

#include "Building.h"
#include "BuildingHouse.h"

#include "Equipment.h"
#include "EquipmentBed.h"
#include "EquipmentStorage.h"
#include "EquipmentInterior.h"

namespace skn
{
	Job* skn::Factory::make_job(s3d::JSONValue json)
	{
		if (json[U"type"].getString() == U"JobBaker") { return new JobBaker(json); }
		if (json[U"type"].getString() == U"JobFarmer") { return new JobFarmer(json); }

		return new Job();
	}

	Item* Factory::make_item(s3d::JSONValue json)
	{
		return new Item(json);
	}

	Building* Factory::make_building(const Position& position, const Rotation& rotation, s3d::JSONValue json)
	{
		if (json[U"type"].getString() == U"BuildingHouse") { return new BuildingHouse(position, rotation, json); }

		return new Building(position, rotation, json);
	}

	Equipment* Factory::make_equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json)
	{
		if (json[U"type"].getString() == U"EquipmentBed") { return new EquipmentBed(position, rotation, json); }
		if (json[U"type"].getString() == U"EquipmentStorage") { return new EquipmentStorage(position, rotation, json); }
		if (json[U"type"].getString() == U"EquipmentInterior") { return new EquipmentInterior(position, rotation, json); }

		return new Equipment(position, rotation, json);
	}
}