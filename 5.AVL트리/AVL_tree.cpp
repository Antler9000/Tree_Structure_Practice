#include"AVL_tree.h"
	void AVL_tree::RemoveTarget(AVLNode*& targetPtr, Stack<AVLNode*>* ancesterNodeStack)
	{
		if (targetPtr->m_lChild != NULL && targetPtr->m_rChild != NULL) //두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(targetPtr, ancesterNodeStack);
		}
		else if (targetPtr->m_lChild == NULL && targetPtr->m_rChild != NULL) {
			ReplaceWithInorderSuccessor(targetPtr, ancesterNodeStack);
		}
		else if (targetPtr->m_lChild != NULL && targetPtr->m_rChild == NULL) {
			ReplaceWithInorderPredecessor(targetPtr, ancesterNodeStack);
		}
		else {
			delete targetPtr;
			targetPtr = NULL;
		}

		BalancingAllTargetToRoot(ancesterNodeStack);
	}

	void AVL_tree::ReplaceWithInorderPredecessor(AVLNode * &targetPtr, Stack<AVLNode*>*ancesterNodeStack)
	{
		AVLNode* previousPtr = NULL;
		AVLNode* traversePtr = targetPtr->m_lChild;
		ancesterNodeStack->Push(targetPtr);
		while (traversePtr->m_rChild != NULL)
		{
			previousPtr = traversePtr;
			traversePtr = traversePtr->m_rChild;
			ancesterNodeStack->Push(previousPtr);
		}

		if (previousPtr != NULL) previousPtr->m_rChild = traversePtr->m_lChild;
		else targetPtr->m_lChild = traversePtr->m_lChild;

		targetPtr->m_key = traversePtr->m_key;
		targetPtr->m_data = traversePtr->m_data;
		delete traversePtr;
	}

	void AVL_tree::ReplaceWithInorderSuccessor(AVLNode * &targetPtr, Stack<AVLNode*>*ancesterNodeStack)
	{
		AVLNode* previousPtr = NULL;
		AVLNode* traversePtr = targetPtr->m_rChild;
		ancesterNodeStack->Push(targetPtr);
		while (traversePtr->m_lChild != NULL)
		{
			previousPtr = traversePtr;
			traversePtr = traversePtr->m_lChild;
			ancesterNodeStack->Push(previousPtr);
		}

		if (previousPtr != NULL) previousPtr->m_lChild = traversePtr->m_rChild;
		else targetPtr->m_rChild = traversePtr->m_rChild;

		targetPtr->m_key = traversePtr->m_key;
		targetPtr->m_data = traversePtr->m_data;
		delete traversePtr;
	}

	void AVL_tree::BalancingAllTargetToRoot(Stack<AVLNode*>*ancesterNodeStack)
	{
		while (ancesterNodeStack->IsEmpty() == false)
		{
			AVLNode* retraverseNode = ancesterNodeStack->Pop();
			AVLNode* parentOfRetraverseNode = ancesterNodeStack->GetTop();
			UpdateHeight(retraverseNode);

			cout << "node's height : " << retraverseNode->m_heightFromLeaf << endl;

			BalancingTargetNode(retraverseNode, parentOfRetraverseNode);
		}
	}

	void AVL_tree::BalancingTargetNode(AVLNode * targetNode, AVLNode * parentNode)
	{
		int leftHeight = 0;
		int rightHeight = 0;
		if (targetNode->m_lChild != NULL) leftHeight = 1 + targetNode->m_lChild->m_heightFromLeaf;
		if (targetNode->m_rChild != NULL) rightHeight = 1 + targetNode->m_rChild->m_heightFromLeaf;

		if (leftHeight - rightHeight >= 2) {
			if (targetNode->m_lChild->m_rChild == NULL)
			{
				LL_Rotation(targetNode, parentNode);
			}
			else if (targetNode->m_lChild->m_lChild == NULL)
			{
				LR_Rotation(targetNode, parentNode);
			}
			else
			{
				if (targetNode->m_lChild->m_lChild->m_heightFromLeaf > targetNode->m_lChild->m_rChild->m_heightFromLeaf)
				{
					LL_Rotation(targetNode, parentNode);
				}
				else
				{
					LR_Rotation(targetNode, parentNode);
				}
			}
		}
		else if (rightHeight - leftHeight >= 2)
		{
			if (targetNode->m_rChild->m_rChild == NULL)
			{
				RL_Rotation(targetNode, parentNode);
			}
			else if (targetNode->m_rChild->m_lChild == NULL)
			{
				RR_Rotation(targetNode, parentNode);
			}
			else
			{
				if (targetNode->m_rChild->m_lChild->m_heightFromLeaf > targetNode->m_rChild->m_rChild->m_heightFromLeaf)
				{
					RL_Rotation(targetNode, parentNode);
				}
				else
				{
					RR_Rotation(targetNode, parentNode);
				}
			}
		}
	}

	void AVL_tree::LL_Rotation(AVLNode * targetNode, AVLNode * parentNode)
	{
		cout << "LL 회전" << endl;

		if (parentNode == NULL)
		{
			m_head = targetNode->m_lChild;
			targetNode->m_lChild = targetNode->m_lChild->m_rChild;
			m_head->m_rChild = targetNode;
			m_head->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}
		else if (parentNode->m_lChild == targetNode)
		{
			parentNode->m_lChild = targetNode->m_lChild;
			targetNode->m_lChild = targetNode->m_lChild->m_rChild;
			parentNode->m_lChild->m_rChild = targetNode;
			parentNode->m_lChild->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}
		else
		{
			parentNode->m_rChild = targetNode->m_lChild;
			targetNode->m_lChild = targetNode->m_lChild->m_rChild;
			parentNode->m_rChild->m_rChild = targetNode;
			parentNode->m_rChild->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}

		UpdateHeight(targetNode);
	}

	void AVL_tree::LR_Rotation(AVLNode * targetNode, AVLNode * parentNode)
	{
		cout << "LR 회전" << endl;

		AVLNode* LRLocation = targetNode->m_lChild->m_rChild;
		targetNode->m_lChild->m_rChild = LRLocation->m_lChild;
		LRLocation->m_lChild = targetNode->m_lChild;
		targetNode->m_lChild = LRLocation;

		UpdateHeight(LRLocation->m_lChild);
		UpdateHeight(LRLocation);
		UpdateHeight(targetNode);

		LL_Rotation(targetNode, parentNode);
	}

	void AVL_tree::RL_Rotation(AVLNode * targetNode, AVLNode * parentNode)
	{
		cout << "RL 회전" << endl;

		AVLNode* RLLocation = targetNode->m_rChild->m_lChild;
		targetNode->m_rChild->m_lChild = RLLocation->m_rChild;
		RLLocation->m_rChild = targetNode->m_rChild;
		targetNode->m_rChild = RLLocation;

		UpdateHeight(RLLocation->m_rChild);
		UpdateHeight(RLLocation);
		UpdateHeight(targetNode);

		RR_Rotation(targetNode, parentNode);
	}

	void AVL_tree::RR_Rotation(AVLNode * targetNode, AVLNode * parentNode)
	{
		cout << "RR 회전" << endl;

		if (parentNode == NULL)
		{
			m_head = targetNode->m_rChild;
			targetNode->m_rChild = targetNode->m_rChild->m_lChild;
			m_head->m_lChild = targetNode;
			m_head->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}
		else if (parentNode->m_lChild == targetNode)
		{
			parentNode->m_lChild = targetNode->m_rChild;
			targetNode->m_rChild = targetNode->m_rChild->m_lChild;
			parentNode->m_lChild->m_lChild = targetNode;
			parentNode->m_lChild->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}
		else
		{
			parentNode->m_rChild = targetNode->m_rChild;
			targetNode->m_rChild = targetNode->m_rChild->m_lChild;
			parentNode->m_rChild->m_lChild = targetNode;
			parentNode->m_rChild->m_heightFromLeaf = targetNode->m_heightFromLeaf - 1;
		}

		UpdateHeight(targetNode);
	}


	void AVL_tree::Insert(int newKey, int newData)
	{
		if (m_head == NULL)
		{
			m_head = new AVLNode(newKey, newData);
			return;
		}

		AVLNode* traversePtr = m_head;
		Stack<AVLNode*> ancesterNodeStack;
		while (true)
		{
			if (newKey < traversePtr->m_key)
			{
				if (traversePtr->m_lChild == NULL)
				{
					traversePtr->m_lChild = new AVLNode(newKey, newData);
					ancesterNodeStack.Push(traversePtr);
					BalancingAllTargetToRoot(&ancesterNodeStack);
					return;
				}
				else
				{
					ancesterNodeStack.Push(traversePtr);
					traversePtr = traversePtr->m_lChild;
				}
			}
			else
			{
				if (traversePtr->m_rChild == NULL)
				{
					traversePtr->m_rChild = new AVLNode(newKey, newData);
					ancesterNodeStack.Push(traversePtr);
					BalancingAllTargetToRoot(&ancesterNodeStack);
					return;
				}
				else
				{
					ancesterNodeStack.Push(traversePtr);
					traversePtr = traversePtr->m_rChild;
				}
			}
		}
	}

	void AVL_tree::Remove(int targetKey)
	{
		if (m_head == NULL)
		{
			cout << "Cannot Remove! tree is emptied" << endl;
			return;
		}

		Stack<AVLNode*> ancesterNodeStack;

		if (m_head->m_key == targetKey)
		{
			RemoveTarget(m_head, &ancesterNodeStack);
			return;
		}

		AVLNode* traversePtr = m_head;
		while (true)
		{
			if (targetKey < traversePtr->m_key)
			{
				ancesterNodeStack.Push(traversePtr);
				if (traversePtr->m_lChild->m_key == targetKey)
				{
					RemoveTarget(traversePtr->m_lChild, &ancesterNodeStack);
					return;
				}
				else traversePtr = traversePtr->m_lChild;
			}
			else
			{
				ancesterNodeStack.Push(traversePtr);
				if (traversePtr->m_rChild->m_key == targetKey)
				{
					RemoveTarget(traversePtr->m_rChild, &ancesterNodeStack);
					return;
				}
				else traversePtr = traversePtr->m_rChild;
			}
		}
	}