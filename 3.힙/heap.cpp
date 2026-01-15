#include "heap.h"

void Heap::ReorderByPromoting() {
	int targetIndex = m_itemNum - 1;
	int parentIndex = getParentIndex(targetIndex);

	while ((targetIndex > 0) && IsNotOrdered(parentIndex, targetIndex)) {
		Swap(m_pDatum[targetIndex], m_pDatum[parentIndex]);
		targetIndex = parentIndex;
		parentIndex = getParentIndex(targetIndex);
	}
}

void Heap::ReorderByDemoting() {
	int targetIndex = 0;
	int leftChildIndex = getLeftChildIndex(targetIndex);
	int rightChildIndex = getRightChildIndex(targetIndex);
	int targetChildIndex;

	while (leftChildIndex <= m_itemNum) {
		if (rightChildIndex <= m_itemNum) {
			if (IsLeftChildTarget(leftChildIndex, rightChildIndex)) targetChildIndex = leftChildIndex;
			else targetChildIndex = rightChildIndex;
		}
		else {
			targetChildIndex = leftChildIndex;
		}

		if (IsNotOrdered(targetIndex, targetChildIndex)) {
			Swap(m_pDatum[targetIndex], m_pDatum[targetChildIndex]);
			targetIndex = targetChildIndex;
			leftChildIndex = getLeftChildIndex(targetIndex);
			rightChildIndex = getRightChildIndex(targetIndex);
		}
		else {
			break;
		}
	}
}