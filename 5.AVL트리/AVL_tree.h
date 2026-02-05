#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class AVL_Node
{
private:
	friend class BST_Template<AVL_Node>;
	friend class AVL_Tree;

	int m_key;
	int m_data;
	int m_heightFromLeaf;
	AVL_Node* m_pLeftChild;
	AVL_Node* m_pRightChild;

	AVL_Node(int newKey, int newData)
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

class AVL_Tree : public BST_Template<AVL_Node>
{
private:
	void RemoveTarget(AVL_Node*& pTarget, Stack<AVL_Node*>* pRouteStack);

	void ReplaceWithInorderPredecessor(AVL_Node*& pTarget, Stack<AVL_Node*>* pRouteStack);

	void ReplaceWithInorderSuccessor(AVL_Node*& pTarget, Stack<AVL_Node*>* pRouteStack);

	void BalancingAllTargetToRoot(Stack<AVL_Node*>* pRouteStack);

	void BalancingTargetNode(AVL_Node* pTarget, AVL_Node* pParent);

	void LL_Rotation(AVL_Node* pTarget, AVL_Node* pParent);

	void LR_Rotation(AVL_Node* pTarget, AVL_Node* pParent);

	void RL_Rotation(AVL_Node* pTarget, AVL_Node* pParent);

	void RR_Rotation(AVL_Node* pTarget, AVL_Node* pParent);

	void UpdateHeight(AVL_Node* pTarget)
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
	AVL_Tree() : BST_Template() {}

	void Insert(int newKey, int newData);

	void Remove(int targetKey);
};

#endif //AVL_TREE_H