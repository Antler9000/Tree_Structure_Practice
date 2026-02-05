#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;

class BST;

class BST_Node
{
private:
	friend BST;

	int	m_data;
	int	m_key;
	BST_Node* m_pLeftChild;
	BST_Node* m_pRightChild;

	BST_Node(int newKey, int newData)
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

class BST
{
private:
	BST_Node* m_pHead;

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꿔야하므로, 레퍼런스 인자로 받음
	void RemoveTarget(BST_Node*& pRemoveTargetNode);

	void ReplaceWithInorderPredecessor(BST_Node* pRemoveTargetNode);

	void ReplaceWithInorderSuccessor(BST_Node* pRemoveTargetNode);

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
	void Insert(int newKey, int newData)
	{
		cout << "inserting BST_Node.... (key : " << newKey << ", data : " << newData << " )" << endl;
		if (m_pHead == NULL)
		{
			m_pHead = new BST_Node(newKey, newData);
		}
		else
		{
			InsertRecurse(m_pHead, newKey, newData);
		}
		cout << "insert ended" << endl;
	}

	void InsertRecurse(BST_Node* pSearchTargetNode, int newKey, int newData);

	//검색
	int Retrieve(int retrieveTargetKey)
	{
		if (m_pHead == NULL)
		{
			cout << "cannot retrieve. becuase tree is null." << endl;
			return -1;
		}

		cout << "retrieving BST_Node.... (key : " << retrieveTargetKey << " )" << endl;
		int retrieveValue = RetrieveRecurse(m_pHead, retrieveTargetKey);
		cout << "retrieving ended" << endl;
		return retrieveValue;
	}

	int RetrieveRecurse(BST_Node* pSearchTargetNode, int retrieiveTargetKey);

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

	void RemoveRecurse(BST_Node* pSearchTargetNode, int removeTargetKey);

	//트리 복사
	void CopyFrom(BST* pSourceBST)
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

	void CopyFromRecurse(BST_Node* pSourceNode)
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

	void PreorderPrintRecurse(BST_Node* pTargetNode)
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

	void InorderPrintRecurse(BST_Node* pTargetNode)
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

	void PostOrderPrintRecurse(BST_Node* pTargetNode)
	{
		if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
		if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	}

};

#endif //BST_USING_RECURSE_H