#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Item;

	class Pouch
		: Uncopyable
	{
		Item*	m_item;
		int		m_size;

	public:
		Pouch(Item* item, int size);

		Item*	get_item() const;
		int		get_size() const;
		int		get_weight() const;

		void	add_item(int size);
		void	pull_item(int size);
	};
}