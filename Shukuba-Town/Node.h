#pragma once

#include "Transform.h"

class Path;

class Node final
	: public Uncopyable
	, public Transform
{
	double m_radius;
	Array<Path*> m_paths;

public:
	Node(const Vec2& position);
	~Node();

	static const double s_radius;

	void connect(Node* to, double width);
	void disconnect(Node* to);

	bool has_path(Node* to) const;
	Path* get_path(Node* to) const;
};