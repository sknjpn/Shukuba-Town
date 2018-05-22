#pragma once

#include "Builder.h"
#include "Transform.h"

//Building
struct Model
{
	JSONValue	m_json;
	Texture		m_texture;
	Polygon		m_base_site;
	Polygon		m_base_shape;
	Vec2		m_entrance_position;

	Model(JSONValue json);
};

class Builder_Building
	: public Builder
{
	Model		m_model;
	Position	m_grabbed_position;
	Rotation	m_rotation;

	bool		can_set() const;

	Position	get_setting_position() const;

public:
	Builder_Building(JSONValue json);

	void		update() override;
};