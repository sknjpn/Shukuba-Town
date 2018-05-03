#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Pouch;
	class Item;

	class Inventry
		: public Uncopyable
	{
		int		m_max_size;
		std::vector<Pouch*>	m_pouches;

	public:
		Inventry(int max_size);
		~Inventry();

		int		get_size(Item* item) const;
		int		get_weight() const;

		void	add_item(Item* item, int size);
		
		void	pull_item(Item* item, int size);
	};
}