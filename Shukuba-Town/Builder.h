#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Builder
		: Uncopyable
	{
	public:
		Builder() = default;
		virtual ~Builder() = default;

		virtual void	update() = 0;
	};
}