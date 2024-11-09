#pragma once
#include "deque.hpp"

template <class T, class Container = deque<T>>
class queue
{
private:
	Container _c;

public:
	T& front()
	{
		return _c.front();
	}
	const T& front() const
	{
		return _c.front();
	}

	T& back()
	{
		return _c.back();
	}
	const T& back() const
	{
		return _c.back();
	}

	bool empty() const
	{
		return _c.empty();
	}
	size_t size() const
	{
		return _c.size();
	}

	void push(const T& el)
	{
		_c.push_back(el);
	}
	void pop()
	{
		_c.pop_front();
	}
};
