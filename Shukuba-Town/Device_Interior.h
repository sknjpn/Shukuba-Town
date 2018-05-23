#pragma once

#include "Device.h"

class Device_Interior
	: public Device
{
public:
	Device_Interior(const Position& position, const Rotation& rotation, JSONValue json)
		: Device(position, rotation, json)
	{}
};