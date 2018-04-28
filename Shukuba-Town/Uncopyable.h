#pragma once

namespace skn
{
	class Uncopyable
	{
		Uncopyable(const Uncopyable&) = delete;
		Uncopyable& operator=(const Uncopyable&) = delete;
		Uncopyable(Uncopyable&&) = delete;
		Uncopyable& operator=(Uncopyable&&) = delete;

	protected:
		Uncopyable() = default;
		~Uncopyable() = default;
	};
}