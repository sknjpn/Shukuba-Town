#include "Factory.h"

#include "Job.h"
#include "Job_Baker.h"
#include "Job_Farmer.h"

#include "Building.h"

#include "Device.h"
#include "Device_Bed.h"
#include "Device_Interior.h"

Job* Factory::make_job(Building* building, JSONValue json)
{
	if (json[U"type"].getString() == U"Job_Baker") { return new Job_Baker(building, json); }
	if (json[U"type"].getString() == U"Job_Farmer") { return new Job_Farmer(building, json); }

	return new Job(building);
}

Device* Factory::make_device(const Position& position, const Rotation& rotation, JSONValue json)
{
	Device* device = nullptr;

	if (json[U"type"].getString() == U"Device_Bed") { device = new Device_Bed(position, rotation, json); }
	else if (json[U"type"].getString() == U"Device_Interior") { device = new Device_Interior(position, rotation, json); }
	else { device = new Device(position, rotation, json); }

	return device;
}