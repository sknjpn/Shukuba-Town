#pragma once

#include "Drawable.h"
#include "Transform.h"

class Agent
	: public Uncopyable
	, public Transform
{
public:
	static const double s_radius;
};