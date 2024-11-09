#pragma once
#include <stdexcept>

template <class T>
class deque
{
private:

	class const_deque_iterator
	{
		size_t _offs;
		deque& _my_deque;

	public:
		const_deque_iterator(size_t offs_, deque& my_deque_) : _offs(offs_), _my_deque(my_deque_) {}

		const T& operator*() const
		{
			return _my_deque.subscript(_offs);
		}

		const T* operator*() const
		{
			return &_my_deque.subscript(_offs);
		}

		bool operator==(const const_deque_iterator& other)
		{
			return _offs == other._offs;
		}

		bool operator!=(const const_deque_iterator& other)
		{
			return !(*this == other);
		}
	};

	class deque_iterator
	{
		size_t _offs;
		deque& _my_deque;

	public:
		deque_iterator(size_t offs_, deque& my_deque_) : _offs(offs_), _my_deque(my_deque_) {}

		T& operator*()
		{
			return _my_deque.subscript(_offs);
		}

		const T& operator*() const
		{
			return _my_deque.subscript(_offs);
		}

		T* operator*()
		{
			return &_my_deque.subscript(_offs);
		}

		const T* operator*() const
		{
			return &_my_deque.subscript(_offs);
		}

		deque_iterator& operator++()
		{
			_offs++;
			return *this;
		}

		deque_iterator operator++(int)
		{
			deque_iterator it = *this;
			++(*this);
			return it;
		}

		deque_iterator& operator--()
		{
			_offs--;
			return *this;
		}

		deque_iterator operator--(int)
		{
			deque_iterator it = *this;
			--(*this);
			return it;
		}

		bool operator==(const deque_iterator& other)
		{
			return _offs == other._offs;
		}

		bool operator!=(const deque_iterator& other)
		{
			return !(*this == other);
		}

		//operator const_deque_iterator<T>() const
		//{
		//	return const_deque_iterator<T>(_offs, _my_deque);
		//}
	};

private:
	void copy(const deque& other);
	void move(deque&& other);
	void free();

	void resize();

	template <class ...Args>
	void construct_at(int idx, Args&& ...args);
	void destruct_at(int idx);

	void allocate_block(int idx);
	void deallocate_block(int idx);

	void init();
	T& subscript(size_t offs);

public:
	deque() = default;

	deque(const deque& other);
	deque& operator=(const deque& other);

	deque(deque&& other);
	deque& operator=(deque&& other);

	~deque();

	void push_back(const T& el);
	void push_front(const T& el);

	void pop_back();
	void pop_front();

	//TODO: implement
	deque_iterator& insert(const_deque_iterator& pos, const T& el);
	deque_iterator& erase(const_deque_iterator& pos);

	const T& operator[](int idx) const;
	T& operator[](int idx);

	size_t size() const;
	bool empty() const;

	deque_iterator begin();
	deque_iterator end();

	const_deque_iterator c_begin() const;
	const_deque_iterator c_end() const;

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

private:
	T** _data = nullptr;; // container of blocks
	size_t _offs = 0; // index of the first element
	size_t _size; // size of elements
	size_t _capacity; // keeps the maximum possible block count

	static constexpr size_t MAX_ELEMENTS_IN_BLOCK = 8;
	static constexpr size_t INIT_CAPACITY = 8;
};

template <class T>
void deque<T>::copy(const deque& other)
{
	_offs = other._offs;
	_size = other._size;
	_capacity = other._capacity;

	for (size_t i = 0; i < other._size; i++)
		push_back(other[i]);
}

template<class T>
void deque<T>::move(deque&& other)
{
	_offs = other._offs;
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;

	other._data = nullptr;
	other._size = other._capacity = other._offs = 0;
}

template <class T>
void deque<T>::free()
{
	for (size_t i = 0; i < _size; i++)
		destruct_at(i);

	size_t beg_block = (_offs + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t end_block = (_offs + _size + 1) / MAX_ELEMENTS_IN_BLOCK;

	for (size_t i = beg_block; i < end_block; i++)
		deallocate_block(i);

	delete[] _data;

	_data = nullptr;
	_size = _offs = _capacity = 0;
}

template <class T>
void deque<T>::resize()
{
	size_t new_cap = _capacity * 2;
	T** new_data = new T * [new_cap] {nullptr};

	size_t block_offs = (new_cap - _capacity) / 2;

	for (size_t i = 0; i < _capacity; i++)
		new_data[i + block_offs] = _data[i];

	delete[] _data;
	_data = new_data;
	_capacity = new_cap;
	_offs = _offs + (new_cap * MAX_ELEMENTS_IN_BLOCK) / 4;;
}


//accepts index as idx + _offs
template <class T>
template <class ...Args>
void deque<T>::construct_at(int idx, Args&& ...args)
{
	size_t block_idx = (idx + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t el_idx = idx % MAX_ELEMENTS_IN_BLOCK;

	if (!_data[block_idx])
		allocate_block(block_idx);

	new(&_data[block_idx][el_idx]) T(std::forward<Args>(args)...);
}

template <class T>
void deque<T>::destruct_at(int idx)
{
	size_t block_idx = (idx + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t el_idx = idx % MAX_ELEMENTS_IN_BLOCK;

	_data[block_idx][el_idx].~T();
}

//accepts idx as first block + some offset
template <class T>
void deque<T>::allocate_block(int idx)
{
	_data[idx] = static_cast<T*>(operator new(MAX_ELEMENTS_IN_BLOCK * sizeof(T)));
}

template <class T>
void deque<T>::deallocate_block(int idx)
{
	operator delete(_data[idx], sizeof(T) * MAX_ELEMENTS_IN_BLOCK);
}

template <class T>
void deque<T>::init()
{
	_data = new T * [INIT_CAPACITY] {nullptr};
	_capacity = INIT_CAPACITY;
	_offs = (INIT_CAPACITY * MAX_ELEMENTS_IN_BLOCK) / 2;

	size_t beg_block = (_offs + 1) / MAX_ELEMENTS_IN_BLOCK;
	allocate_block(beg_block);
}

template <class T>
void deque<T>::push_back(const T& el)
{
	if (!_data)
		init();

	size_t idx = _offs + _size;
	if (idx == MAX_ELEMENTS_IN_BLOCK * _capacity - 1) // currently at the end
	{
		resize();
		idx = _offs + _size;
	}

	construct_at(idx, el);
	_size++;
}

template <class T>
void deque<T>::push_front(const T& el)
{
	if (!_data)
		init();

	if (_offs == 0)
		resize();

	_offs--;
	construct_at(_offs, el);
	_size++;
}

template <class T>
void deque<T>::pop_back()
{
	if (size() == 0)
		throw std::out_of_range("Cannot pop on empty deque");

	destruct_at(_offs + _size);
	_size--;
}

template <class T>
void deque<T>::pop_front()
{
	if (size() == 0)
		throw std::out_of_range("Cannot pop on empty deque");

	destruct_at(_offs);
	_offs++;
	_size--;
}

template<class T>
const T& deque<T>::operator[](int idx) const
{
	size_t offs = _offs + idx;
	if (offs < _offs || offs >= _offs + _size)
		throw std::out_of_range("Invalid index");

	size_t block_idx = (offs + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t el_idx = offs % MAX_ELEMENTS_IN_BLOCK;

	return _data[block_idx][el_idx];
}

template<class T>
T& deque<T>::operator[](int idx)
{
	size_t offs = _offs + idx;
	if (offs < _offs || offs > _offs + _size)
		throw std::out_of_range("Invalid index");

	size_t block_idx = (offs + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t el_idx = offs % MAX_ELEMENTS_IN_BLOCK;

	return _data[block_idx][el_idx];
}

template <class T>
deque<T>::deque(const deque& other)
{
	copy(other);
}

template <class T>
deque<T>& deque<T>::operator=(const deque& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <class T>
deque<T>::deque(deque&& other)
{
	move(std::move(other));
}

template <class T>
deque<T>& deque<T>::operator=(deque&& other)
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}

template <class T>
deque<T>::~deque()
{
	free();
}

template <class T>
size_t deque<T>::size() const
{
	return _size;
}

template <class T>
bool deque<T>::empty() const
{
	return size() == 0;
}

template <class T>
T& deque<T>::subscript(size_t offs)
{
	size_t block_idx = (offs + 1) / MAX_ELEMENTS_IN_BLOCK;
	size_t el_idx = offs % MAX_ELEMENTS_IN_BLOCK;

	return _data[block_idx][el_idx];
}

template <class T>
typename deque<T>::deque_iterator deque<T>::begin()
{
	return deque_iterator(_offs, *this);
}

template <class T>
typename deque<T>::deque_iterator deque<T>::end()
{
	return deque_iterator(_offs + _size, *this);
}

template <class T>
typename deque<T>::const_deque_iterator deque<T>::c_begin() const
{
	return const_deque_iterator(_offs, *this);
}

template <class T>
typename deque<T>::const_deque_iterator deque<T>::c_end() const
{
	return const_deque_iterator(_offs + _size, *this);
}

template <class T>
T& deque<T>::front()
{
	return operator[](0);
}

template <class T>
const T& deque<T>::front() const
{
	return operator[](0);
}

template <class T>
T& deque<T>::back()
{
	return operator[](size() - 1);
}

template <class T>
const T& deque<T>::back() const
{
	return operator[](size() - 1);
}
