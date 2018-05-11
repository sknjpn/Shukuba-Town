#pragma once

class Scene
	: public Uncopyable
{
public:
	virtual void start() = 0;
	virtual void update() = 0;
};
