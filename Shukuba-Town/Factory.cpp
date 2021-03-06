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
	Job* skn::Factory::make_job(Building* building, s3d::JSONValue json)
	{
		if (json[U"type"].getString() == U"JobBaker") { return new JobBaker(building, json); }
		if (json[U"type"].getString() == U"JobFarmer") { return new JobFarmer(building, json); }

		return new Job(building);
	}

	Item* Factory::make_item(s3d::JSONValue json)
	{
		return new Item(json);
	}

	Building* Factory::make_building(const Position& position, const Rotation& rotation, s3d::JSONValue json)
	{
		Building* building = nullptr;

		if (json[U"type"].getString() == U"BuildingHouse") { building = new BuildingHouse(position, rotation, json); }
		else { building = new Building(position, rotation, json); }

		return building;
	}

	Equipment* Factory::make_equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json)
	{
		Equipment* equipment = nullptr;

		if (json[U"type"].getString() == U"EquipmentBed") { equipment = new EquipmentBed(position, rotation, json); }
		else if (json[U"type"].getString() == U"EquipmentStorage") { equipment = new EquipmentStorage(position, rotation, json); }
		else if (json[U"type"].getString() == U"EquipmentInterior") { equipment = new EquipmentInterior(position, rotation, json); }
		else { equipment = new Equipment(position, rotation, json); }

		return equipment;
	}
}