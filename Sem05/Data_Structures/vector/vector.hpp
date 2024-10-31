#pragma once
#include "iterator.hpp"
#include <stdexcept>

template <class T>
class vector
{
private:
	T* _data;
	size_t _size;
	size_t _capacity;

public:
	vector();
	vector(size_t size);
	vector(size_t size, const T& value);

	vector(const vector<T>& other);
	vector(vector<T>&& other);
	vector<T>& operator=(const vector<T>& other);
	vector<T>& operator=(vector<T>&& other);

	~vector();

	size_t size() const
	{
		return _size;
	}

	size_t capacity() const
	{
		return _capacity;
	}

	iterator<T> begin()
	{
		return { _data };
	}
	iterator<T> end()
	{
		return { _data + _size };
	}

	T& front() 
	{
		return _data[0];
	}

	const T& front() const
	{
		return _data[0];
	}

	T& back()
	{
		return _data[_size - 1];
	}

	const T& back() const
	{
		return _data[_size - 1];
	}

	bool empty() const
	{
		return size() == 0;
	}

	T& operator[](size_t idx)
	{
		if (idx >= _size)
			throw std::out_of_range("Index out of bounds");

		return _data[idx];
	}

	const T& operator[](size_t idx) const
	{
		if (idx >= _size)
			throw std::out_of_range("Index out of bounds");

		return _data[idx];
	}

	void push_back(const T& value);
	void push_back(T&& value);

	template< class... Args >
	void emplace_back(Args&&... args);

	void pop_back();

	void erase(const iterator<T>& it);
	void erase(const iterator<T>& first, const iterator<T>& last);

	void insert(const iterator<T>& pos, const T& el);
	void insert(const iterator<T>& pos, T&& el);
	void insert(const iterator<T>& pos, size_t count, const T& el);
	void insert(const iterator<T>& pos, const iterator<T>& first, const iterator<T>& last);

	void resize(size_t n);
	void reserve(size_t n);

	void clear();

private:
	void free();
	void copyFrom(const vector<T>& other);
	void moveFrom(vector<T>&& other);

	static const size_t DEFAULT_SIZE = 8;
	static const size_t GROWTH_FACTOR = 2;
};

template <class T>
void vector<T>::free()
{
	for (int i = 0; i < _size; i++)
		_data[i].~T();

	operator delete(_data, _capacity * sizeof(T));
}

template <class T>
void vector<T>::copyFrom(const vector<T>& other)
{
	_data = static_cast<T*>(operator new(other._capacity * sizeof(T))); //allocates memory

	for (size_t i = 0; i < other._size; i++)
		new(&_data[i]) T(other._data[i]); // constructs object on address _data[i] with copy constructor

	_size = other._size;
	_capacity = other._capacity;

}

template <class T>
void vector<T>::moveFrom(vector<T>&& other)
{
	_data = static_cast<T*>(operator new(other._capacity * sizeof(T))); //allocates memory

	for (size_t i = 0; i < other._size; i++)
		new(&_data[i]) T(std::move(other._data[i])); // constructs object on address _data[i] with move constructor

	_size = other._size;
	_capacity = other._capacity;
}

template<class T>
vector<T>::vector()
{
	reserve(DEFAULT_SIZE);
}

template<class T>
vector<T>::vector(size_t size) : _size(size), _capacity(size)
{
	_data = static_cast<T*>(operator new(size) * sizeof(T)); // allocates memory

	for (size_t i = 0; i < size; i++)
		new(&_data[i]) T(); // constructs each object with default value 
}

template<class T>
vector<T>::vector(size_t size, const T& value)
{
	_data = static_cast<T*>(operator new(size) * sizeof(T)); // allocates memory

	for (size_t i = 0; i < size; i++)
		new(&_data[i]) T(value); // constructs each object with copy constructor 
}

template<class T>
vector<T>::vector(const vector<T>& other)
{
	copyFrom(other);
}

template<class T>
vector<T>::vector(vector<T>&& other)
{
	moveFrom(std::move(other));
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(other);
	}

	return *this;
}

template<class T>
vector<T>::~vector()
{
	free();
}

template <class T>
void vector<T>::push_back(const T& value)
{
	if (_capacity == _size)
		reserve(_capacity * GROWTH_FACTOR);

	new(_data[size++]) T(value);
}

template <class T>
void vector<T>::push_back(T&& value)
{
	if (_capacity == _size)
		reserve(_capacity * GROWTH_FACTOR);

	new(&_data[_size++]) T(std::move(value));
}

template <class T>
template <class... Args>
void vector<T>::emplace_back(Args&&... args)
{
	if (_capacity == _size)
		reserve(_capacity * GROWTH_FACTOR);

	new (&_data[_size++]) T(std::forward<Args>(args)...);
}

template <class T>
void vector<T>::pop_back()
{
	_size--;
	_data[_size].~T();
}

template <class T>
void vector<T>::erase(const iterator<T>& it)
{
	erase(it, it + 1);
}

template <class T>
void vector<T>::erase(const iterator<T>& first, const iterator<T>& last)
{
	int deleted_count = last - first;
	if (deleted_count <= 0)
		return;

	int begin_offs = first - begin();
	int end_offs = last - begin();

	if (last != end())
	{
		for (size_t i = end_offs; i < _size; i++)
			new (&_data[begin_offs++]) T(std::move(_data[i]));
	}

	for (size_t i = end_offs; i < _size; i++)
		_data[i].~T();

	_size -= deleted_count;
}

template <class T>
void vector<T>::insert(const iterator<T>& pos, const T& el)
{
	int pos_offs = pos - begin();
	if (pos_offs >= _size)
		throw std::out_of_range("Iterator out of bounds");

	if (_size == _capacity)
		reserve(_capacity * GROWTH_FACTOR);

	_size++;

	for (size_t i = _size - 1; i > pos_offs; i--)
	{
		new (&_data[i]) T(std::move(_data[i - 1]));
		_data[i - 1].~T();
	}

	new (&_data[pos_offs]) T(el);
}

template <class T>
void vector<T>::insert(const iterator<T>& pos, T&& el)
{
	int pos_offs = pos - begin();
	if (pos_offs >= _size)
		throw std::out_of_range("Iterator out of bounds");

	if (_size == _capacity)
		reserve(_capacity * GROWTH_FACTOR);

	_size++;

	for (int i = _size - 1; i > pos_offs; i--)
	{
		new (&_data[i]) T(std::move(_data[i - 1]));
		_data[i - 1].~T();
	}

	new (&_data[pos_offs]) T(std::move(el));
}

template <class T>
void vector<T>::insert(const iterator<T>& pos, size_t count, const T& el)
{
	int pos_offs = pos - begin();
	if (pos_offs >= _size)
		throw std::out_of_range("Iterator out of bounds");

	if (_size + count > _capacity)
		reserve(_size + count);

	int end_offs = _size - 1;
	int last_el = _capacity - 1;

	for (int i = end_offs; i >= pos_offs; i--)
	{
		new (&_data[last_el--]) T(_data[i]);
		_data[i].~T();
	}

	for (size_t i = 0; i < count; i++)
		new (&_data[pos_offs + i]) T(el);

	_size += count;
}

template <class T>
void vector<T>::insert(const iterator<T>& pos, const iterator<T>& first, const iterator<T>& last)
{
	int pos_offs = pos - begin();
	if (pos_offs >= _size)
		throw std::out_of_range("Iterator out of bounds");

	int added_count = last - first;
	if (added_count <= 0)
		return;

	if (_size + added_count > _capacity)
		reserve(_size + added_count);

	int last_el = _capacity - 1;
	int end_offs = _size - 1;

	for (int i = end_offs; i >= pos_offs; i--)
	{
		new (&_data[last_el--]) T(_data[i]);
		_data[i].~T();
	}

	for (size_t i = 0; i < added_count; i++)
		new (&_data[pos_offs + i]) T(*(first + i));

	_size += added_count;
}

template <class T>
void vector<T>::resize(size_t n)
{
	if (n < _size)
	{
		for (size_t i = n; i < _size; i++)
			_data[i].~T();

		_size = n;
	}
	else
	{
		if (n <= _capacity)
		{
			for (size_t i = n; i < _capacity; i++)
				new (&_data[i]) T();

			_size = n;
		}
		else
		{
			T* new_data = static_cast<T*>(operator new(n * sizeof(T)));
			for (size_t i = 0; i < _size; i++)
			{
				new(&new_data[i]) T(std::move(_data[i]));
				_data[i].~T();
			}

			for (size_t i = _size; i < n; i++)
				new (&new_data[i]) T();

			operator delete(_data, _capacity * sizeof(T));
			_capacity = _size = n;
			_data = new_data;
		}
	}
}

template <class T>
void vector<T>::reserve(size_t n)
{
	if (n <= _capacity)
		return;

	T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

	for (size_t i = 0; i < _size; i++)
		new (&new_data[i]) T(std::move(_data[i]));

	operator delete(_data, capacity() * sizeof(T));

	_data = new_data;
	_capacity = n;
}

template <class T>
void vector<T>::clear()
{
	for (size_t i = 0; i < _size; i++)
		_data[i].~T();
}