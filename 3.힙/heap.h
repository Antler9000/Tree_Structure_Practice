#ifndef HEAP_H
#define HEAP_H

#include <iostream>

using namespace std;

class Heap
{
protected:
	int* m_pDatum;
	int m_itemNum;
	int m_maxNum;

	int getLeftChildIndex(int dataIndex)
	{
		return (dataIndex * 2 + 1);
	}

	int getRightChildIndex(int dataIndex)
	{
		return (dataIndex * 2 + 2);
	}

	int getParentIndex(int dataIndex)
	{
		return ((dataIndex - 1) / 2);
	}

	void Swap(int& dataA, int& dataB)
	{
		int temp = dataA;
		dataA = dataB;
		dataB = temp;
	}

	virtual bool IsNotOrdered(int parentIndex, int childIndex) = 0;				//상속된 최소힙, 최대힙에서 구체적으로 명시.

	virtual bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex) = 0;		//상속된 최소힙, 최대힙에서 구체적으로 명시.

	void ReorderByPromoting();

	void ReorderByDemoting();

	void GiveTwiceMemorySpace()
	{
		int newSize = 2 * m_maxNum;
		int* newData = new int[newSize];

		for (int i = 0; i < m_maxNum; i++)
		{
			newData[i] = m_pDatum[i];
		}

		delete m_pDatum;
		m_pDatum = newData;
	}

public:
	//일단 기본 크기는 50으로 시작. 이를 넘도록 push가 일어나면 기존 크기의 2배를 배정해준다.
	Heap()
	{
		cout << "heap is being made" << endl;
		m_pDatum = new int[50];
		m_itemNum = 0;
		m_maxNum = 50;
	}

	~Heap()
	{
		cout << "heap is being removed" << endl;
		delete m_pDatum;
		m_pDatum = NULL;
	}

	void Push(int newData)
	{
		if (m_itemNum >= m_maxNum)
		{
			cout << "cannot Push item into heap. heap is fulled." << endl;
			cout << "moving to bigger space...." << endl;
			GiveTwiceMemorySpace();
		}

		m_pDatum[m_itemNum] = newData;
		m_itemNum++;
		ReorderByPromoting();
	}

	int GetTop()
	{
		if (m_itemNum <= 0)
		{
			cout << "cannot GetTop item from heap. heap is emptied." << endl;
			return 0;
		}

		return m_pDatum[0];
	}

	int Pop() {
		if (m_itemNum <= 0)
		{
			cout << "cannot GetTop item from heap. heap is emptied." << endl;
			return 0;
		}

		m_itemNum--;
		int poppedData = m_pDatum[0];
		m_pDatum[0] = m_pDatum[m_itemNum];
		ReorderByDemoting();
		return poppedData;
	}

	void RemoveAll()
	{
		m_itemNum = 0;
	}
};

class MinHeap : public Heap
{
	bool IsNotOrdered(int parentIndex, int childIndex)
	{
		if (m_pDatum[parentIndex] > m_pDatum[childIndex]) return true;
		else return false;
	}

	bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex)
	{
		if (m_pDatum[leftChildIndex] < m_pDatum[rightChildIndex]) return true;
		else return false;
	}

public :
	MinHeap() : Heap() {}
};


class MaxHeap : public Heap
{
	bool IsNotOrdered(int parentIndex, int childIndex)
	{
		if (m_pDatum[parentIndex] < m_pDatum[childIndex]) return true;
		else return false;
	}

	bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex)
	{
		if (m_pDatum[leftChildIndex] > m_pDatum[rightChildIndex]) return true;
		else return false;
	}

public :
	MaxHeap() : Heap() {}
};


#endif //HEAP_H