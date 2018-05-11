#pragma once

class Builder;

class Field 
	: public Uncopyable
{
	Builder* m_builder;

public:
	Field();
	~Field();
};

extern Field* g_field;