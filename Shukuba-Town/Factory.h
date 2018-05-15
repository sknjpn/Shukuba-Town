#pragma once

class Job;
class Building;
class Equipment;

class Factory
{
public:
	static Job*			make_job(Building* building, JSONValue json);
	static Building*	make_building(const Position& position, const Rotation& rotation, JSONValue json);
	static Equipment*	make_equipment(const Position& position, const Rotation& rotation, JSONValue json);
};