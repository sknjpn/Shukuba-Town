#include "Builder.h"
#include "Sample.h"

Sample* Builder::get_selected_sample() const
{
	auto it = std::find_if(m_samples.begin(), m_samples.end(), [](Sample* s) { return s->is_selected(); });

	return (it == m_samples.end()) ? nullptr : *it;
}

void Builder::update_samples()
{
	for (auto* s : m_samples)
	{
		s->update();
	}
}
