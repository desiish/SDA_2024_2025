#pragma once

template <class T>
class iterator
{
private:
	T* _mem_ptr;

public:
	iterator(T* ptr) : _mem_ptr{ ptr } {}
	iterator(T* ptr, size_t offs) : _mem_ptr{ ptr + offs } {}

	iterator<T>& operator--()
	{
		_mem_ptr--;
		return *this;
	}

	iterator<T>& operator--(int)
	{
		_mem_ptr--;
		return { _mem_ptr + 1 };
	}

	iterator<T>& operator++()
	{
		_mem_ptr++;
		return *this;
	}

	iterator<T>& operator++(int)
	{
		iterator<T> it = *this;
		*this++;
		return it;
	}

	int operator-(const iterator<T>& other) const
	{
		return (_mem_ptr - other._mem_ptr);
	}

	iterator<T> operator-(int offset) const
	{
		return { _mem_ptr - offset };
	}

	iterator<T> operator+(int offset) const
	{
		return { _mem_ptr + offset };
	}

	const T* operator->() const
	{
		return _mem_ptr;
	}

	T* operator->() {
		return _mem_ptr;
	}

	T& operator*()
	{
		return (*_mem_ptr);
	}

	const T& operator*() const
	{
		return (*_mem_ptr);
	}

	bool operator==(const iterator<T>& other) const
	{
		return _mem_ptr == other._mem_ptr;
	}

	bool operator!=(const iterator<T>& other) const
	{
		return !(*this == other);
	}
};