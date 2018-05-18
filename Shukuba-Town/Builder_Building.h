#pragma once

#include "Builder.h"
#include "Transform.h"

class Builder_Building
	: public Builder
{
	Vec2		m_grabbed_position;
	double		m_rotation;

	bool		can_set() const;

	Position	get_setting_position() const;

public:
	Builder_Building();

	void		update() override;
};