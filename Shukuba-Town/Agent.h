#pragma once

#include "Drawable.h"

class Agent
	: public Uncopyable
	, public Drawable
{
	void draw() override {}
};