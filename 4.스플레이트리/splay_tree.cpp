#include"splay_tree.h"

int SplayTree::Retrieve(int targetKey)
{
	SplayNode* pTraversePtr = m_pHead;
	SplayNode* pFatherOfTraversePtr = NULL;
	SplayNode* pGrandFatherOfTraversePtr = NULL;
	SplayNode* pGreatGrandFatherOfTraversePtr = NULL;
	while (pTraversePtr != NULL)
	{
		if (targetKey < pTraversePtr->m_key)
		{
			pGreatGrandFatherOfTraversePtr = pGrandFatherOfTraversePtr;
			pGrandFatherOfTraversePtr = pFatherOfTraversePtr;
			pFatherOfTraversePtr = pTraversePtr;
			pTraversePtr = pTraversePtr->m_pLeftChild;
		}
		else if (pTraversePtr->m_key < targetKey)
		{
			pGreatGrandFatherOfTraversePtr = pGrandFatherOfTraversePtr;
			pGrandFatherOfTraversePtr = pFatherOfTraversePtr;
			pFatherOfTraversePtr = pTraversePtr;
			pTraversePtr = pTraversePtr->m_pRightChild;
		}
		else
		{
			SplayTarget(pGreatGrandFatherOfTraversePtr, pGrandFatherOfTraversePtr, pFatherOfTraversePtr, pTraversePtr);

			return pTraversePtr->m_data;
		}
	}
}

void SplayTree::SplayTarget(SplayNode* pGreatGrandFatherOfTarget, SplayNode* pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget)
{
	if (pGreatGrandFatherOfTarget != NULL)
	{
		if (pGreatGrandFatherOfTarget->m_pLeftChild == pGrandFatherOfTarget)
		{
			if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
				else	 LR_ZigZag(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
			}
			else
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
				else RR_ZigZig(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
			}
		}
		else
		{
			if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
				else	 LR_ZigZag(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
			}
			else
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
				else RR_ZigZig(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
			}
		}
	}
	else if (pGrandFatherOfTarget != NULL)
	{
		if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
		{
			if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(m_pHead, pFatherOfTarget, pTarget);
			else	 LR_ZigZag(m_pHead, pFatherOfTarget, pTarget);
		}
		else
		{
			if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(m_pHead, pFatherOfTarget, pTarget);
			else RR_ZigZig(m_pHead, pFatherOfTarget, pTarget);
		}
	}
	else if (pFatherOfTarget != NULL)
	{
		if (pFatherOfTarget->m_pLeftChild == pTarget) L_Zig(m_pHead, pTarget);
		else R_Zig(m_pHead, pTarget);
	}
	else
	{
		//head를 스플레이 할 수는 없으므로, 아무것도 하지 말자
	}
}