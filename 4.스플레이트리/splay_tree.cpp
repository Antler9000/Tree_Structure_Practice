#include"splay_tree.h"

int SplayTree::Retrieve(int targetKey) {
	SplayNode* traversePtr = m_head;
	SplayNode* fatherOfTraversePtr = NULL;
	SplayNode* grandfatherOfTraversePtr = NULL;
	SplayNode* greatgrandfatherOfTraversePtr = NULL;
	while (traversePtr != NULL) {
		if (targetKey < traversePtr->m_key) {
			greatgrandfatherOfTraversePtr = grandfatherOfTraversePtr;
			grandfatherOfTraversePtr = fatherOfTraversePtr;
			fatherOfTraversePtr = traversePtr;
			traversePtr = traversePtr->m_lChild;
		}
		else if (traversePtr->m_key < targetKey) {
			greatgrandfatherOfTraversePtr = grandfatherOfTraversePtr;
			grandfatherOfTraversePtr = fatherOfTraversePtr;
			fatherOfTraversePtr = traversePtr;
			traversePtr = traversePtr->m_rChild;
		}
		else {
			SplayTarget(greatgrandfatherOfTraversePtr, grandfatherOfTraversePtr, fatherOfTraversePtr, traversePtr);
			return traversePtr->m_data;
		}
	}
}

void SplayTree::SplayTarget(SplayNode* greatgrandfatherOfTraversePtr, SplayNode* grandfatherOfTarget, SplayNode* fatherOfTarget, SplayNode* target) {
	if (greatgrandfatherOfTraversePtr != NULL) {
		if (greatgrandfatherOfTraversePtr->m_lChild == grandfatherOfTarget) {
			if (grandfatherOfTarget->m_lChild == fatherOfTarget) {
				if (fatherOfTarget->m_lChild == target) LLZigZig(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
				else	 LRZigZag(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
			}
			else {
				if (fatherOfTarget->m_lChild == target) RLZigZag(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
				else RRZigZig(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
			}
		}
		else {
			if (grandfatherOfTarget->m_lChild == fatherOfTarget) {
				if (fatherOfTarget->m_lChild == target) LLZigZig(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
				else	 LRZigZag(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
			}
			else {
				if (fatherOfTarget->m_lChild == target) RLZigZag(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
				else RRZigZig(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
			}
		}
	}
	else if (grandfatherOfTarget != NULL) {
		if (grandfatherOfTarget->m_lChild == fatherOfTarget) {
			if (fatherOfTarget->m_lChild == target) LLZigZig(m_head, fatherOfTarget, target);
			else	 LRZigZag(m_head, fatherOfTarget, target);
		}
		else {
			if (fatherOfTarget->m_lChild == target) RLZigZag(m_head, fatherOfTarget, target);
			else RRZigZig(m_head, fatherOfTarget, target);
		}
	}
	else if (fatherOfTarget != NULL) {
		if (fatherOfTarget->m_lChild == target) LZig(m_head, target);
		else RZig(m_head, target);
	}
	else {
		//We cannot splay the head. So, let's do nothing.
	}
}