#pragma once

#include "Drawable.h"

class Path
	: public Uncopyable
	, public Drawable
{
	void draw() override {}
};