#include "Factory.h"

#include "Job.h"
#include "Job_Baker.h"
#include "Job_Farmer.h"

#include "Building.h"

#include "Equipment.h"
#include "Equipment_Bed.h"
#include "Equipment_Interior.h"

namespace skn
{
	Job* skn::Factory::make_job(Building* building, s3d::JSONValue json)
	{
		if (json[U"type"].getString() == U"Job_Baker") { return new Job_Baker(building, json); }
		if (json[U"type"].getString() == U"Job_Farmer") { return new Job_Farmer(building, json); }

		return new Job(building);
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

		if (json[U"type"].getString() == U"Equipment_Bed") { equipment = new Equipment_Bed(position, rotation, json); }
		else if (json[U"type"].getString() == U"EquipmentStorage") { equipment = new EquipmentStorage(position, rotation, json); }
		else if (json[U"type"].getString() == U"Equipment_Interior") { equipment = new Equipment_Interior(position, rotation, json); }
		else { equipment = new Equipment(position, rotation, json); }

		return equipment;
	}
}