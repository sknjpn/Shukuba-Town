#pragma once

#include "Builder.h"

class Node;

class Builder_Road
	: public Builder
{
	Vec2	m_from_position;
	Vec2	m_to_position;

	void		set_from_position(const Vec2& position);
	void		set_to_position(const Vec2& position);

	bool		can_set() const;

public:
	void	update() override;
};