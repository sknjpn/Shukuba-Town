#pragma once

class Sample;

class Builder
	: public Uncopyable
{
	Sample*			m_selected_sample;
	Array<Sample*>	m_samples;

public:
	virtual ~Builder() = default;

	Sample*	get_selected_sample() const;

	void update_samples();
	virtual void update() = 0;
};