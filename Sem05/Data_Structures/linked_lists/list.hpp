#pragma once
#include <stdexcept>

template <class T>
struct node
{
	node<T>* _next;
	node<T>* _prev;
	T _value;

	node() : _next{ nullptr }, _prev{ nullptr }, _value() {}
	node(const T& value) : _next{ nullptr }, _prev{ nullptr }, _value(value) {}
	node(T&& value) : _next{ nullptr }, _prev{ nullptr }, _value(std::move(value)) {}

	template <class ...Args>
	node(Args&& ...args) : _next{ nullptr }, _prev{ nullptr }, _value(std::forward<Args>(args)...) {}

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

	iterator<T>& operator--()
	{
		if (!_node_ptr)
			throw std::out_of_range("Iterator out of bounds");

		_node_ptr = _node_ptr->_prev;
		return *this;
	}

	iterator<T> operator--(int dummy)
	{
		iterator<T> it = *this;
		--(*this);

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

	iterator<T> operator-(int offs)
	{
		node<T>* ptr = _node_ptr;
		while (ptr && offs)
		{
			ptr = ptr->_prev;
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
class list
{
public:

	list();
	list(size_t count);
	list(size_t count, const T& value);

	list(const list<T>& other)
	{
		copyFrom(other);
	}

	list<T>& operator=(const list<T>& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	list(list<T>&& other)
	{
		moveFrom(std::move(other));
	}

	list<T>& operator=(list<T>&& other)
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}
		return *this;
	}

	~list()
	{
		free();
	}

	T& front()
	{
		return *(begin());
	}

	const T& front() const
	{
		return *(begin());
	}

	T& back()
	{
		return *(--end());
	}

	const T& back() const
	{
		return *(--end());
	}

	iterator<T> begin()
	{
		return { _sentinel->_next };
	}

	iterator<T> end()
	{
		return { _sentinel };
	}

	const iterator<T> c_begin() const
	{
		return { _sentinel->_next };
	}

	const iterator<T> c_end() const
	{
		return { _sentinel };
	}

	bool empty() const
	{
		return _size == 0;
	}

	size_t size() const
	{
		return _size;
	}

	void clear();

	iterator<T> insert(const iterator<T>& pos, const T& el);
	iterator<T> insert(const iterator<T>& pos, T&& el);

	template <class ...Args>
	iterator<T> emplace(const iterator<T>& pos, Args&&... args);

	iterator<T> erase(const iterator<T>& pos);

	void push_back(const T& el);
	void push_front(const T& el);

	void push_back(T&& el);
	void push_front(T&& el);

	void pop_back();
	void pop_front();

	template <class ...Args>
	void emplace_front(Args&&... args);

	template <class ...Args>
	void emplace_back(Args&&... args);

	void splice(const iterator<T>& pos, list<T>& other);

private:
	void free();
	void copyFrom(const list<T>& other);
	void moveFrom(list<T>&& other);

	size_t _size;
	node<T>* _sentinel; // sentinel node to allow end()--;
};

template <class T>
list<T>::list()
{
	_sentinel = new node<T>();
	_size = 0;
}

template <class T>
list<T>::list(size_t count)
{
	_sentinel = new node<T>();
	auto _head = _sentinel->_next = new node<T>();

	for (size_t i = 1; i < count; i++)
	{
		_head->_next = new node<T>();
		_head->_next->_prev = _head;
		_head = _head->_next;
	}

	_head->_next = _sentinel;
	_sentinel->_prev = _head;

	_size = count;
}

template <class T>
list<T>::list(size_t count, const T& value)
{
	_sentinel = new node<T>();
	auto _head = _sentinel->_next = new node<T>(value);

	for (size_t i = 1; i < count; i++)
	{
		_head->_next = new node<T>(value);
		_head->_next->_prev = _head;
		_head = _head->_next;
	}

	_head->_next = _sentinel;
	_sentinel->_prev = _head;

	_size = count;
}

template <class T>
void list<T>::free()
{
	auto start = _sentinel->_next;
	_sentinel->_next = nullptr;

	while (start)
	{
		auto temp = start->_next;
		delete start;
		start = temp;
	}

	_sentinel = nullptr;
	_size = 0;
}

template <class T>
void list<T>::copyFrom(const list<T>& other)
{
	_sentinel = new node<T>();
	auto _head = new node<T>(other._sentinel->_next->_value);
	_sentinel->_next = _head;

	auto other_h = other._sentinel->_next;
	auto other_t = other._sentinel->_prev;

	while (other_h != other._sentinel)
	{
		_head->_next = new node<T>(other_h->next->_value);
		_head->_next->_prev = _head;
		_head = _head->_next;
		other_h = other_h->_next;
	}

	_head->_next = _sentinel;
	_sentinel->_prev = _head;

	_size = other._size;
}

template <class T>
void list<T>::moveFrom(list<T>&& other)
{
	_sentinel = other._sentinel;
	_size = other._size;
	other._size = 0;
	other._sentinel = nullptr;
}

template <class T>
void list<T>::clear()
{
	if (_size == 0)
		return;

	auto _head = _sentinel->_next;
	auto _tail = _sentinel->_prev;

	_sentinel->_next = nullptr;
	_sentinel->_prev = nullptr; 
	_tail->_next = nullptr;
	_head->_prev = nullptr; // now _sentinel is deattached

	while (_head)
	{
		auto temp = _head->_next;
		delete _head;
		_head = temp;
	}

	_size = 0;
}

template <class T>
iterator<T> list<T>::insert(const iterator<T>& pos, const T& el)
{
	if (!pos._node_ptr)
		throw std::runtime_error("Invalid iterator");

	if (pos == begin())
	{
		push_front(el);
		return begin();
	}

	if (pos == (end() - 1))
	{
		push_back(el);
		return end();
	}

	node<T>* to_insert = new node<T>(el);
	node<T>* curr = pos._node_ptr;
	node<T>* prev = pos._node_ptr->_prev; // prev keeps previous node

	curr->_prev = to_insert; // we insert to_insert before curr
	to_insert->_next = curr; // attaching to_insert to curr
	prev->_next = to_insert; // we attached to_insert to prev node
	to_insert->_prev = prev; // we attached previous node to to_insert

	_size++;

	return pos;
}

template <class T>
iterator<T> list<T>::insert(const iterator<T>& pos, T&& el)
{
	if (!pos._node_ptr)
		throw std::runtime_error("Invalid iterator");

	if (pos == begin())
	{
		push_front(std::move(el));
		return begin();
	}

	if (pos == (end() - 1))
	{
		push_back(std::move(el));
		return end();
	}

	node<T>* to_insert = new node<T>(std::move(el));
	node<T>* curr = pos._node_ptr;
	node<T>* prev = pos._node_ptr->_prev; 

	curr->_prev = to_insert;
	to_insert->_next = curr;
	prev->_next = to_insert;
	to_insert->_prev = prev;

	_size++;

	return pos;
}

template <class T>
template <class ...Args>
iterator<T> list<T>::emplace(const iterator<T>& pos, Args&&... args)
{
	if (!pos._node_ptr)
		throw std::runtime_error("Invalid iter");

	if (pos == begin())
	{
		emplace_front(std::forward<Args>(args)...);
		return begin();
	}

	if (pos == (end() - 1))
	{
		emplace_back(std::forward<Args>(args)...);
		return end();
	}

	node<T>* to_insert = new node<T>(std::forward<Args>(args)...);
	node<T>* curr = pos._node_ptr;
	node<T>* prev = pos._node_ptr->_prev;

	curr->_prev = to_insert;
	to_insert->_next = curr;
	prev->_next = to_insert;
	to_insert->_prev = prev;

	_size++;

	return pos;
}

template <class T>
iterator<T> list<T>::erase(const iterator<T>& pos)
{
	if (!pos._node_ptr)
		throw std::runtime_error("Invalid iter");

	if (pos == begin())
	{
		pop_front();
		return begin();
	}

	if (pos == --end())
	{
		pop_back();
		return end();
	}

	node<T>* prev = pos._node_ptr->_prev;
	node<T>* next = pos._node_ptr->_next;
	node<T>* curr = pos._node_ptr;

	prev->_next = next;
	next->_prev = prev;

	delete curr;

	_size--;

	return { next };
}

template <class T>
void list<T>::push_back(const T& el)
{
	auto _tail = _sentinel->_prev;
	node<T>* to_push = new node<T>(el);

	_sentinel->_prev = to_push;
	to_push->_next = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_tail->_next = to_push;
		to_push->_prev = _tail; // now we attached both _tail and to_push
	}
	else
	{
		_sentinel->_next = to_push;
		to_push->_prev = _sentinel;
	}

	_size++;
}

template <class T>
void list<T>::push_front(const T& el)
{
	auto _head = _sentinel->_next;
	node<T>* to_push = new node<T>(el);

	_sentinel->_next = to_push;
	to_push->_prev = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_head->_prev = to_push;
		to_push->_next = _head; // now we attached both _head and to_push
	}
	else
	{
		_sentinel->_prev = to_push;
		to_push->_next = _sentinel;
	}

	_size++;
}

template <class T>
void list<T>::push_back(T&& el)
{
	auto _tail = _sentinel->_prev;
	node<T>* to_push = new node<T>(std::move(el));

	_sentinel->_prev = to_push;
	to_push->_next = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_tail->_next = to_push;
		to_push->_prev = _tail; // now we attached both _tail and to_push
	}
	else
	{
		_sentinel->_next = to_push;
		to_push->_prev = _sentinel;
	}

	_size++;
}

template <class T>
void list<T>::push_front(T&& el)
{
	auto _head = _sentinel->_next;
	node<T>* to_push = new node<T>(std::move(el));

	_sentinel->_next = to_push;
	to_push->_prev = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_head->_prev = to_push;
		to_push->_next = _head; // now we attached both _head and to_push
	}
	else
	{
		_sentinel->_prev = to_push;
		to_push->_next = _sentinel;
	}

	_size++;
}

template <class T>
void list<T>::pop_back()
{
	if (!_sentinel->_prev)
		return;

	auto _tail = _sentinel->_prev;
	auto new_tail = _tail->_prev;
	_sentinel->_prev = new_tail;

	if (new_tail)
		new_tail->_next = _sentinel;

	delete _tail;
	_size--;
}

template <class T>
void list<T>::pop_front()
{
	if (!_sentinel->_next)
		return;

	auto _head = _sentinel->_next;
	auto new_head = _head->_next;
	_sentinel->_next = new_head;

	if (new_head)
		new_head->_prev = _sentinel;

	delete _head;
	_size--;
}

template <class T>
template <class ...Args>
void list<T>::emplace_front(Args&&... args)
{
	auto _head = _sentinel->_next;
	node<T>* to_push = new node<T>(std::forward<Args>(args)...);

	_sentinel->_next = to_push;
	to_push->_prev = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_head->_prev = to_push;
		to_push->_next = _head; // now we attached both _head and to_push
	}
	else
	{
		_sentinel->_prev = to_push;
		to_push->_next = _sentinel;
	}

	_size++;
}

template <class T>
template <class ...Args>
void list<T>::emplace_back(Args&&... args)
{
	auto _tail = _sentinel->_prev;
	node<T>* to_push = new node<T>(std::forward<Args>(args)...);

	_sentinel->_prev = to_push;
	to_push->_next = _sentinel; // now _sentinel is attached to to_push

	if (size())
	{
		_tail->_next = to_push;
		to_push->_prev = _tail; // now we attached both _tail and to_push
	}
	else
	{
		_sentinel->_next = to_push;
		to_push->_prev = _sentinel;
	}

	_size++;
}

template <class T>
void list<T>::splice(const iterator<T>& pos, list<T>& other)
{
	if (!pos._node_ptr || !other.size())
		return;

	auto other_h = other._sentinel->_next;
	auto other_t = other._sentinel->_prev;
	other._sentinel->_next = other._sentinel->_prev = nullptr;
	other._size = 0;

	auto curr = pos._node_ptr;
	auto prev = curr->_prev;

	prev->_next = other_h;
	other_h->_prev = prev; // now we attached prev to other`s head

	curr->_prev = other_t;
	other_t->_next = curr; // now we attached curr to other`s tail

	_size += other._size;
}