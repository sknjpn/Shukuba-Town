#pragma once

#include "Drawable.h"

class Node;

class Path
	: public Uncopyable
	, public Drawable
{
	Node* m_from;
	Node* m_to;

public:
	Path(Node* from, Node* to);
	~Path();

	Node* get_from() const { return m_from; }
	Node* get_to() const { return m_to; }

	void draw() override {}
};