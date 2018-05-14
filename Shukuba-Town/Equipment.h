#pragma once

#include "Transform.h"
#include "Drawable.h"

class Equipment
	: public Uncopyable
	, public Transform
	, public Drawable
{

public:
	Equipment();
};