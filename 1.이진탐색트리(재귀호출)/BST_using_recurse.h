#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;

template <typename DataType>
class BST;

template <typename DataType>
class BST_Node
{
private:
	friend class BST<DataType>;

	int	m_key;
	DataType	m_data;
	BST_Node<DataType>* m_pLeftChild;
	BST_Node<DataType>* m_pRightChild;

	BST_Node(int newKey, DataType newData)
	{
		m_key = newKey;
		m_data = newData;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}

	~BST_Node()
	{
		delete m_pLeftChild;
		delete m_pRightChild;
	}
};

template <typename DataType>
class BST
{
private:
	BST_Node<DataType>* m_pHead;

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꿔야하므로, 레퍼런스 인자로 받음
	void RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode);

	void ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode);

	void ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode);

public:
	BST()
	{
		m_pHead = NULL;
	}

	~BST()
	{
		RemoveAll();
	}

	//삽입
	void Insert(int newKey, DataType newData)
	{
		cout << "inserting BST_Node.... (key : " << newKey << ", data : " << newData << " )" << endl;
		if (m_pHead == NULL)
		{
			m_pHead = new BST_Node<DataType>(newKey, newData);
		}
		else
		{
			InsertRecurse(m_pHead, newKey, newData);
		}
		cout << "insert ended" << endl;
	}

	void InsertRecurse(BST_Node<DataType>* pSearchTargetNode, int newKey, DataType newData);

	//검색
	int Retrieve(int retrieveTargetKey)
	{
		if (m_pHead == NULL)
		{
			cout << "cannot retrieve. becuase tree is null." << endl;
			return -1;
		}

		cout << "retrieving BST_Node.... (key : " << retrieveTargetKey << " )" << endl;
		DataType retrieveValue = RetrieveRecurse(m_pHead, retrieveTargetKey);
		cout << "retrieving ended" << endl;
		return retrieveValue;
	}

	DataType RetrieveRecurse(BST_Node<DataType>* pSearchTargetNode, int retrieiveTargetKey);

	//삭제
	void Remove(int removeTargetKey)
	{
		if (m_pHead == NULL)
		{
			cout << "cannot remove. becuase tree is null." << endl;
			return;
		}
		
		if (m_pHead->m_key == removeTargetKey)
		{
			RemoveTarget(m_pHead);
		}
		else
		{
			cout << "removing BST_Node.... (key : " << removeTargetKey << " )" << endl;
			RemoveRecurse(m_pHead, removeTargetKey);
			cout << "removing ended" << endl;
		}
	}

	void RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, int removeTargetKey);

	//트리 복사
	void CopyFrom(BST<DataType>* pSourceBST)
	{		
		if (pSourceBST == NULL)
		{
			cout << "cannot copying. becuase tree is null." << endl;
			return;
		}
		
		if (pSourceBST->m_pHead == NULL)
		{
			cout << "cannot coping. becuase m_pHead is null." << endl;
			return;
		}

		cout << "copying tree..." << endl;
		CopyFromRecurse(pSourceBST->m_pHead);
		cout << "copying dended" << endl;
	}

	void CopyFromRecurse(BST_Node<DataType>* pSourceNode)
	{
		Insert(pSourceNode->m_key, pSourceNode->m_data);
		if (pSourceNode->m_pLeftChild != NULL) CopyFromRecurse(pSourceNode->m_pLeftChild);
		if (pSourceNode->m_pRightChild != NULL) CopyFromRecurse(pSourceNode->m_pRightChild);
	}

	//트리 삭제
	void RemoveAll()
	{
		delete m_pHead;
		m_pHead = NULL;
	}

	//전위 순회
	void PreorderPrint()
	{
		if (m_pHead == NULL)
		{
			cout << "cannot traverse print. becuase m_pHead is null." << endl;
			return;
		}

		cout << "preorder traverse..." << endl;
		PreorderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

	void PreorderPrintRecurse(BST_Node<DataType>* pTargetNode)
	{
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
		if (pTargetNode->m_pLeftChild != NULL) PreorderPrintRecurse(pTargetNode->m_pLeftChild);
		if (pTargetNode->m_pRightChild != NULL) PreorderPrintRecurse(pTargetNode->m_pRightChild);
	}

	//중위 순회
	void InorderPrint()
	{
		if (m_pHead == NULL)
		{
			cout << "cannot traverse print. becuase m_pHead is null." << endl;
			return;
		}

		cout << "inorder traverse..." << endl;
		InorderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

	void InorderPrintRecurse(BST_Node<DataType>* pTargetNode)
	{
		if (pTargetNode->m_pLeftChild != NULL) InorderPrintRecurse(pTargetNode->m_pLeftChild);
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
		if (pTargetNode->m_pRightChild != NULL) InorderPrintRecurse(pTargetNode->m_pRightChild);
	}

	//후위 순회
	void PostOrderPrint()
	{
		if (m_pHead == NULL)
		{
			cout << "cannot traverse print. becuase m_pHead is null." << endl;
			return;
		}

		cout << "postorder traverse..." << endl;
		PostOrderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

	void PostOrderPrintRecurse(BST_Node<DataType>* pTargetNode)
	{
		if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
		if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	}

};

template <typename DataType>
void BST<DataType>::ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode)
{
	BST_Node<DataType>* pPreviousPtr = NULL;
	BST_Node<DataType>* pTraversePtr = pRemoveTargetNode->m_pLeftChild;
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

template <typename DataType>
void BST<DataType>::ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode)
{
	BST_Node<DataType>* pPrevious = NULL;
	BST_Node<DataType>* pTraverse = pRemoveTargetNode->m_pRightChild;
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

template <typename DataType>
void BST<DataType>::RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode)
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

template <typename DataType>
void BST<DataType>::InsertRecurse(BST_Node<DataType>* pSearchTargetNode, int newKey, DataType newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL) pSearchTargetNode->m_pLeftChild = new BST_Node<DataType>(newKey, newData);
		else InsertRecurse(pSearchTargetNode->m_pLeftChild, newKey, newData);
	}
	else if (pSearchTargetNode->m_key < newKey)
	{
		if (pSearchTargetNode->m_pRightChild == NULL) pSearchTargetNode->m_pRightChild = new BST_Node<DataType>(newKey, newData);
		else InsertRecurse(pSearchTargetNode->m_pRightChild, newKey, newData);
	}
	else
	{
		cout << "cannot insert! key is same! If it is dummy_room_node, then it is okay" << endl;
	}
}

template <typename DataType>
DataType BST<DataType>::RetrieveRecurse(BST_Node<DataType>* pSearchTargetNode, int retrieveTargetKey)
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

template <typename DataType>
void BST<DataType>::RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, int removeTargetKey)
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

#endif //BST_USING_RECURSE_H