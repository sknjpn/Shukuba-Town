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
};

