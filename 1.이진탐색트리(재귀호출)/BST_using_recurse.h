#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>	//에러 출력 함수와 순회 출력 함수에서 cin, cout을 사용함
#include <string>		//에러 출력 함수의 매개변수 타입으로 string 타입을 사용함

using namespace std;

#define ErrorPrint(statement) cout << "(Error : " << __func__ << ") " << statement << endl;
#define WarningPrint(statement) cout << "(Warning : " << __func__ << ") " << statement << endl;

template <typename DataType>
class BST
{
private:
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

public:
	BST()
	{
		m_pHead = NULL;
	}

	~BST()
	{
		RemoveTree();
	}

	bool Insert(int newKey, DataType newData)
	{
		if (m_pHead == NULL)
		{
			m_pHead = new BST_Node<DataType>(newKey, newData);

			return true;
		}
		else
		{
			return InsertRecurse(m_pHead, newKey, newData);
		}
	}

	bool Retrieve(int retrieveTargetKey, DataType& outData)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot retrieve. becuase tree is empty.");

			return false;
		}

		return RetrieveRecurse(m_pHead, retrieveTargetKey, outData);
	}

	bool Remove(int removeTargetKey)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot remove. becuase tree is empty.");

			return false;
		}
		
		if (m_pHead->m_key == removeTargetKey)
		{
			return RemoveTarget(m_pHead);
		}
		else
		{
			return RemoveRecurse(m_pHead, removeTargetKey);
		}
	}

	//트리의 값전달로 인한 복사가 일어나지 않도록 하기 위해서 레퍼런스 인자를 사용함
	bool CopyTree(BST<DataType>& pSourceBST)
	{		
		if (&pSourceBST == NULL)
		{
			WarningPrint("cannot copying. becuase source tree is null.");
			return false;
		}
		
		if (pSourceBST.m_pHead == NULL)
		{
			WarningPrint("cannot coping. becuase source tree is empty.");
			return false;
		}

		return CopyTreeRecurse(pSourceBST.m_pHead);
	}

	void RemoveTree()
	{
		if (m_pHead != NULL)
		{
			delete m_pHead;
			m_pHead = NULL;
		}
	}

	void PreorderPrint()
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");
			return;
		}

		cout << "preorder traverse..." << endl;
		PreorderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

	void InorderPrint()
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");
			return;
		}

		cout << "inorder traverse..." << endl;
		InorderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

	void PostOrderPrint()
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");
			return;
		}

		cout << "postorder traverse..." << endl;
		PostOrderPrintRecurse(m_pHead);
		cout << "traverse ended" << endl;
	}

private:
	BST_Node<DataType>* m_pHead;

	bool InsertRecurse(BST_Node<DataType>* pSearchTargetNode, int newKey, DataType newData);

	bool RetrieveRecurse(BST_Node<DataType>* pSearchTargetNode, int retrieiveTargetKey, DataType& outData);

	bool RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, int removeTargetKey);

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꾸기 위해서 레퍼런스 인자를 사용함
	bool RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode);

	bool ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode);

	bool ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode);

	bool CopyTreeRecurse(BST_Node<DataType>* pSourceNode);

	void PreorderPrintRecurse(BST_Node<DataType>* pTargetNode);

	void InorderPrintRecurse(BST_Node<DataType>* pTargetNode);

	void PostOrderPrintRecurse(BST_Node<DataType>* pTargetNode);
};

template <typename DataType>
bool BST<DataType>::InsertRecurse(BST_Node<DataType>* pSearchTargetNode, int newKey, DataType newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL)
		{
			pSearchTargetNode->m_pLeftChild = new BST_Node<DataType>(newKey, newData);
			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pLeftChild, newKey, newData);
		}
	}
	else if (pSearchTargetNode->m_key < newKey)
	{
		if (pSearchTargetNode->m_pRightChild == NULL)
		{
			pSearchTargetNode->m_pRightChild = new BST_Node<DataType>(newKey, newData);
			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pRightChild, newKey, newData);
		}
	}
	else
	{
		ErrorPrint("cannot insert because there is same key in tree already!");

		return false;
	}
}

template <typename DataType>
bool BST<DataType>::RetrieveRecurse(BST_Node<DataType>* pSearchTargetNode, int retrieveTargetKey, DataType& outData)
{
	if (retrieveTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild != NULL)
		{
			return RetrieveRecurse(pSearchTargetNode->m_pLeftChild, retrieveTargetKey, outData);
		}
		else
		{
			ErrorPrint("there is no such key in searching.");
			return false;
		}
	}
	else if (retrieveTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild != NULL)
		{
			return RetrieveRecurse(pSearchTargetNode->m_pRightChild, retrieveTargetKey, outData);
		}
		else
		{
			ErrorPrint("there is no such key in searching.");
			return false;
		}
	}
	else
	{
		outData = pSearchTargetNode->m_data;
		return true;
	}
}

template <typename DataType>
bool BST<DataType>::RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, int removeTargetKey)
{
	if (removeTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild->m_key == removeTargetKey)
		{
			return RemoveTarget(pSearchTargetNode->m_pLeftChild);
		}
		else
		{
			return RemoveRecurse(pSearchTargetNode->m_pLeftChild, removeTargetKey);
		}
	}
	else if (removeTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild->m_key == removeTargetKey)
		{
			return RemoveTarget(pSearchTargetNode->m_pRightChild);
		}
		else
		{
			return RemoveRecurse(pSearchTargetNode->m_pRightChild, removeTargetKey);
		}
	}
	else
	{
		ErrorPrint("should not reach here");

		return false;
	}
}
template <typename DataType>
bool BST<DataType>::RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode)
{
	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
	if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{
		return ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild == NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{
		return ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild == NULL)
	{
		return ReplaceWithInorderPredecessor(pRemoveTargetNode);
	}
	else
	{
		delete pRemoveTargetNode;
		pRemoveTargetNode = NULL;

		return true;
	}
}

template <typename DataType>
bool BST<DataType>::ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode)
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

	return true;
}

template <typename DataType>
bool BST<DataType>::ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode)
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

	return true;
}

template <typename DataType>
bool BST<DataType>::CopyTreeRecurse(BST_Node<DataType>* pSourceNode)
{
	bool result = Insert(pSourceNode->m_key, pSourceNode->m_data);
	if (pSourceNode->m_pLeftChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pLeftChild);
	if (pSourceNode->m_pRightChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pRightChild);

	return result;
}

template <typename DataType>
void BST<DataType>::PreorderPrintRecurse(BST_Node<DataType>* pTargetNode)
{
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pLeftChild != NULL) PreorderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PreorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::InorderPrintRecurse(BST_Node<DataType>* pTargetNode)
{
	if (pTargetNode->m_pLeftChild != NULL) InorderPrintRecurse(pTargetNode->m_pLeftChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pRightChild != NULL) InorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::PostOrderPrintRecurse(BST_Node<DataType>* pTargetNode)
{
	if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
}

#endif //BST_USING_RECURSE_H