#include "Inventry.h"
#include "Pouch.h"

#include <numeric>

namespace skn
{
	Inventry::Inventry(int max_size)
		: m_max_size(max_size)
	{

	}

	Inventry::~Inventry()
	{
		//Pouch‚Ìƒƒ‚ƒŠŠJ•ú
		for (auto* p : m_pouches)
		{
			delete p;
		}
	}

	int Inventry::get_size(Item* item) const
	{
		auto pouch = std::find_if(m_pouches.begin(), m_pouches.end(), [item](Pouch* p) { return p->get_item() == item; });

		return (pouch == m_pouches.end()) ? 0 : (*pouch)->get_size();
	}

	int Inventry::get_weight() const
	{
		return std::accumulate(m_pouches.begin(), m_pouches.end(), 0, [](int v, Pouch* p) { return v + p->get_weight(); });
	}

	void Inventry::add_item(Item* item, int size)
	{
		auto p_i = std::find_if(m_pouches.begin(), m_pouches.end(), [item](Pouch* p) { return p->get_item() == item; });

		if (p_i == m_pouches.end())
		{
			m_pouches.emplace_back(new Pouch(item, size));
		}
		else
		{
			(*p_i)->add_item(size);
		}
	}
	void Inventry::pull_item(Item* item, int size)
	{
		auto p_i = std::find_if(m_pouches.begin(), m_pouches.end(), [item](Pouch* p) { return p->get_item() == item; });

		(*p_i)->pull_item(size);
	}
}