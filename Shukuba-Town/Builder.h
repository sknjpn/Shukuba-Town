#pragma once

class Builder
	: public Uncopyable
{
public:
	virtual void update() = 0;
};