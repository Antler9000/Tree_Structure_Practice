#include <iostream>
#include "BST_using_recurse.h"

using namespace std;

void BST::ReplaceWithInorderPredecessor(BST_Node* pRemoveTargetNode)
{
	BST_Node* pPreviousPtr = NULL;
	BST_Node* pTraversePtr = pRemoveTargetNode->m_pLeftChild;
	while (pTraversePtr->m_pRightChild != NULL)
	{
		pPreviousPtr = pTraversePtr;
		pTraversePtr = pTraversePtr->m_pRightChild;
	}
	if (pPreviousPtr != NULL) pPreviousPtr->m_pRightChild = pTraversePtr->m_pLeftChild;
	else pRemoveTargetNode->m_pLeftChild = pTraversePtr->m_pLeftChild;
	pRemoveTargetNode->m_key = pTraversePtr->m_key;
	pRemoveTargetNode->m_data = pTraversePtr->m_data;
	delete pTraversePtr;
	if (pPreviousPtr != NULL) pPreviousPtr->m_pRightChild = NULL;
}

void BST::ReplaceWithInorderSuccessor(BST_Node* pRemoveTargetNode)
{
	BST_Node* pPrevious = NULL;
	BST_Node* pTraverse = pRemoveTargetNode->m_pRightChild;
	while (pTraverse->m_pLeftChild != NULL)
	{
		pPrevious = pTraverse;
		pTraverse = pTraverse->m_pLeftChild;
	}
	if (pPrevious != NULL) pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
	else pRemoveTargetNode->m_pRightChild = pTraverse->m_pRightChild;
	pRemoveTargetNode->m_key = pTraverse->m_key;
	pRemoveTargetNode->m_data = pTraverse->m_data;
	delete pTraverse;
	if (pPrevious != NULL) pPrevious->m_pLeftChild = NULL;
}

void BST::RemoveTarget(BST_Node*& pRemoveTargetNode)
{
	if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{								//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild == NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{
		ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild == NULL)
	{
		ReplaceWithInorderPredecessor(pRemoveTargetNode);
	}
	else
	{
		delete pRemoveTargetNode;
		pRemoveTargetNode = NULL;
	}
}

void BST::InsertRecurse(BST_Node* pSearchTargetNode, int newKey, int newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if(pSearchTargetNode->m_pLeftChild == NULL) pSearchTargetNode->m_pLeftChild = new BST_Node(newKey, newData);
		else InsertRecurse(pSearchTargetNode->m_pLeftChild, newKey, newData);
	}
	else if(pSearchTargetNode->m_key < newKey)
	{
		if (pSearchTargetNode->m_pRightChild == NULL) pSearchTargetNode->m_pRightChild = new BST_Node(newKey, newData);
		else InsertRecurse(pSearchTargetNode->m_pRightChild, newKey, newData);
	}
	else
	{
		cout << "cannot insert! key is same! If it is dummy_room_node, then it is okay" << endl;
	}
}

int BST::RetrieveRecurse(BST_Node* pSearchTargetNode, int retrieveTargetKey)
{
	if (retrieveTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild != NULL) return RetrieveRecurse(pSearchTargetNode->m_pLeftChild, retrieveTargetKey);
		else  cout << "there is no such key in searching." << endl;
	}
	else if (retrieveTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild != NULL) return RetrieveRecurse(pSearchTargetNode->m_pRightChild, retrieveTargetKey);
		else  cout << "there is no such key in searching." << endl;
	}
	else
	{
		return pSearchTargetNode->m_data;
	}
}

void BST::RemoveRecurse(BST_Node* pSearchTargetNode, int removeTargetKey)
{
	if (removeTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild->m_key == removeTargetKey)
		{
			RemoveTarget(pSearchTargetNode->m_pLeftChild);
		}
		else
		{
			RemoveRecurse(pSearchTargetNode->m_pLeftChild, removeTargetKey);
		}
	}
	else if (removeTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild->m_key == removeTargetKey)
		{
			RemoveTarget(pSearchTargetNode->m_pRightChild);
		}
		else
		{
			RemoveRecurse(pSearchTargetNode->m_pRightChild, removeTargetKey);
		}
	}
	else
	{
		cout << "should not reach here while RemoveRecurse()" << endl;
	}
}


