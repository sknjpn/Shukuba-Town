#pragma once

#include "Drawable.h"
#include "Transform.h"

class Agent
	: public Uncopyable
	, public Transform
	, public Drawable
{
	void draw() override {}
};