#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

enum NodeColor { RED, BLACK };

//이상하게 여기에만 정의해놨는데도 이 연산자 오버로딩에서는 중복정의 에러가 떠서, 그냥 inline 키워드를 사용해놓음.
//ostream 클래스는 복사생성자가 없으므로, 값복사가 아니라 레퍼런스 방식으로 전달 받도록 함.
inline ostream& operator <<(ostream& out, NodeColor m_color)
{
	if (m_color == RED)
	{
		out << "RED";
	}
	else
	{
		out << "BLACK";
	}
	
	return out;
}

class RedBlackNode
{
	friend class BSTTemplate<RedBlackNode>;
	friend class RedBlackTree;

	int m_key;
	int m_data;
	NodeColor m_color;
	RedBlackNode* m_lChild;
	RedBlackNode* m_rChild;

	RedBlackNode(int newKey, int newData)
	{
		m_key = newKey;
		m_data = newData;
		m_color = BLACK;
		m_lChild = NULL;
		m_rChild = NULL;
	}

	void PrintNode()
	{
		cout << "node newKey : " << m_key << " / node newData : " << m_data << " / node m_color : " << m_color << endl;
	}
};

class RedBlackTree : public BSTTemplate<RedBlackNode>
{
protected :
	//삽입 메소드에서 삽입 위치를 찾기 위해 빈 리프노드 자리로 탐색하는 과정에서 매번 호출되는 메소드다.
	//4노드가 있으면 이를 쪼개놓고 내려가는 로직을 수행한다.
	void CheckAndResolve4NodesWhileDescent(Stack<RedBlackNode*>* routeStack)
	{
		RedBlackNode* targetNode = routeStack->Pop();
		RedBlackNode* parentNode = routeStack->Pop();

		if (Is4Node(targetNode))
		{
			targetNode->m_lChild->m_color = BLACK;
			targetNode->m_rChild->m_color = BLACK;
			if (parentNode != NULL && parentNode->m_color == RED)
			{
				RedBlackNode* grandParentNode = routeStack->Pop();
				RedBlackNode* greatGrandParentNode = routeStack->Pop();

				DoProperRotation(true, targetNode, parentNode, grandParentNode, greatGrandParentNode);

				if (greatGrandParentNode != NULL) routeStack->Push(greatGrandParentNode);
				routeStack->Push(grandParentNode);
			}
			else Split4Node(targetNode);
		}

		routeStack->Push(parentNode);
		routeStack->Push(targetNode);
	}

	bool Is4Node(RedBlackNode* targetNode)
	{
		if (targetNode->m_lChild != NULL && targetNode->m_rChild != NULL)
		{
			if (targetNode->m_lChild->m_color == RED && targetNode->m_rChild->m_color == RED)
			{
				return true;
			}
		}
		return false;
	}

	void Split4Node(RedBlackNode* targetNode)
	{
		if (targetNode != m_head) targetNode->m_color = RED;
	}

	//삽입 메소드에서는 빈 리프노드에 레드 노드의 형태로 삽입이 일어난다.
	//그렇게 삽입이 일어났는데 "조부노드-부모노드-삽입노드"가 "블랙-레드-레드"이렇게 연속적인 레드로 구성될 경우,
	//이를 확인하고 회전으로 해결하기 위한 메소드다.
	void CheckAndResolve4NodesOnDestination(Stack<RedBlackNode*>* routeStack)
	{
		RedBlackNode* targetNode = routeStack->Pop();
		RedBlackNode* parentNode = routeStack->Pop();

		if (parentNode->m_color == RED)
		{
			RedBlackNode* grandParentNode = routeStack->Pop();
			RedBlackNode* greatGrandParentNode = routeStack->Pop();
			DoProperRotation(true, targetNode, parentNode, grandParentNode, greatGrandParentNode);
		}
	}

	void DoProperRotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode* grandParentNode, RedBlackNode* greatGrandParentNode)
	{
		if (greatGrandParentNode == NULL)
		{
			SelectProperRotation(isDoubleRed, targetNode, parentNode, m_head);
		}
		else if (greatGrandParentNode->m_lChild == grandParentNode)
		{
			SelectProperRotation(isDoubleRed, targetNode, parentNode, greatGrandParentNode->m_lChild);
		}
		else
		{
			SelectProperRotation(isDoubleRed, targetNode, parentNode, greatGrandParentNode->m_rChild);
		}
	}

	//회전으로 인해 조부 노드의 위치가 변하면, 증조부 노드의 자식 포인터도 그에 맞게 업데이트해줘야 한다.
	//따라서 조부 노드의 경우에는 단순히 해당 노드의 포인터를 값으로 받아오지 않고, 증조부 노드의 자식 포인터의 레퍼런스 인자로 받아왔다.
	void SelectProperRotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode*& grandParentNode)
	{
		if (grandParentNode->m_lChild == parentNode)
		{
			if (parentNode->m_lChild == targetNode)
			{
				LL_Rotation(isDoubleRed, targetNode, parentNode, grandParentNode);
			}
			else
			{
				LR_Rotation(isDoubleRed, targetNode, parentNode, grandParentNode);
			}
		}
		else
		{
			if (parentNode->m_lChild == targetNode)
			{
				RL_Rotation(isDoubleRed, targetNode, parentNode, grandParentNode);
			}
			else
			{
				RR_Rotation(isDoubleRed, targetNode, parentNode, grandParentNode);
			}
		}
	}

	void LL_Rotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode*& grandParentNode)
	{
		if (isDoubleRed == true)
		{
			grandParentNode->m_color = RED;
			parentNode->m_color = BLACK;
			targetNode->m_color = RED;
		}

		grandParentNode->m_lChild = parentNode->m_rChild;
		parentNode->m_rChild = grandParentNode;
		grandParentNode = parentNode;
	}

	void LR_Rotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode*& grandParentNode)
	{
		grandParentNode->m_lChild = targetNode;
		parentNode->m_rChild = targetNode->m_lChild;
		targetNode->m_lChild = parentNode;
		LL_Rotation(isDoubleRed, parentNode, targetNode, grandParentNode);
	}

	void RL_Rotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode*& grandParentNode)
	{
		grandParentNode->m_rChild = targetNode;
		parentNode->m_lChild = targetNode->m_rChild;
		targetNode->m_rChild = parentNode;
		RR_Rotation(isDoubleRed, parentNode, targetNode, grandParentNode);
	}

	void RR_Rotation(bool isDoubleRed, RedBlackNode* targetNode, RedBlackNode* parentNode, RedBlackNode*& grandParentNode)
	{
		if (isDoubleRed == true)
		{
			grandParentNode->m_color = RED;
			parentNode->m_color = BLACK;
			targetNode->m_color = RED;
		}

		grandParentNode->m_rChild = parentNode->m_lChild;
		parentNode->m_lChild = grandParentNode;
		grandParentNode = parentNode;
	}

	//삭제 대상이 리프 노드여서 아에 삭제되는 경우,
	//그 노드를 가리키는 부모노드의 자식 포인터를 null로 해야하기에 레퍼런스 인자를 두었다.
	void RemoveTarget(RedBlackNode*& targetNode, Stack<RedBlackNode*>* routeStack)
	{
		if (targetNode->m_lChild != NULL && targetNode->m_rChild != NULL)	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(targetNode, routeStack);
		}
		else if (targetNode->m_lChild == NULL && targetNode->m_rChild != NULL)
		{
			ReplaceWithInorderSuccessor(targetNode, routeStack);
		}
		else if (targetNode->m_lChild != NULL && targetNode->m_rChild == NULL)
		{
			ReplaceWithInorderPredecessor(targetNode, routeStack);
		}
		else  //자식이 없는 경우에도 블랙 노드 균형을 맞추기 위한 과정이 필요하므로, 중위후속자 대체 메소드를 호출하도록 하자. 중위후속자가 없으므로 target_node의 자리에서 삭제가 일어나지만 균형을 맞추는 과정은 수행할 것이다.
		{
			ReplaceWithInorderSuccessor(targetNode, routeStack);
		}
	}

	//이진탐색트리에서의 replace_with_inorder_predecessor(...)과 차이점은,
	//중위 선행자나 후속자의 삭제 문제로 대체할 때, 트리의 블랙 노드의 균형이 깨지는 것을 방지하기 위해서 다음을 수행한다는 점이다.
	void ReplaceWithInorderPredecessor(RedBlackNode*& targetNode, Stack<RedBlackNode*>* routeStack)
	{
		if (targetNode->m_lChild != NULL)
		{
			RedBlackNode* traversePtr = targetNode->m_lChild;
			routeStack->Push(traversePtr);
			while (traversePtr->m_rChild != NULL)
			{
				traversePtr = traversePtr->m_rChild;
				routeStack->Push(traversePtr);
			}
		}
		
		RedBlackNode* predecessorNode = routeStack->Pop();
		RedBlackNode* parentOfPredecessor = routeStack->Pop();
		RedBlackNode* grandParentOfPredecessor = routeStack->Pop();
		targetNode->m_key = predecessorNode->m_key;
		targetNode->m_data = predecessorNode->m_data;

		//트리에 헤드 노드만 하나 남은 경우
		if (parentOfPredecessor == NULL)
		{
			delete m_head;
			m_head = NULL;

			return;
		}

		//1.중위 선행자 자신이 레드 노드인가?
		// -> 그렇다면 그냥 삭제하면 된다
		if (predecessorNode->m_color == RED)
		{
			if (parentOfPredecessor->m_lChild == predecessorNode) parentOfPredecessor->m_lChild = NULL;
			else parentOfPredecessor->m_rChild = NULL;
			delete predecessorNode;

			return;
		}
		//2.위 경우가 아니라면, 중위 선행자에게 자식으로 레드 리프 노드가 달려있는가?
		// -> 그렇다면 중위 선행자의 부모에 해당 자식을 붙이며, 해당 빨간 자식 노드의 색깔을 검은색으로 바꾸면 된다
		if ((predecessorNode->m_lChild != NULL) && (predecessorNode->m_lChild->m_color == RED))
		{
			predecessorNode->m_key = predecessorNode->m_lChild->m_key;
			predecessorNode->m_data = predecessorNode->m_lChild->m_data;
			delete predecessorNode->m_lChild;
			predecessorNode->m_lChild == NULL;

			return;
		}
		//3~5. 선행자 본인과 그 자식들로는 블랙 노드의 균형을 맞출 수 없다. 부모와 형제자매 노드를 이용해보자.
		BalanceTheBlackNodeByFamily(predecessorNode, parentOfPredecessor, grandParentOfPredecessor, routeStack);

		return;
	}

	void ReplaceWithInorderSuccessor(RedBlackNode*& targetNode, Stack<RedBlackNode*>* routeStack)
	{
		if (targetNode->m_rChild != NULL)
		{
			RedBlackNode* traversePtr = targetNode->m_rChild;
			routeStack->Push(traversePtr);
			while (traversePtr->m_lChild != NULL)
			{
				traversePtr = traversePtr->m_lChild;
				routeStack->Push(traversePtr);
			}
		}

		RedBlackNode* SuccessorNode = routeStack->Pop();
		RedBlackNode* parentOfSuccessor = routeStack->Pop();
		RedBlackNode* grandParentOfSuccessor = routeStack->Pop();
		targetNode->m_key = SuccessorNode->m_key;
		targetNode->m_data = SuccessorNode->m_data;

		//트리에 헤드 노드만 하나 남은 경우
		if (parentOfSuccessor == NULL) {
			delete m_head;
			m_head = NULL;

			return;
		}

		//1.중위 후속자 자신이 레드 노드인가?
		// -> 그렇다면 그냥 삭제하면 된다
		if (SuccessorNode->m_color == RED) {
			if (parentOfSuccessor->m_rChild == SuccessorNode) parentOfSuccessor->m_rChild = NULL;
			else parentOfSuccessor->m_lChild = NULL;
			delete SuccessorNode;

			return;
		}

		//2.위 경우가 아니라면, 중위 후속자에게 자식으로 레드 리프 노드가 달려있는가?
		// -> 그렇다면 중위 후속자의 부모에 해당 자식을 붙이며, 해당 빨간 자식 노드의 색깔을 검은색으로 바꾸면 된다
		if ((SuccessorNode->m_rChild != NULL) && (SuccessorNode->m_rChild->m_color == RED)) {
			SuccessorNode->m_key = SuccessorNode->m_rChild->m_key;
			SuccessorNode->m_data = SuccessorNode->m_rChild->m_data;
			delete SuccessorNode->m_rChild;
			SuccessorNode->m_rChild == NULL;

			return;
		}

		//3~5.후속자 본인과 그 자식들로는 블랙 노드의 균형을 맞출 수 없다. 부모와 형제자매 노드를 이용해보자.
		if (parentOfSuccessor->m_lChild == SuccessorNode) parentOfSuccessor->m_lChild = NULL;
		else parentOfSuccessor->m_rChild = NULL;
		delete SuccessorNode;
		BalanceTheBlackNodeByFamily(SuccessorNode, parentOfSuccessor, grandParentOfSuccessor, routeStack);
	}

	void BalanceTheBlackNodeByFamily(RedBlackNode* targetNode, RedBlackNode* parentOfTarget, RedBlackNode* grandParentOfTarget, Stack<RedBlackNode*>* routeStack)
	{
		//3.앞선 경우들도 아니라면, 균형을 맞추기 위해 댕겨올 자매노드의 자식(=조카) 레드 노드가 있는가?
		// -> 그렇다면 회전이나 조정을 통해서 블랙 노드의 균형을 맞추면 된다.
		RedBlackNode* brotherNode;
		if (parentOfTarget->m_lChild != NULL && parentOfTarget->m_lChild != targetNode) brotherNode = parentOfTarget->m_lChild;
		else if (parentOfTarget->m_rChild != NULL && parentOfTarget->m_rChild != targetNode) brotherNode = parentOfTarget->m_rChild;
		else brotherNode = NULL;


		if (brotherNode != NULL)
		{
			if (brotherNode->m_color == RED)
			{
				//형제 노드가 레드 노드라면, 균형 조건에 의하면 무조건 두 개의 검은색 조카 노드가 존재한다.
				//그리고 이 조카들과 그것에 달려있을 수 있는 자식 레드 노드들을 사용해서 균형을 맞출 수 있다.
				//이 과정에서는 기존의 LL, LR, RL, RR 회전으로 수행할 수 없으므로, 여기서는 복잡하더라도 직접 노드 관계를 조정한다.
				//조정에 사용한 규칙은 다음과 같다.
				//-우선 삭제되는 중위 선행자나 후속자의 위치를 부모 노드로 채운다.
				//-그리고 이로 인해 비게 되는 부모 노드의 위치를 형제 노드의 자식이나 손자 중에 가장 값이 낮거나(형제가 우측일시), 높은(형제가 좌측일시) 녀석으로 채운다.
				//-여전히 트리 중간에 빈 노드가 존재하는 경우 앞선 방법처럼 가장 높거나 낮은 녀석을 이용해서 채운다.
				if (grandParentOfTarget != NULL && grandParentOfTarget->m_lChild == parentOfTarget)
				{
					DoProperAdjustment(targetNode, brotherNode, grandParentOfTarget->m_lChild);

					return;
				}
				else if (grandParentOfTarget != NULL && grandParentOfTarget->m_rChild == parentOfTarget)
				{
					DoProperAdjustment(targetNode, brotherNode, grandParentOfTarget->m_rChild);

					return;
				}
				else if (grandParentOfTarget == NULL)
				{
					DoProperAdjustment(targetNode, brotherNode, m_head);

					return;
				}
				else
				{
					cout << "Cannot be here! The parentOfTarget should be one of grandParentOfTarget's childs" << endl;

					return;
				}
			}
			else if ((brotherNode->m_lChild != NULL) && (brotherNode->m_lChild->m_color == RED))
			{	
				if (parentOfTarget->m_lChild == brotherNode)
				{
					brotherNode->m_lChild->m_color = parentOfTarget->m_color;
					parentOfTarget->m_color = BLACK;
					brotherNode->m_color = BLACK;
					
				}
				else if (parentOfTarget->m_rChild == brotherNode)
				{
					brotherNode->m_lChild->m_color = parentOfTarget->m_color;
					parentOfTarget->m_color = BLACK;
					brotherNode->m_color = BLACK;
				}
				else
				{
					cout << "Cannot be here! The brotherNode should be one of parentOfTarget's childs" << endl;

					return;
				}

				DoProperRotation(false, brotherNode->m_lChild, brotherNode, parentOfTarget, grandParentOfTarget);

				return;
			}
			else if ((brotherNode->m_rChild != NULL) && (brotherNode->m_rChild->m_color == RED))
			{
				if (parentOfTarget->m_lChild == brotherNode)
				{
					brotherNode->m_rChild->m_color = parentOfTarget->m_color;
					parentOfTarget->m_color = BLACK;
					brotherNode->m_color = BLACK;
				}
				else if (parentOfTarget->m_rChild == brotherNode)
				{
					brotherNode->m_rChild->m_color = parentOfTarget->m_color;
					parentOfTarget->m_color = BLACK;
					brotherNode->m_color = BLACK;
				}
				else
				{
					cout << "Cannot be here! The brotherNode should be one of parentOfTarget's childs" << endl;

					return;
				}
				
				DoProperRotation(false, brotherNode->m_rChild, brotherNode, parentOfTarget, grandParentOfTarget);

				return;
			}
			else
			{
				//댕겨올 조카 노드들이 없으므로, 블럭을 나와 다음 4번 과정으로 진행한다.
			}
		}

		//4.위 경우도 아니라면, 부모노드가 레드노드인가?
		// -> 부모노드는 블랙노드가 되도록 하고, 자매 노드가 있으면 레드 노드가 되도록 하여 균형을 맞추자
		if (parentOfTarget->m_color == RED)
		{
			parentOfTarget->m_color = BLACK;
			if(brotherNode != NULL) brotherNode->m_color = RED;

			return;
		}


		//5.위 경우도 아니라면
		// -> 자매 노드가 있으면 레드 노드가 되도록 하자. 그리고 부모노드 위치의 삭제 문제로 변환하여 다시 3번부터 수행하도록 하자
		if (brotherNode != NULL) brotherNode->m_color = RED;

		if (grandParentOfTarget != NULL)
		{
			targetNode = parentOfTarget;
			parentOfTarget = grandParentOfTarget;
			grandParentOfTarget = routeStack->Pop();

			BalanceTheBlackNodeByFamily(targetNode, parentOfTarget, grandParentOfTarget, routeStack);
		}

		return;
	}
	
	//삭제되는 중위 선행자나 후속자의 부모 노드의 교체를 원활히 교체하기 위해서, 일반 변수가 아니라 레퍼런스 변수로 이를 지칭하였다.
	void DoProperAdjustment(RedBlackNode* targetNode, RedBlackNode* brotherNode, RedBlackNode*& parentOfTarget)
	{

		RedBlackNode* originalParentOfTarget = parentOfTarget;

		if (originalParentOfTarget->m_lChild == brotherNode)
		{
			if (brotherNode->m_rChild->m_rChild != NULL && brotherNode->m_rChild->m_rChild->m_color == RED)
			{
				brotherNode->m_rChild->m_rChild->m_color = BLACK;

				originalParentOfTarget->m_lChild = NULL;
				parentOfTarget = brotherNode->m_rChild->m_rChild;
				brotherNode->m_rChild->m_rChild = NULL;
				parentOfTarget->m_rChild = originalParentOfTarget;
				parentOfTarget->m_lChild = brotherNode;

				return;
			}
			else if (brotherNode->m_rChild->m_lChild != NULL && brotherNode->m_rChild->m_lChild->m_color == RED)
			{
				brotherNode->m_rChild->m_lChild->m_color = BLACK;

				originalParentOfTarget->m_lChild = NULL;
				parentOfTarget = brotherNode->m_rChild;
				brotherNode->m_rChild = brotherNode->m_rChild->m_lChild;
				parentOfTarget->m_rChild = originalParentOfTarget;
				parentOfTarget->m_lChild = brotherNode;

				return;
			}
			else if (brotherNode->m_lChild->m_rChild != NULL && brotherNode->m_lChild->m_rChild->m_color == RED)
			{
				brotherNode->m_color = BLACK;

				originalParentOfTarget->m_lChild = NULL;
				parentOfTarget = brotherNode->m_rChild;
				brotherNode->m_rChild = NULL;
				parentOfTarget->m_rChild = originalParentOfTarget;
				parentOfTarget->m_lChild = brotherNode->m_lChild->m_rChild;
				brotherNode->m_lChild->m_rChild = NULL;
				parentOfTarget->m_lChild->m_rChild = brotherNode;
				parentOfTarget->m_lChild->m_lChild = brotherNode->m_lChild;
				brotherNode->m_lChild = NULL;

				return;
			}
			else if (brotherNode->m_lChild->m_lChild != NULL && brotherNode->m_lChild->m_lChild->m_color == RED)
			{
				originalParentOfTarget->m_lChild = NULL;
				parentOfTarget = brotherNode->m_rChild;
				brotherNode->m_rChild = NULL;
				parentOfTarget->m_rChild = originalParentOfTarget;
				parentOfTarget->m_lChild = brotherNode->m_lChild;
				parentOfTarget->m_lChild->m_rChild = brotherNode;
				brotherNode->m_lChild = NULL;

				return;
			}
			//균형을 맞출 조카의 레드 노드 자식들이 없는 경우에도 조정이 가능하다.
			else
			{
				brotherNode->m_color = BLACK;
				brotherNode->m_lChild->m_color = RED;

				originalParentOfTarget->m_lChild = NULL;
				parentOfTarget = brotherNode->m_rChild;
				brotherNode->m_rChild = NULL;
				parentOfTarget->m_rChild = originalParentOfTarget;
				parentOfTarget->m_lChild = brotherNode;
				return;
			}
		}
		else if (originalParentOfTarget->m_rChild == brotherNode)
		{
			if (brotherNode->m_lChild->m_lChild != NULL && brotherNode->m_lChild->m_lChild->m_color == RED)
			{
				brotherNode->m_lChild->m_lChild->m_color = BLACK;

				originalParentOfTarget->m_rChild = NULL;
				parentOfTarget = brotherNode->m_lChild->m_lChild;
				brotherNode->m_lChild->m_lChild = NULL;
				parentOfTarget->m_lChild = originalParentOfTarget;
				parentOfTarget->m_rChild = brotherNode;

				return;
			}
			else if (brotherNode->m_lChild->m_rChild != NULL && brotherNode->m_lChild->m_rChild->m_color == RED)
			{
				brotherNode->m_lChild->m_rChild->m_color = BLACK;

				originalParentOfTarget->m_rChild = NULL;
				parentOfTarget = brotherNode->m_lChild;
				brotherNode->m_lChild = brotherNode->m_lChild->m_rChild;
				parentOfTarget->m_lChild = originalParentOfTarget;
				parentOfTarget->m_rChild = brotherNode;

				return;
			}
			else if (brotherNode->m_rChild->m_lChild != NULL && brotherNode->m_rChild->m_lChild->m_color == RED)
			{
				brotherNode->m_color = BLACK;

				originalParentOfTarget->m_rChild = NULL;
				parentOfTarget = brotherNode->m_lChild;
				brotherNode->m_lChild = NULL;
				parentOfTarget->m_lChild = originalParentOfTarget;
				parentOfTarget->m_rChild = brotherNode->m_rChild->m_lChild;
				brotherNode->m_rChild->m_lChild = NULL;
				parentOfTarget->m_rChild->m_lChild = brotherNode;
				parentOfTarget->m_rChild->m_rChild = brotherNode->m_rChild;
				brotherNode->m_rChild = NULL;

				return;
			}
			else if (brotherNode->m_rChild->m_rChild != NULL && brotherNode->m_rChild->m_rChild->m_color == RED)
			{
				originalParentOfTarget->m_rChild = NULL;
				parentOfTarget = brotherNode->m_lChild;
				brotherNode->m_lChild = NULL;
				parentOfTarget->m_lChild = originalParentOfTarget;
				parentOfTarget->m_rChild = brotherNode->m_rChild;
				parentOfTarget->m_rChild->m_lChild = brotherNode;
				brotherNode->m_rChild = NULL;


				return;
			}
			//균형을 맞출 조카의 레드 노드 자식들이 없는 경우에도 조정이 가능하다.
			else
			{
				brotherNode->m_color = BLACK;
				brotherNode->m_rChild->m_color = RED;

				originalParentOfTarget->m_rChild = NULL;
				parentOfTarget = brotherNode->m_lChild;
				brotherNode->m_lChild = NULL;
				parentOfTarget->m_lChild = originalParentOfTarget;
				parentOfTarget->m_rChild = brotherNode;
				return;
			}
		}
		else
		{
			cout << "Cannot be here! The brotherNode should be one of ParentOfTarget's childs" << endl;

			return;
		}
	}


public :
	RedBlackTree() : BSTTemplate() {}

	void Insert(int newKey, int newData)
	{
		if (m_head == NULL)
		{
			m_head = new RedBlackNode(newKey, newData);

			return;
		}

		RedBlackNode* traversePtr = m_head;
		Stack<RedBlackNode*> routeStack;
		while (true)
		{
			routeStack.Push(traversePtr);
			CheckAndResolve4NodesWhileDescent(&routeStack);

			if (newKey < traversePtr->m_key)
			{
				if (traversePtr->m_lChild != NULL)
				{
					traversePtr = traversePtr->m_lChild;
				}
				else
				{
					traversePtr->m_lChild = new RedBlackNode(newKey, newData);
					traversePtr->m_lChild->m_color = RED;
					routeStack.Push(traversePtr->m_lChild);
					CheckAndResolve4NodesOnDestination(&routeStack);

					return;
				}
			}
			else if (traversePtr->m_key < newKey)
			{
				if (traversePtr->m_rChild != NULL)
				{
					traversePtr = traversePtr->m_rChild;
				}
				else
				{
					traversePtr->m_rChild = new RedBlackNode(newKey, newData);
					traversePtr->m_rChild->m_color = RED;
					routeStack.Push(traversePtr->m_rChild);
					CheckAndResolve4NodesOnDestination(&routeStack);

					return;
				}
			}
			else
			{
				cout << "Cannot Insert node to tree! There are same newKey node already!" << endl;

				return;
			}
		}
	}

	void Remove(int targetKey)
	{
		Stack<RedBlackNode*> routeStack;

		if (m_head->m_key == targetKey)
		{
			routeStack.Push(m_head);
			RemoveTarget(m_head, &routeStack);

			return;
		}

		RedBlackNode* traversePtr = m_head;
		while (true)
		{
			if (targetKey < traversePtr->m_key)
			{
				if (traversePtr->m_lChild != NULL)
				{
					routeStack.Push(traversePtr);
					traversePtr = traversePtr->m_lChild;
				}
				else
				{
					cout << "Cannot Remove! Cannot find such target node!" << endl;

					return;
				}
			}
			else if (traversePtr->m_key < targetKey)
			{
				if (traversePtr->m_rChild != NULL)
				{
					routeStack.Push(traversePtr);
					traversePtr = traversePtr->m_rChild;
				}
				else
				{
					cout << "Cannot Remove! Cannot find such target node!" << endl;

					return;
				}
			}
			else
			{
				RedBlackNode* parent = routeStack.GetTop();
				routeStack.Push(traversePtr);
				if (parent->m_lChild == traversePtr)
				{
					RemoveTarget(parent->m_lChild, &routeStack);
				}
				else
				{
					RemoveTarget(parent->m_rChild, &routeStack);
				}

				return;
			}
		}
	}
};

#endif //RED_BLACK_TREE_H