#pragma once

#include "Transform.h"

class Path;

class Node
	: public Uncopyable
	, public Transform
{
	Array<Path*> m_paths;

public:
	Node(const Vec2& position);
	~Node();

	void connect(Node* to) { m_paths.emplace_back(new Path(this, to)); to->m_paths.emplace_back(new Path(to, this)); }
	void disconnect(Node* to) { m_paths.remove_if([to](Path* p) { return p->get_to() == to; }); to->m_paths.remove_if([this](Path* p) { return p->get_to() == this; }); }

	bool has_path(Node* to) const { return m_paths.end() != std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }); }
	Path* get_path(Node* to) const { return *std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }); }
};