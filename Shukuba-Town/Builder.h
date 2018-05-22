#pragma once

class Sample;

class Builder
	: public Uncopyable
{
public:
	virtual ~Builder() = default;

	virtual void update() = 0;
};