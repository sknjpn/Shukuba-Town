#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Builder
		: public Uncopyable
	{
	public:
		Builder() = default;
		virtual ~Builder() = default;

		virtual void	update() = 0;
	};
}