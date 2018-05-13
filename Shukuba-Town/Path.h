#pragma once

#include "Drawable.h"

class Node;

class Path final
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

	Line get_line() const;

	void draw() override {}
};