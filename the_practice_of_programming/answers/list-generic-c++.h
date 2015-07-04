#ifndef _LIST_GENERIC_C___H
#define _LIST_GENERIC_C___H

#include <cstdlib>
#include <stdexcept>

template <typename T>
class List_node {
	public:
	List_node(const T &data)
	{
		this->data = *(new T(data));
		next = NULL;
	}

	T data;
	List_node<T> *next;
};

/* A generic list type. The type T stored in the list must have a copy
   constructor. */
template <typename T>
class List {
	public:
	List()
	{
		head = NULL;
	}

	~List()
	{
		List_node<T> *p, *next;

		for (p = head; p != NULL; p = next) {
			next = p->next;
			delete p;
		}
	}

	/* Insert an element at the front of the list. */
	void insert(const T &data)
	{
		List_node<T> *node;

		node = new List_node<T>(data);
		node->next = head;
		head = node;
	}

	/* Return the number of elements in the list. */
	unsigned int size() const
	{
		List_node<T> *p;
		unsigned int count;

		count = 0;
		for (p = head; p != NULL; p = p->next)
			count++;

		return count;
	}

	/* Get the object at the given index. Throws out_of_range if the index
	   is greater than size. */
	T &get(unsigned int index) const
	{
		List_node<T> *p;

		for (p = head; p != NULL && index > 0; p = p->next)
			index--;
		if (p == NULL)
			throw std::out_of_range("List index out of range.");

		return p->data;
	}

	/* Delete the first occurrence of data in the list. Return true if
	   anything was deleted, false otherwise. */
	bool remove(const T &data)
	{
		List_node<T> *p, *prev;

		prev = NULL;
		for (p = head; p != NULL; p = p->next) {
			if (p->data == data) {
				if (prev == NULL)
					head = p->next;
				else
					prev->next = p->next;
				delete p;
				return true;
			}
		}

		return false;
	}

	/* Return true if the list contains the given object. */
	bool contains(const T &data) const
	{
		List_node<T> *p;

		for (p = head; p != NULL; p = p->next) {
			if (p->data == data)
				return true;
		}

		return false;
	}

	private:
	List_node<T> *head;
};

#endif
