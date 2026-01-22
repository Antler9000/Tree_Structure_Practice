#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class AVLNode
{
	friend class BSTTemplate<AVLNode>;
	friend class AVL_tree;

	int m_key;
	int m_data;
	int m_heightFromLeaf;
	AVLNode* m_pLeftChild;
	AVLNode* m_pRightChild;

	AVLNode(int newKey, int newData)
	{
		m_key = newKey;
		m_data = newData;
		m_heightFromLeaf = 0;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}

	inline void PrintNode()
	{
		cout << "node m_key : " << m_key << " / node m_data : " << m_data << endl;
	}
};

class AVL_tree : public BSTTemplate<AVLNode>
{
protected:
	void RemoveTarget(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack);

	void ReplaceWithInorderPredecessor(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack);

	void ReplaceWithInorderSuccessor(AVLNode*& pTarget, Stack<AVLNode*>* pRouteStack);

	void BalancingAllTargetToRoot(Stack<AVLNode*>* pRouteStack);

	void BalancingTargetNode(AVLNode* pTarget, AVLNode* pParent);

	void LL_Rotation(AVLNode* pTarget, AVLNode* pParent);

	void LR_Rotation(AVLNode* pTarget, AVLNode* pParent);

	void RL_Rotation(AVLNode* pTarget, AVLNode* pParent);

	void RR_Rotation(AVLNode* pTarget, AVLNode* pParent);

	void UpdateHeight(AVLNode* pTarget)
	{
		int heightFromLChild = 0;
		int heightFromRChild = 0;
		if (pTarget->m_pLeftChild != NULL) heightFromLChild = 1 + pTarget->m_pLeftChild->m_heightFromLeaf;
		if (pTarget->m_pRightChild != NULL) heightFromRChild = 1 + pTarget->m_pRightChild->m_heightFromLeaf;
		pTarget->m_heightFromLeaf = Max(heightFromLChild, heightFromRChild);
	}

	int Max(int a, int b)
	{
		return (a > b) ? a : b;
	}

public:
	AVL_tree() : BSTTemplate() {}

	void Insert(int newKey, int newData);

	void Remove(int targetKey);
};

#endif //AVL_TREE_H