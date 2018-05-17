#pragma once

#include "Transform.h"
#include "Drawable.h"

class Node;
class Equipment;
class Job;

class Building
	: public Transform
	, public Uncopyable
{
	Node*		m_entrance;
	Polygon	m_base_site;
	Polygon	m_base_shape;
	Texture	m_texture;
	std::vector<Job*>		m_jobs;
	std::vector<Equipment*>	m_equipments;

	void	init_jobs(JSONValue json);
	void	init_equipments(JSONValue json);

public:
	Building(Node* entrance, const Rotation& rotation, JSONValue json);
	~Building();

	Polygon	get_shape() const
	{
		return m_base_shape
			.rotated(get_rotation())
			.movedBy(get_position());
	}

	Polygon	get_site() const
	{
		return m_base_site
			.rotated(get_rotation())
			.movedBy(get_position());
	}
};