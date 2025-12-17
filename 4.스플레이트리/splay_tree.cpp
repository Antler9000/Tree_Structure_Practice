#include"splay_tree.h"

int SplayTree::Retrieve(int targetKey)
{
	SplayNode* traversePtr = m_head;
	SplayNode* fatherOfTraversePtr = NULL;
	SplayNode* grandfatherOfTraversePtr = NULL;
	SplayNode* greatgrandfatherOfTraversePtr = NULL;
	while (traversePtr != NULL)
	{
		if (targetKey < traversePtr->m_key)
		{
			greatgrandfatherOfTraversePtr = grandfatherOfTraversePtr;
			grandfatherOfTraversePtr = fatherOfTraversePtr;
			fatherOfTraversePtr = traversePtr;
			traversePtr = traversePtr->m_lChild;
		}
		else if (traversePtr->m_key < targetKey)
		{
			greatgrandfatherOfTraversePtr = grandfatherOfTraversePtr;
			grandfatherOfTraversePtr = fatherOfTraversePtr;
			fatherOfTraversePtr = traversePtr;
			traversePtr = traversePtr->m_rChild;
		}
		else
		{
			SplayTarget(greatgrandfatherOfTraversePtr, grandfatherOfTraversePtr, fatherOfTraversePtr, traversePtr);

			return traversePtr->m_data;
		}
	}
}

void SplayTree::SplayTarget(SplayNode* greatgrandfatherOfTraversePtr, SplayNode* grandfatherOfTarget, SplayNode* fatherOfTarget, SplayNode* target)
{
	if (greatgrandfatherOfTraversePtr != NULL)
	{
		if (greatgrandfatherOfTraversePtr->m_lChild == grandfatherOfTarget)
		{
			if (grandfatherOfTarget->m_lChild == fatherOfTarget)
			{
				if (fatherOfTarget->m_lChild == target) LL_ZigZig(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
				else	 LR_ZigZag(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
			}
			else
			{
				if (fatherOfTarget->m_lChild == target) RL_ZigZag(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
				else RR_ZigZig(greatgrandfatherOfTraversePtr->m_lChild, fatherOfTarget, target);
			}
		}
		else
		{
			if (grandfatherOfTarget->m_lChild == fatherOfTarget)
			{
				if (fatherOfTarget->m_lChild == target) LL_ZigZig(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
				else	 LR_ZigZag(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
			}
			else
			{
				if (fatherOfTarget->m_lChild == target) RL_ZigZag(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
				else RR_ZigZig(greatgrandfatherOfTraversePtr->m_rChild, fatherOfTarget, target);
			}
		}
	}
	else if (grandfatherOfTarget != NULL)
	{
		if (grandfatherOfTarget->m_lChild == fatherOfTarget)
		{
			if (fatherOfTarget->m_lChild == target) LL_ZigZig(m_head, fatherOfTarget, target);
			else	 LR_ZigZag(m_head, fatherOfTarget, target);
		}
		else
		{
			if (fatherOfTarget->m_lChild == target) RL_ZigZag(m_head, fatherOfTarget, target);
			else RR_ZigZig(m_head, fatherOfTarget, target);
		}
	}
	else if (fatherOfTarget != NULL)
	{
		if (fatherOfTarget->m_lChild == target) L_Zig(m_head, target);
		else R_Zig(m_head, target);
	}
	else
	{
		//head를 스플레이 할 수는 없으므로, 아무것도 하지 말자
	}
}