#ifndef SplayTree_H
#define SplayTree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class SplayNode
{
	friend class SplayTree;
	friend class BSTTemplate<SplayNode>;

	int m_key;
	int m_data;
	SplayNode* m_lChild;
	SplayNode* m_rChild;

	SplayNode(int newKey, int newData)
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

class SplayTree : public BSTTemplate<SplayNode>
{
	void SplayTarget(SplayNode* greatgrandfatherOfTraversePtr, SplayNode* grandfatherOfTarget, SplayNode* fatherOfTarget, SplayNode* target);

	//ZIG의 경우에는 부모까지 변화가 일어나는 경우이므로, 부모를 가르키는 조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	//ZIG_ZIG나 ZIG_ZAG와 같이 조부까지 변화가 일어나는 경우를 위해, 조부를 가리키는 증조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	void L_Zig(SplayNode*& fatherOfTarget, SplayNode* target)
	{
		cout << "L_Zig" << endl;
		fatherOfTarget->m_lChild = target->m_rChild;
		target->m_rChild = fatherOfTarget;
		fatherOfTarget = target;
	}

	void R_Zig(SplayNode*& fatherOfTarget, SplayNode* target)
	{
		cout << "R_Zig" << endl;
		fatherOfTarget->m_rChild = target->m_lChild;
		target->m_lChild = fatherOfTarget;
		fatherOfTarget = target;
	}

	void LL_ZigZig(SplayNode*& grandfatherOfTarget, SplayNode* father_of_target, SplayNode* target)
	{
		cout << "LL_ZigZig" << endl;
		grandfatherOfTarget->m_lChild = father_of_target->m_rChild;
		father_of_target->m_rChild = grandfatherOfTarget;
		grandfatherOfTarget = father_of_target;

		father_of_target->m_lChild = target->m_rChild;
		target->m_rChild = father_of_target;
		grandfatherOfTarget = target;
	}

	void LR_ZigZag(SplayNode*& grandfatherOfTarget, SplayNode* father_of_target, SplayNode* target)
	{
		cout << "LR_ZigZag" << endl;
		cout << grandfatherOfTarget->m_key << " " << father_of_target->m_key << " " << target->m_key << endl;
		grandfatherOfTarget->m_lChild = target;
		father_of_target->m_rChild = target->m_lChild;
		target->m_lChild = father_of_target;

		grandfatherOfTarget->m_lChild = target->m_rChild;
		target->m_rChild = grandfatherOfTarget;
		grandfatherOfTarget = target;
	}

	void RL_ZigZag(SplayNode*& grandfatherOfTarget, SplayNode* father_of_target, SplayNode* target)
	{
		cout << "RL_ZigZag" << endl;
		grandfatherOfTarget->m_rChild = target;
		father_of_target->m_lChild = target->m_rChild;
		target->m_rChild = father_of_target;

		grandfatherOfTarget->m_rChild = target->m_lChild;
		target->m_lChild = grandfatherOfTarget;
		grandfatherOfTarget = target;
	}

	void RR_ZigZig(SplayNode*& grandfatherOfTarget, SplayNode* father_of_target, SplayNode* target)
	{
		cout << "RR_ZigZig" << endl;
		grandfatherOfTarget->m_rChild = father_of_target->m_lChild;
		father_of_target->m_lChild = grandfatherOfTarget;
		grandfatherOfTarget = father_of_target;

		father_of_target->m_rChild = target->m_lChild;
		target->m_lChild = father_of_target;
		grandfatherOfTarget = target;
	}


public :
	SplayTree() : BSTTemplate() {}

	int Retrieve(int target_key);
};

#endif //SPLAY_TREE_H