#pragma once

#include "Builder.h"
#include "Transform.h"

struct Model
{
	Texture		m_texture;
};

class Builder_Building
	: public Builder
{
	Position	m_grabbed_position;
	Rotation	m_rotation;

	bool		can_set() const;

	Position	get_setting_position() const;

public:
	Builder_Building();

	void		update() override;
};