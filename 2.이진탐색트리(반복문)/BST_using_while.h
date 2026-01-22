#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "stack.h"

template <class T>
class BSTTemplate;


class BSTNode
{
	friend class BSTTemplate<BSTNode>;

	int m_key;
	int m_data;
	BSTNode* m_pLeftChild;
	BSTNode* m_pRightChild;

	BSTNode(int newKey, int newData)
	{
		m_key = newKey;
		m_data = newData;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}

	inline void PrintNode()
	{
		cout << "node m_key : " << m_key << " / node m_data : " << m_data << endl;
	}
};


//이진 탐색 트리를 상속받아 더 특수화된 트리(eg. SplayTree 등)를 만들 때 내부 노드 클래스를 변경하기 쉽도록, 사용할 내부 노드 클래스를 템플릿 인자로 정의하였다.
//따라서, 이진 탐색 트리에서 더 특수화된 트리을 정의하고 싶다면, BST_template에 자신이 정의한 새 노드 클래스를 인자로 준 것을 그것을 상속받으면 된다. (eg. class SplayTree : public BST_template<SplayNode> {};)
//또한 우리가 일반적으로 사용할 이진 탐색 트리도 이 템플릿에 BST_node를 인자로 준 특수화된 경우로 class BST를 이 다음 클래스로 정의해놓았으니 그것을 사용하면 된다.
template <class NodeType = BSTNode>
class BSTTemplate
{
protected:
	NodeType* m_pHead;

	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	NodeType* Search(int targetKey, NodeType* (BSTTemplate::* pToDoWithTargetPtr)(NodeType*&))
	{
		if (m_pHead == NULL) return (this->*pToDoWithTargetPtr)(m_pHead);
		else if (targetKey == m_pHead->m_key) return (this->*pToDoWithTargetPtr)(m_pHead);

		NodeType* pSearch = m_pHead;
		while (true)
		{
			if (targetKey < pSearch->m_key)
			{
				if (pSearch->m_pLeftChild != NULL && pSearch->m_pLeftChild->m_key != targetKey) pSearch = pSearch->m_pLeftChild;
				else return (this->*pToDoWithTargetPtr)(pSearch->m_pLeftChild);
			}
			else
			{
				if (pSearch->m_pRightChild != NULL && pSearch->m_pRightChild->m_key != targetKey) pSearch = pSearch->m_pRightChild;
				else return (this->*pToDoWithTargetPtr)(pSearch->m_pRightChild);
			}
		}
	}

	NodeType* GetT(NodeType*& pParentSeat)
	{
		return pParentSeat;
	}

	NodeType* SetDummyChild(NodeType*& pParentSeat)
	{
		return pParentSeat = new NodeType(0, 0);
	}

	NodeType* RemoveTarget(NodeType*& pTarget)
	{
		if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild != NULL)	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(pTarget);
		}
		else if (pTarget->m_pLeftChild == NULL && pTarget->m_pRightChild != NULL)
		{
			ReplaceWithInorderSuccessor(pTarget);
		}
		else if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild == NULL)
		{
			ReplaceWithInorderPredecessor(pTarget);
		}
		else
		{
			delete pTarget;
			pTarget = NULL;
			return pTarget;
		}
	}

	void ReplaceWithInorderPredecessor(NodeType*& pTarget)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTarget->m_pLeftChild;
		while (pTraverse->m_pRightChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
		}

		if (pPrevious != NULL) pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
		else pTarget->m_pLeftChild = pTraverse->m_pLeftChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}

	void ReplaceWithInorderSuccessor(NodeType*& pTarget)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTarget->m_pRightChild;
		while (pTraverse->m_pLeftChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
		}

		if (pPrevious != NULL) pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
		else pTarget->m_pRightChild = pTraverse->m_pRightChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}


	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void PreorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* pOptionalTargetBST)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		NodeType* pTraverse = NULL;
		headStack.Push(this->m_pHead);
		while ((pTraverse = headStack.Pop()))
		{
			(*pToDoWhileTraverse)(pTraverse, pOptionalTargetBST);

			if (pTraverse->m_pRightChild != NULL) headStack.Push(pTraverse->m_pRightChild);
			if (pTraverse->m_pLeftChild != NULL) headStack.Push(pTraverse->m_pLeftChild);
		}
	}

	void InorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* pOptionalTargetBST)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_pHead);
		bool newLeftSpine = true;
		while (!headStack.IsEmpty())
		{
			while (newLeftSpine && headStack.GetTop()->m_pLeftChild)
			{
				headStack.Push(headStack.GetTop()->m_pLeftChild);
			}

			NodeType* pTraverse = headStack.Pop();
			(*pToDoWhileTraverse)(pTraverse, pOptionalTargetBST);

			if (pTraverse->m_pRightChild != NULL)
			{
				headStack.Push(pTraverse->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				newLeftSpine = false;
			}
		}
	}

	void PostorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* pOptionalTargetBST)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_pHead);
		bool newLeftSpine = true;
		bool newRightSpine = true;
		while (!headStack.IsEmpty())
		{
			while (newLeftSpine && headStack.GetTop()->m_pLeftChild)
			{
				headStack.Push(headStack.GetTop()->m_pLeftChild);
			}

			if (newRightSpine && headStack.GetTop()->m_pRightChild)
			{
				headStack.Push(headStack.GetTop()->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				(*pToDoWhileTraverse)(headStack.GetTop(), pOptionalTargetBST);

				newLeftSpine = false;
				NodeType* pPreviousNode = headStack.Pop();
				NodeType* pPpresentNode = headStack.GetTop();

				if (pPpresentNode && pPpresentNode->m_pRightChild && (pPpresentNode->m_pRightChild == pPreviousNode)) newRightSpine = false;
				else newRightSpine = true;
			}
		}
	}

	static void PrintTargetNode(NodeType* pTargetNode, BSTTemplate* pDummyArgument)
	{
		pTargetNode->PrintNode();
	}

	static void RemoveChilds(NodeType* pTargetNode, BSTTemplate* pDummyArgument)
	{
		if (pTargetNode->m_pLeftChild != NULL)
		{
			delete pTargetNode->m_pLeftChild;
			pTargetNode->m_pLeftChild = NULL;
		}
		if (pTargetNode->m_pRightChild != NULL)
		{
			delete pTargetNode->m_pRightChild;
			pTargetNode->m_pRightChild = NULL;
		}
	}

	static void CopyNode(NodeType* pSourceNode, BSTTemplate* pDestBST)
	{
		pDestBST->Insert(pSourceNode);
	}


public:
	BSTTemplate()
	{
		cout << "BST is being made!" << endl;
		m_pHead = NULL;
	}

	~BSTTemplate()
	{
		cout << "BST is being removed" << endl;
		RemoveAll();
	}

	void Insert(int newKey, int newData)
	{
		NodeType* pMadeChild = Search(newKey, &BSTTemplate::SetDummyChild);
		pMadeChild->m_key = newKey;
		pMadeChild->m_data = newData;
	}

	void Insert(NodeType* pNewNode)
	{
		NodeType* pMadeChild = Search(pNewNode->m_key, &BSTTemplate::SetDummyChild);
		*pMadeChild = *pNewNode;
	}

	int Retrieve(int targetKey)
	{
		return Search(targetKey, &BSTTemplate::GetT)->m_data;
	}

	void Remove(int targetKey)
	{
		Search(targetKey, &BSTTemplate::RemoveTarget);
	}

	void CopyFrom(BSTTemplate* pTargetBST)
	{
		pTargetBST->PreorderTraverse(&BSTTemplate::CopyNode, this);
	}

	void RemoveAll()
	{
		cout << "Remove all" << endl;
		PostorderTraverse(&BSTTemplate::RemoveChilds, NULL);
		delete m_pHead;
		m_pHead = NULL;
	}

	void PreorderPrint()
	{
		cout << "preorder traverse start" << endl;
		PreorderTraverse(&BSTTemplate::PrintTargetNode, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void InorderPrint()
	{
		cout << "inorder traverse start" << endl;
		InorderTraverse(&BSTTemplate::PrintTargetNode, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void PostorderPrint()
	{
		cout << "postorder traverse start" << endl;
		PostorderTraverse(&BSTTemplate::PrintTargetNode, NULL);
		cout << "traverse ended" << endl << endl;
	}
};


class BST : public BSTTemplate<BSTNode>
{
public:
	BST() : BSTTemplate() {}
};

#endif //BST_USING_WHILE_H