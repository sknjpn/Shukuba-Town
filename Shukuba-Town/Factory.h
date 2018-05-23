#pragma once

#include "Transform.h"

class Job;
class Building;
class Device;

class Factory
{
public:
	static Job*			make_job(Building* building, JSONValue json);
	static Device*	make_device(const Position& position, const Rotation& rotation, JSONValue json);
};