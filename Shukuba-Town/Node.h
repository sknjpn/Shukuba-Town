#pragma once

#include "Transform.h"

class Path;
class Road;

class Node final
	: public Uncopyable
	, public Transform
{
	friend Road;	//êe

	double m_radius;
	Array<Path*> m_paths;

public:
	Node(const Vec2& position);
	~Node();

	static const double s_radius;

	bool has_path(Node* to) const;
	Path* get_path(Node* to) const;
};