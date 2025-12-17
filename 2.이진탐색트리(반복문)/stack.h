#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack;

template <class T>
class StackNode
{
	friend class Stack<T>;
	T m_data;
	StackNode* m_child;

	StackNode(T newData) {
		this->m_data = newData;
		this->m_child = NULL;
	}
};

template <class T>
class Stack
{
	StackNode<T>* m_head;

public:
	Stack()
	{
		m_head = NULL;
	}

	void Push(T data)
	{
		if (m_head == NULL)
		{
			m_head = new StackNode<T>(data);
		}
		else
		{
			StackNode<T>* traverse_ptr = m_head;
			while (traverse_ptr->m_child)
			{
				traverse_ptr = traverse_ptr->m_child;
			}
			traverse_ptr->m_child = new StackNode<T>(data);
		}
	}

	T Pop()
	{
		if (m_head == NULL)
		{
			return NULL;
		}

		if (m_head->m_child == NULL)
		{
			T temp = m_head->m_data;
			delete m_head;
			m_head = NULL;
			return temp;
		}
		else
		{
			StackNode<T>* traversePtr = m_head;
			while (traversePtr->m_child->m_child != NULL)
			{
				traversePtr = traversePtr->m_child;
			}
			T temp = traversePtr->m_child->m_data;
			delete traversePtr->m_child;
			traversePtr->m_child = NULL;
			return temp;
		}
	}

	T GetTop()
	{
		if (m_head == NULL)
		{
			return NULL;
		}

		if (m_head->m_child == NULL)
		{
			return m_head->m_data;
		}
		else
		{
			StackNode<T>* traversePtr = m_head;
			while (traversePtr->m_child->m_child)
			{
				traversePtr = traversePtr->m_child;
			}
			return traversePtr->m_child->m_data;
		}
	}

	bool IsEmpty()
	{
		if (m_head == NULL) return true;
		else return false;
	}
};


#endif //STACK_H