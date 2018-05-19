#pragma once

#include "Drawable.h"

class Node;
class Road;

class Path final
	: public Uncopyable
{
	friend Road;	//êe

	Road* m_road;
	Node* m_from;
	Node* m_to;

public:
	Path(Road* road, Node* from, Node* to);
	~Path();

	Node* get_from() const { return m_from; }
	Node* get_to() const { return m_to; }

	Path* get_opposite() const;

	Line get_line() const;
};