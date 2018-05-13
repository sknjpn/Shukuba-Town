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
	Node(const Vec2& position, double radius);
	~Node();

	void connect(Node* to, double width);
	void disconnect(Node* to);

	bool has_path(Node* to) const { return m_paths.end() != std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }); }
	Path* get_path(Node* to) const { return *std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }); }
};