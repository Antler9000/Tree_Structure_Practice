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
	BSTNode* m_lChild;
	BSTNode* m_rChild;

	BSTNode(int newKey, int newData)
	{
		m_key = newKey;
		m_data = newData;
		m_lChild = NULL;
		m_rChild = NULL;
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
	NodeType* m_head;

	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	NodeType* Search(int targetKey, NodeType* (BSTTemplate::* toDoWithTargetPtr)(NodeType*&))
	{
		if (m_head == NULL) return (this->*toDoWithTargetPtr)(m_head);
		else if (targetKey == m_head->m_key) return (this->*toDoWithTargetPtr)(m_head);

		NodeType* searchPtr = m_head;
		while (true)
		{
			if (targetKey < searchPtr->m_key)
			{
				if (searchPtr->m_lChild != NULL && searchPtr->m_lChild->m_key != targetKey) searchPtr = searchPtr->m_lChild;
				else return (this->*toDoWithTargetPtr)(searchPtr->m_lChild);
			}
			else
			{
				if (searchPtr->m_rChild != NULL && searchPtr->m_rChild->m_key != targetKey) searchPtr = searchPtr->m_rChild;
				else return (this->*toDoWithTargetPtr)(searchPtr->m_rChild);
			}
		}
	}

	NodeType* GetT(NodeType*& parentSeat)
	{
		return parentSeat;
	}

	NodeType* SetDummyChild(NodeType*& parentSeat)
	{
		return parentSeat = new NodeType(0, 0);
	}

	NodeType* RemoveTarget(NodeType*& targetPtr)
	{
		if (targetPtr->m_lChild != NULL && targetPtr->m_rChild != NULL)	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(targetPtr);
		}
		else if (targetPtr->m_lChild == NULL && targetPtr->m_rChild != NULL)
		{
			ReplaceWithInorderSuccessor(targetPtr);
		}
		else if (targetPtr->m_lChild != NULL && targetPtr->m_rChild == NULL)
		{
			ReplaceWithInorderPredecessor(targetPtr);
		}
		else
		{
			delete targetPtr;
			targetPtr = NULL;
			return targetPtr;
		}
	}

	void ReplaceWithInorderPredecessor(NodeType*& targetPtr)
	{
		NodeType* previousPtr = NULL;
		NodeType* traversePtr = targetPtr->m_lChild;
		while (traversePtr->m_rChild != NULL)
		{
			previousPtr = traversePtr;
			traversePtr = traversePtr->m_rChild;
		}

		if (previousPtr != NULL) previousPtr->m_rChild = traversePtr->m_lChild;
		else targetPtr->m_lChild = traversePtr->m_lChild;

		targetPtr->m_key = traversePtr->m_key;
		targetPtr->m_data = traversePtr->m_data;
		delete traversePtr;
	}

	void ReplaceWithInorderSuccessor(NodeType*& targetPtr)
	{
		NodeType* previousPtr = NULL;
		NodeType* traversePtr = targetPtr->m_rChild;
		while (traversePtr->m_lChild != NULL)
		{
			previousPtr = traversePtr;
			traversePtr = traversePtr->m_lChild;
		}

		if (previousPtr != NULL) previousPtr->m_lChild = traversePtr->m_rChild;
		else targetPtr->m_rChild = traversePtr->m_rChild;

		targetPtr->m_key = traversePtr->m_key;
		targetPtr->m_data = traversePtr->m_data;
		delete traversePtr;
	}


	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void PreorderTraverse(void (*toDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* optionalTargetBST)
	{
		if (m_head == NULL) return;

		Stack<NodeType*> headStack;
		NodeType* traversePtr = NULL;
		headStack.Push(this->m_head);
		while ((traversePtr = headStack.Pop()))
		{
			(*toDoWhileTraverse)(traversePtr, optionalTargetBST);

			if (traversePtr->m_rChild != NULL) headStack.Push(traversePtr->m_rChild);
			if (traversePtr->m_lChild != NULL) headStack.Push(traversePtr->m_lChild);
		}
	}

	void InorderTraverse(void (*toDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* optionalTargetBST)
	{
		if (m_head == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_head);
		bool newLeftSpine = true;
		while (!headStack.IsEmpty())
		{
			while (newLeftSpine && headStack.GetTop()->m_lChild)
			{
				headStack.Push(headStack.GetTop()->m_lChild);
			}

			NodeType* traversePtr = headStack.Pop();
			(*toDoWhileTraverse)(traversePtr, optionalTargetBST);

			if (traversePtr->m_rChild != NULL)
			{
				headStack.Push(traversePtr->m_rChild);
				newLeftSpine = true;
			}
			else
			{
				newLeftSpine = false;
			}
		}
	}

	void PostorderTraverse(void (*toDoWhileTraverse)(NodeType*, BSTTemplate*), BSTTemplate* optionalTargetBST)
	{
		if (m_head == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_head);
		bool newLeftSpine = true;
		bool newRightSpine = true;
		while (!headStack.IsEmpty())
		{
			while (newLeftSpine && headStack.GetTop()->m_lChild)
			{
				headStack.Push(headStack.GetTop()->m_lChild);
			}

			if (newRightSpine && headStack.GetTop()->m_rChild)
			{
				headStack.Push(headStack.GetTop()->m_rChild);
				newLeftSpine = true;
			}
			else
			{
				(*toDoWhileTraverse)(headStack.GetTop(), optionalTargetBST);

				newLeftSpine = false;
				NodeType* previousNode = headStack.Pop();
				NodeType* presentNode = headStack.GetTop();

				if (presentNode && presentNode->m_rChild && (presentNode->m_rChild == previousNode)) newRightSpine = false;
				else newRightSpine = true;
			}
		}
	}

	static void PrintTargetNode(NodeType* targetNode, BSTTemplate* dummyArgument)
	{
		targetNode->PrintNode();
	}

	static void RemoveChilds(NodeType* targetNode, BSTTemplate* dummyArgument)
	{
		if (targetNode->m_lChild != NULL)
		{
			delete targetNode->m_lChild;
			targetNode->m_lChild = NULL;
		}
		if (targetNode->m_rChild != NULL)
		{
			delete targetNode->m_rChild;
			targetNode->m_rChild = NULL;
		}
	}

	static void CopyNode(NodeType* sourceNode, BSTTemplate* destBST)
	{
		destBST->Insert(sourceNode->m_key, sourceNode->m_data);
	}


public:
	BSTTemplate()
	{
		cout << "BST is being made!" << endl;
		m_head = NULL;
	}

	~BSTTemplate()
	{
		cout << "BST is being removed" << endl;
		RemoveAll();
	}

	void Insert(int newKey, int newData)
	{
		NodeType* made_child = Search(newKey, &BSTTemplate::SetDummyChild);
		made_child->m_key = newKey;
		made_child->m_data = newData;
	}

	int Retrieve(int targetKey)
	{
		return Search(targetKey, &BSTTemplate::GetT)->m_data;
	}

	void Remove(int targetKey)
	{
		Search(targetKey, &BSTTemplate::RemoveTarget);
	}

	void CopyFrom(BSTTemplate* targetBST)
	{
		targetBST->PreorderTraverse(&BSTTemplate::CopyNode, this);
	}

	void RemoveAll()
	{
		cout << "Remove all" << endl;
		PostorderTraverse(&BSTTemplate::RemoveChilds, NULL);
		delete m_head;
		m_head = NULL;
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