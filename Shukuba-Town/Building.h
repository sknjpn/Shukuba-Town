#pragma once

#include "Transform.h"
#include "Drawable.h"

class Node;
class Device;
class Job;

class Building
	: public Transform
	, public Uncopyable
{
	Node*	m_entrance;
	Polygon	m_base_site;
	Polygon	m_base_shape;
	Texture	m_texture;
	Array<Job*>		m_jobs;
	Array<Device*>	m_devices;

	void	init_jobs(JSONValue json);
	void	init_devices(JSONValue json);

public:
	Building(Node* entrance, const Rotation& rotation, JSONValue json);
	~Building();

	Node*	get_entrance() const { return m_entrance; }

	const Texture&	get_texture() const { return m_texture; }

	const Array<Device*>& get_devices() const { return m_devices; }

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