#pragma once

#include "Device.h"

class Device_Bed
	: public Device
{
public:
	Device_Bed(const Position& position, const Rotation& rotation, JSONValue json)
		: Device(position, rotation, json)
	{}
};