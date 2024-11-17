#pragma once
#include <functional>
#include <stack>
#include <stdexcept>

template <class T, class Comparator = std::less<T>>
class BST
{
	struct Node
	{
		T value;
		Node* left;
		Node* right;

		Node(const T& value_, Node* left_ = nullptr, Node* right_ = nullptr) :
			value(value_),
			left(left_),
			right(right_) {}
	};

	using _NodePtr = Node*;

	class Iterator
	{
		std::stack<_NodePtr> _currStack;
		std::stack<_NodePtr> _popped;

		void push_left(_NodePtr root)
		{
			if (!root)
				return;

			_currStack.push(root);
			push_left(root->left);
		}

	public:
		Iterator(_NodePtr root)
		{
			push_left(root);
		}

		T& operator*()
		{
			return _currStack.top()->value;
		}

		const T& operator*() const
		{
			return _currStack.top()->value;
		}

		Iterator& operator++()
		{
			if (_currStack.empty())
				throw std::out_of_range("Cannot pop on empty stack");

			_NodePtr curr = _currStack.top();
			_currStack.pop();
			_popped.push(curr);

			push_left(curr->right);

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator copy = *this;
			++(*this);

			return copy;
		}

		Iterator& operator--()
		{
			if (_popped.empty())
				throw std::out_of_range("Cannot pop on empty stack");

			_NodePtr prev = _popped.top();
			_popped.pop();
			_currStack.push(prev);

			push_left(prev->left);

			return *this;
		}

		Iterator operator--(int)
		{
			Iterator copy = *this;
			--(*this);

			return copy;
		}

		bool operator==(const Iterator& other)
		{
			return (_currStack == other._currStack);
		}

		bool operator!=(const Iterator& other)
		{
			return (_currStack != other._currStack);
		}
	};

private:
	_NodePtr copy(_NodePtr root);
	void move(BST&& other);
	void free(_NodePtr root);

	_NodePtr* findMinNode(_NodePtr* root);
	_NodePtr remove(_NodePtr* root, const T& el);
	_NodePtr add(_NodePtr* root, const T& el);
	_NodePtr find(_NodePtr root, const T& el);

public:
	BST() = default;
	BST(const BST& other);
	BST& operator=(const BST& other);
	BST(BST&& other);
	BST& operator=(BST&& other);

	std::pair<Iterator, bool> insert(const T& el);
	std::pair<Iterator, bool> erase(const T& el);

	Iterator begin()
	{
		return { _root };
	}

	Iterator end()
	{
		return { nullptr }; // we cannot do end()--;
	}

	Iterator find(const T& el);

	size_t size() const
	{
		return _size;
	}

	bool empty() const
	{
		return size() == 0;
	}

private:
	_NodePtr _root = nullptr;
	size_t _size = 0;
	Comparator _comp;
};

template <class T, class Comparator>
typename BST<T, Comparator>::_NodePtr BST<T, Comparator>::copy(_NodePtr root)
{
	if (!root)
		return nullptr;

	_NodePtr toReturn = new Node(root->value);
	toReturn->left = copy(root->left);
	toReturn->right = copy(root->right);

	return toReturn;
}

template <class T, class Comparator>
void BST<T, Comparator>::move(BST&& other)
{
	_root = other._root;
	_size = other._size;
	
	other._root = nullptr;
	other._size = 0;
}

template <class T, class Comparator>
void BST<T, Comparator>::free(_NodePtr root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

template <class T, class Comparator>
BST<T, Comparator>::BST(const BST& other) : _comp(other._comp)
{
	_root = copy(other._root);
	_size = other._size;
}

template <class T, class Comparator>
BST<T, Comparator>& BST<T, Comparator>::operator=(const BST& other)
{
	if (this != &other)
	{
		free(_root);
		_root = copy(other._root);
		_comp = other._comp;
		_size = other._size;
	}

	return *this;
}

template <class T, class Comparator>
BST<T, Comparator>::BST(BST&& other)
{
	move(std::move(other));
}

template <class T, class Comparator>
BST<T, Comparator>& BST<T, Comparator>::operator=(BST&& other)
{
	if (this != &other)
	{
		free(_root);
		move(std::move(other));
	}

	return *this;
}

template <class T, class Comparator>
typename BST<T, Comparator>::_NodePtr* BST<T, Comparator>::findMinNode(_NodePtr* root)
{
	if (!(*root)->left)
		return root;

	findMinNode(&(*root)->left);
}

template <class T, class Comparator>
typename BST<T, Comparator>::_NodePtr BST<T, Comparator>::remove(_NodePtr* root, const T& el)
{
	if (!(*root))
		return nullptr;

	if (_comp(el, (*root)->value))
		return remove(&(*root)->left, el);
	else if(_comp((*root)->value, el))
		return remove(&(*root)->right, el);

	_NodePtr toDelete = *root;

	if (!(*root)->left && !(*root)->right)
		*root = nullptr;
	else if (!(*root)->left)
		*root = (*root)->right;
	else if (!(*root)->right)
		*root = (*root)->left;
	else
	{
		_NodePtr* rightMin = findMinNode(&((*root)->right));

		*root = *rightMin;
		*rightMin = (*rightMin)->right;

		(*root)->left = toDelete->left;
		(*root)->right = toDelete->right;
	}

	delete toDelete;
	_size--;
	return *root;
}

template <class T, class Comparator>
std::pair<typename BST<T, Comparator>::Iterator, bool> BST<T, Comparator>::erase(const T& el)
{
	_NodePtr res = remove(&_root, el);

	return { {res}, res != nullptr };
}

template <class T, class Comparator>
typename BST<T, Comparator>::_NodePtr BST<T, Comparator>::add(_NodePtr* root, const T& el)
{
	if (!(*root))
	{
		_size++;
		*root = new Node(el);
		return *root;
	}

	if (_comp(el, (*root)->value))
		return add(&(*root)->left, el);
	else if (_comp((*root)->value, el))
		return add(&(*root)->right, el);
	else
		return nullptr;
}

template <class T, class Comparator>
std::pair<typename BST<T, Comparator>::Iterator, bool> BST<T, Comparator>::insert(const T& el)
{
	_NodePtr res = add(&_root, el);

	return { {res}, res != nullptr };
}

template <class T, class Comparator>
typename BST<T, Comparator>::_NodePtr BST<T, Comparator>::find(_NodePtr root, const T& el)
{
	if (!root)
		return nullptr;

	if (_comp(el, root->value))
		return find(root->left, el);
	else if (_comp(root->value, el))
		return find(root->right, el);
	else
		return root;
}

template <class T, class Comparator>
typename BST<T, Comparator>::Iterator BST<T, Comparator>::find(const T& el)
{
	_NodePtr res = find(_root, el);

	return { res };
}
