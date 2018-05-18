#pragma once

class Node;
class Path;

class Road
	: public Uncopyable
{
	Node* m_from;
	Node* m_to;

	Path* m_primary;
	Path* m_secondary;

public:
	Road(Node* from, Node* to);
	~Road();

	const Node* get_from() const { return m_from; }
	const Node* get_to() const { return m_to; }

	const Path* get_primary() const { return m_primary; }
	const Path* get_secondary() const { return m_secondary; }
};

