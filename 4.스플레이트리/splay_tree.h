#ifndef SplayTree_H
#define SplayTree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class SplayNode
{
	friend class SplayTree;
	friend class BSTTemplate<SplayNode>;

	int m_key;
	int m_data;
	SplayNode* m_pLeftChild;
	SplayNode* m_pRightChild;

	SplayNode(int newKey, int newData)
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

class SplayTree : public BSTTemplate<SplayNode>
{
	void SplayTarget(SplayNode* pGreatGrandFatherOfTarget, SplayNode* pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget);

	//ZIG의 경우에는 부모까지 변화가 일어나는 경우이므로, 부모를 가르키는 조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	//ZIG_ZIG나 ZIG_ZAG와 같이 조부까지 변화가 일어나는 경우를 위해, 조부를 가리키는 증조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	void L_Zig(SplayNode*& pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "L_Zig" << endl;
		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;
		pFatherOfTarget = pTarget;
	}

	void R_Zig(SplayNode*& pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "R_Zig" << endl;
		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;
		pFatherOfTarget = pTarget;
	}

	void LL_ZigZig(SplayNode*& pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "LL_ZigZig" << endl;
		pGrandFatherOfTarget->m_pLeftChild = pFatherOfTarget->m_pRightChild;
		pFatherOfTarget->m_pRightChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pFatherOfTarget;

		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void LR_ZigZag(SplayNode*& pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "LR_ZigZag" << endl;
		cout << pGrandFatherOfTarget->m_key << " " << pFatherOfTarget->m_key << " " << pTarget->m_key << endl;
		pGrandFatherOfTarget->m_pLeftChild = pTarget;
		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;

		pGrandFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void RL_ZigZag(SplayNode*& pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "RL_ZigZag" << endl;
		pGrandFatherOfTarget->m_pRightChild = pTarget;
		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;

		pGrandFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void RR_ZigZig(SplayNode*& pGrandFatherOfTarget, SplayNode* pFatherOfTarget, SplayNode* pTarget)
	{
		cout << "RR_ZigZig" << endl;
		pGrandFatherOfTarget->m_pRightChild = pFatherOfTarget->m_pLeftChild;
		pFatherOfTarget->m_pLeftChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pFatherOfTarget;

		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}


public :
	SplayTree() : BSTTemplate() {}

	int Retrieve(int targetKey);
};

#endif //SPLAY_TREE_H