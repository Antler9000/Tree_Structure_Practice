#include"AVL_tree.h"
	void AVL_tree::RemoveTarget(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack)
	{
		if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild != NULL) //두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(pTarget, pRouteStack);
		}
		else if (pTarget->m_pLeftChild == NULL && pTarget->m_pRightChild != NULL) {
			ReplaceWithInorderSuccessor(pTarget, pRouteStack);
		}
		else if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild == NULL) {
			ReplaceWithInorderPredecessor(pTarget, pRouteStack);
		}
		else {
			delete pTarget;
			pTarget = NULL;
		}

		BalancingAllTargetToRoot(pRouteStack);
	}

	void AVL_tree::ReplaceWithInorderPredecessor(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack)
	{
		AVLNode* pPrevious = NULL;
		AVLNode* pTraverse = pTarget->m_pLeftChild;
		pRouteStack->Push(pTarget);
		while (pTraverse->m_pRightChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
			pRouteStack->Push(pPrevious);
		}

		if (pPrevious != NULL) pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
		else pTarget->m_pLeftChild = pTraverse->m_pLeftChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}

	void AVL_tree::ReplaceWithInorderSuccessor(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack)
	{
		AVLNode* pPrevious = NULL;
		AVLNode* pTraverse = pTarget->m_pRightChild;
		pRouteStack->Push(pTarget);
		while (pTraverse->m_pLeftChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
			pRouteStack->Push(pPrevious);
		}

		if (pPrevious != NULL) pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
		else pTarget->m_pRightChild = pTraverse->m_pRightChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}

	void AVL_tree::BalancingAllTargetToRoot(Stack<AVLNode*>* pRouteStack)
	{
		while (pRouteStack->IsEmpty() == false)
		{
			AVLNode* pRetraverse = pRouteStack->Pop();
			AVLNode* pParentOfRetraverse = pRouteStack->GetTop();
			UpdateHeight(pRetraverse);

			cout << "node's height : " << pRetraverse->m_heightFromLeaf << endl;

			BalancingTargetNode(pRetraverse, pParentOfRetraverse);
		}
	}

	void AVL_tree::BalancingTargetNode(AVLNode* pTarget, AVLNode* pParent)
	{
		int leftHeight = 0;
		int rightHeight = 0;
		if (pTarget->m_pLeftChild != NULL) leftHeight = 1 + pTarget->m_pLeftChild->m_heightFromLeaf;
		if (pTarget->m_pRightChild != NULL) rightHeight = 1 + pTarget->m_pRightChild->m_heightFromLeaf;

		if (leftHeight - rightHeight >= 2) {
			if (pTarget->m_pLeftChild->m_pRightChild == NULL)
			{
				LL_Rotation(pTarget, pParent);
			}
			else if (pTarget->m_pLeftChild->m_pLeftChild == NULL)
			{
				LR_Rotation(pTarget, pParent);
			}
			else
			{
				if (pTarget->m_pLeftChild->m_pLeftChild->m_heightFromLeaf > pTarget->m_pLeftChild->m_pRightChild->m_heightFromLeaf)
				{
					LL_Rotation(pTarget, pParent);
				}
				else
				{
					LR_Rotation(pTarget, pParent);
				}
			}
		}
		else if (rightHeight - leftHeight >= 2)
		{
			if (pTarget->m_pRightChild->m_pRightChild == NULL)
			{
				RL_Rotation(pTarget, pParent);
			}
			else if (pTarget->m_pRightChild->m_pLeftChild == NULL)
			{
				RR_Rotation(pTarget, pParent);
			}
			else
			{
				if (pTarget->m_pRightChild->m_pLeftChild->m_heightFromLeaf > pTarget->m_pRightChild->m_pRightChild->m_heightFromLeaf)
				{
					RL_Rotation(pTarget, pParent);
				}
				else
				{
					RR_Rotation(pTarget, pParent);
				}
			}
		}
	}

	void AVL_tree::LL_Rotation(AVLNode* pTarget, AVLNode* pParent)
	{
		cout << "LL 회전" << endl;

		if (pParent == NULL)
		{
			m_pHead = pTarget->m_pLeftChild;
			pTarget->m_pLeftChild = pTarget->m_pLeftChild->m_pRightChild;
			m_pHead->m_pRightChild = pTarget;
			m_pHead->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}
		else if (pParent->m_pLeftChild == pTarget)
		{
			pParent->m_pLeftChild = pTarget->m_pLeftChild;
			pTarget->m_pLeftChild = pTarget->m_pLeftChild->m_pRightChild;
			pParent->m_pLeftChild->m_pRightChild = pTarget;
			pParent->m_pLeftChild->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}
		else
		{
			pParent->m_pRightChild = pTarget->m_pLeftChild;
			pTarget->m_pLeftChild = pTarget->m_pLeftChild->m_pRightChild;
			pParent->m_pRightChild->m_pRightChild = pTarget;
			pParent->m_pRightChild->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}

		UpdateHeight(pTarget);
	}

	void AVL_tree::LR_Rotation(AVLNode* pTarget, AVLNode* pParent)
	{
		cout << "LR 회전" << endl;

		AVLNode* pLR_Location = pTarget->m_pLeftChild->m_pRightChild;
		pTarget->m_pLeftChild->m_pRightChild = pLR_Location->m_pLeftChild;
		pLR_Location->m_pLeftChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pLR_Location;

		UpdateHeight(pLR_Location->m_pLeftChild);
		UpdateHeight(pLR_Location);
		UpdateHeight(pTarget);

		LL_Rotation(pTarget, pParent);
	}

	void AVL_tree::RL_Rotation(AVLNode* pTarget, AVLNode* pParent)
	{
		cout << "RL 회전" << endl;

		AVLNode* pRL_Location = pTarget->m_pRightChild->m_pLeftChild;
		pTarget->m_pRightChild->m_pLeftChild = pRL_Location->m_pRightChild;
		pRL_Location->m_pRightChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pRL_Location;

		UpdateHeight(pRL_Location->m_pRightChild);
		UpdateHeight(pRL_Location);
		UpdateHeight(pTarget);

		RR_Rotation(pTarget, pParent);
	}

	void AVL_tree::RR_Rotation(AVLNode* pTarget, AVLNode* pParent)
	{
		cout << "RR 회전" << endl;

		if (pParent == NULL)
		{
			m_pHead = pTarget->m_pRightChild;
			pTarget->m_pRightChild = pTarget->m_pRightChild->m_pLeftChild;
			m_pHead->m_pLeftChild = pTarget;
			m_pHead->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}
		else if (pParent->m_pLeftChild == pTarget)
		{
			pParent->m_pLeftChild = pTarget->m_pRightChild;
			pTarget->m_pRightChild = pTarget->m_pRightChild->m_pLeftChild;
			pParent->m_pLeftChild->m_pLeftChild = pTarget;
			pParent->m_pLeftChild->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}
		else
		{
			pParent->m_pRightChild = pTarget->m_pRightChild;
			pTarget->m_pRightChild = pTarget->m_pRightChild->m_pLeftChild;
			pParent->m_pRightChild->m_pLeftChild = pTarget;
			pParent->m_pRightChild->m_heightFromLeaf = pTarget->m_heightFromLeaf - 1;
		}

		UpdateHeight(pTarget);
	}


	void AVL_tree::Insert(int newKey, int newData)
	{
		if (m_pHead == NULL)
		{
			m_pHead = new AVLNode(newKey, newData);
			return;
		}

		AVLNode* pTraverse = m_pHead;
		Stack<AVLNode*> pRouteStack;
		while (true)
		{
			if (newKey < pTraverse->m_key)
			{
				if (pTraverse->m_pLeftChild == NULL)
				{
					pTraverse->m_pLeftChild = new AVLNode(newKey, newData);
					pRouteStack.Push(pTraverse);
					BalancingAllTargetToRoot(&pRouteStack);
					return;
				}
				else
				{
					pRouteStack.Push(pTraverse);
					pTraverse = pTraverse->m_pLeftChild;
				}
			}
			else
			{
				if (pTraverse->m_pRightChild == NULL)
				{
					pTraverse->m_pRightChild = new AVLNode(newKey, newData);
					pRouteStack.Push(pTraverse);
					BalancingAllTargetToRoot(&pRouteStack);
					return;
				}
				else
				{
					pRouteStack.Push(pTraverse);
					pTraverse = pTraverse->m_pRightChild;
				}
			}
		}
	}

	void AVL_tree::Remove(int targetKey)
	{
		if (m_pHead == NULL)
		{
			cout << "Cannot Remove! tree is emptied" << endl;
			return;
		}

		Stack<AVLNode*> pRouteStack;

		if (m_pHead->m_key == targetKey)
		{
			RemoveTarget(m_pHead, &pRouteStack);
			return;
		}

		AVLNode* pTraverse = m_pHead;
		while (true)
		{
			if (targetKey < pTraverse->m_key)
			{
				pRouteStack.Push(pTraverse);
				if (pTraverse->m_pLeftChild->m_key == targetKey)
				{
					RemoveTarget(pTraverse->m_pLeftChild, &pRouteStack);
					return;
				}
				else pTraverse = pTraverse->m_pLeftChild;
			}
			else
			{
				pRouteStack.Push(pTraverse);
				if (pTraverse->m_pRightChild->m_key == targetKey)
				{
					RemoveTarget(pTraverse->m_pRightChild, &pRouteStack);
					return;
				}
				else pTraverse = pTraverse->m_pRightChild;
			}
		}
	}