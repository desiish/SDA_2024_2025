#pragma once
#include <stdexcept>

template <class T>
struct node
{
	node<T>* _next;
	T _value;

	node() : _next{ nullptr }, _value() {};
	node(const T& value) : _value(value), _next{ nullptr } {};
	node(T&& value) : _value(std::move(value)), _next{ nullptr } {};

	template <class ...Args>
	node(Args ...args) : _next{ nullptr }, _value(std::forward<Args>(args)...) {}
};


template <class T>
class iterator
{
public:
	node<T>* _node_ptr;


	iterator() : _node_ptr{ nullptr } {};
	iterator(node<T>* ptr) : _node_ptr{ ptr } {};

	iterator<T>& operator++()
	{
		if (!_node_ptr)
			throw std::out_of_range("Iterator out of bounds");

		_node_ptr = _node_ptr->_next;
		return *this;
	}

	iterator<T> operator++(int dummy)
	{
		iterator<T> it = *this;
		++(*this);

		return it;
	}

	iterator<T> operator+(int offs)
	{
		node<T>* ptr = _node_ptr;
		while (ptr && offs)
		{
			ptr = ptr->_next;
			offs--;
		}

		if (!ptr)
			throw std::out_of_range("Iterator out of range");

		return { ptr };
	}

	T& operator*()
	{
		return _node_ptr->_value;
	}

	const T& operator*() const
	{
		return _node_ptr->_value;
	}

	T* operator->()
	{
		return &(_node_ptr->_value);
	}

	const T* operator->() const
	{
		return &(_node_ptr->_value);
	}

	bool operator==(const iterator<T>& other) const
	{
		return _node_ptr == other._node_ptr;
	}

	bool operator!=(const iterator<T>& other) const
	{
		return _node_ptr != other._node_ptr;
	}
};


template <class T>
class forward_list
{
public:

	forward_list();
	forward_list(size_t count);
	forward_list(size_t count, const T& value);

	forward_list(const forward_list<T>& other)
	{
		copyFrom(other);
	}

	forward_list<T>& operator=(const forward_list<T>& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	forward_list(forward_list<T>&& other)
	{
		moveFrom(std::move(other));
	}

	forward_list<T>& operator=(forward_list<T>&& other)
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}
		return *this;
	}

	~forward_list()
	{
		free();
	}

	T& front()
	{
		return _head->_value;
	}

	const T& front() const
	{
		return _head->_value;
	}

	iterator<T> begin()
	{
		return { _head };
	}

	iterator<T> end()
	{
		return { nullptr };
	}

	const iterator<T> c_begin() const
	{
		return { _head };
	}

	const iterator<T> c_end() const
	{
		return { nullptr };
	}

	iterator<T> before_begin()
	{
		return { _before_head };
	}

	const iterator<T> c_before_begin() const
	{
		return { _before_head };
	}

	bool empty() const
	{
		return _before_head->_next == nullptr;
	}

	template< class... Args >
	iterator<T> emplace_after(const iterator<T> pos, Args&&... args);

	iterator<T> insert_after(const iterator<T>& pos, const T& el);
	iterator<T> insert_after(const iterator<T>& pos, T&& el);

	iterator<T> erase_after(const iterator<T>& pos);

	template< class... Args >
	void emplace_front(Args&&... args);

	void push_front(const T& value);
	void push_front(T&& value);

	void pop_front();

	void splice_after(const iterator<T>& pos, forward_list<T>& other);

	void clear();

private:
	void free();
	void copyFrom(const forward_list<T>& other);
	void moveFrom(forward_list<T>&& other);

	node<T>* _before_head; // sentinel node
	node<T>* _head;
	node<T>* _tail;
};

template <class T>
forward_list<T>::forward_list()
{
	_before_head = new node<T>();
	_head = _tail = nullptr;
}

template <class T>
forward_list<T>::forward_list(size_t count)
{
	_before_head = new node<T>();
	_head = _tail = new node<T>();
	_before_head->_next = _head;
	for (size_t i = 1; i < count; i++)
	{
		_tail->_next = new node<T>();
		_tail = _tail->_next;
	}
}

template <class T>
forward_list<T>::forward_list(size_t count, const T& value)
{
	_before_head = new node<T>();
	_head = _tail = new node<T>(value);
	_before_head->_next = _head;
	for (size_t i = 1; i < count; i++)
	{
		_tail->_next = new node<T>(value);
		_tail = _tail->_next;
	}
}

template <class T>
void forward_list<T>::free()
{
	while (_before_head != _tail)
	{
		node<T>* next = _before_head->_next;
		delete _before_head;
		_before_head = next;
	}

	delete _tail;
	_before_head = _head = _tail = nullptr;
}

template <class T>
void forward_list<T>::copyFrom(const forward_list<T>& other)
{
	_before_head = new node<T>();
	_head = _tail = new node<T>(*(other._head));
	_before_head->_next = _head;
	node<T>* other_h = other._head;
	node<T>* other_t = other._tail;

	while (other_h != other_t)
	{
		_tail->_next = new node<T>(*(other_h->_next));
		_tail = _tail->_next;
		other_h = other_h->_next;
	}
}

template <class T>
void forward_list<T>::moveFrom(forward_list<T>&& other)
{
	_before_head = other._before_head;
	_head = other._head;
	_tail = other._tail;
	other._before_head = other._head = other._tail = nullptr;
}

template <class T>
template <class... Args>
iterator<T> forward_list<T>::emplace_after(const iterator<T> pos, Args&&... args)
{
	if (!pos._node_ptr)
		throw std::invalid_argument("Node ptr is null");

	if (pos == before_begin())
	{
		emplace_front(std::forward<Args>(args)...);
		return _head;
	}

	node<T>* to_insert = new node<T>(std::forward<Args>(args)...);
	node<T>* temp = pos._node_ptr->_next;
	pos._node_ptr->_next = to_insert;
	to_insert->_next = temp;

	if (!temp)
		_tail = to_insert;

	return pos;
}


template <class T>
iterator<T> forward_list<T>::insert_after(const iterator<T>& pos, const T& el)
{
	if (!pos._node_ptr)
		throw std::invalid_argument("Node ptr is null");

	if (pos == c_before_begin())
	{
		push_front(el);
		return _head;
	}

	node<T>* to_insert = new node<T>(el);
	node<T>* temp = pos._node_ptr->_next;
	pos._node_ptr->_next = to_insert;
	to_insert->_next = temp;

	if (!temp)
		_tail = to_insert;
	
	return pos;
}

template <class T>
iterator<T> forward_list<T>::insert_after(const iterator<T>& pos, T&& el)
{
	if (!pos._node_ptr)
		throw std::invalid_argument("Node ptr is null");

	if (pos == c_before_begin())
	{
		emplace_front(std::move(el));
		return _head;
	}

	node<T>* to_insert = new node<T>(std::move(el));
	node<T>* temp = pos._node_ptr->_next;
	pos._node_ptr->_next = to_insert;
	to_insert->_next = temp;

	if (!temp)
		_tail = to_insert;

	return pos;
}

template <class T>
iterator<T> forward_list<T>::erase_after(const iterator<T>& pos)
{
	if (!pos._node_ptr)
		throw std::invalid_argument("Node ptr is null");

	if (pos == c_before_begin())
	{
		pop_front();
		return _head;
	}

	node<T>* to_erase = pos._node_ptr->_next;
	if (to_erase)
	{
		if (!to_erase->_next) //to_erase is tail
		{
			pos._node_ptr->_next = to_erase->_next;
			delete to_erase;
			_tail = pos._node_ptr;
			return end();
		}
		else
		{
			pos._node_ptr->_next = to_erase->_next;
			delete to_erase;
			return pos._node_ptr->_next;
		}
	}

	return end();
}

template <class T>
template <class... Args>
void forward_list<T>::emplace_front(Args&&... args)
{
	node<T>* to_insert = new node<T>(std::forward<Args>(args)...);
	node<T>* temp = _head;;
	_head = to_insert;
	to_insert->_next = temp;

	if (!temp)
		_tail = _head;

	_before_head->_next = _head;
}

template <class T>
void forward_list<T>::push_front(const T& value)
{
	node<T>* to_insert = new node<T>(value);
	node<T>* temp = _head;;
	to_insert->_next = temp;
	_head = to_insert;

	if (!temp)
		_tail = _head;

	_before_head->_next = _head;
}

template <class T>
void forward_list<T>::push_front(T&& value)
{
	node<T>* to_insert = new node<T>(std::move(value));
	node<T>* temp = _head;
	to_insert->_next = temp;
	_head = to_insert;

	if (!temp)
		_tail = _head;

	_before_head->_next = _head;
}

template <class T>
void forward_list<T>::pop_front()
{
	if (!_head)
		throw std::runtime_error("_head was nullptr");

	auto temp = _head;
	_head = _head->_next;
	delete temp;

	if (!_head)
		_tail = nullptr;

	_before_head->_next = _head;
}

// Moves elements from another forward_list to *this. The elements are inserted after the element pointed to by pos
template <class T>
void forward_list<T>::splice_after(const iterator<T>& pos, forward_list<T>& other)
{
	if (!pos._node_ptr || !other._head)
		return;

	auto temp = pos._node_ptr->_next;
	pos._node_ptr->_next = other._head;
	other._tail->_next = temp;

	if (pos == c_before_begin())
		_head = other._head;

	if (!temp)
		_tail = other._tail;

	other._head = other._tail = nullptr;
	other._before_head->_next = nullptr;
}

template <class T>
void forward_list<T>::clear()
{
	if (_head)
	{
		while (_head != _tail)
		{
			node<T>* next = _head->_next;
			delete _head;
			_head = next;
		}
	}

	delete _tail;
	_head = _tail = nullptr;
	_before_head->_next = _head;
}