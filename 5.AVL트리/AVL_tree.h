#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class AVLNode {
	friend class BSTTemplate<AVLNode>;
	friend class AVL_tree;
	int m_key;
	int m_data;
	int m_heightFromLeaf;
	AVLNode* m_lChild;
	AVLNode* m_rChild;

	AVLNode(int newKey, int newData) {
		this->m_key = newKey;
		this->m_data = newData;
		this->m_heightFromLeaf = 0;
		this->m_lChild = NULL;
		this->m_rChild = NULL;
	}

	inline void PrintNode() {
		cout << "node m_key : " << m_key << " / node m_data : " << m_data << endl;
	}
};

class AVL_tree : public BSTTemplate<AVLNode> {
protected :
	void RemoveTarget(AVLNode*& targetPtr, Stack<AVLNode*>* ancesterNodeStack);

	void ReplaceWithInorderPredecessor(AVLNode*& targetPtr, Stack<AVLNode*>* ancesterNodeStack);

	void ReplaceWithInorderSuccessor(AVLNode*& targetPtr, Stack<AVLNode*>* ancesterNodeStack);

	void BalancingAllTargetToRoot(Stack<AVLNode*>* ancesterNodeStack);

	void BalancingTargetNode(AVLNode* targetNode, AVLNode* parentNode);

	void LLRotation(AVLNode* targetNode, AVLNode* parentNode);

	void LRRotation(AVLNode* targetNode, AVLNode* parentNode);

	void RLRotation(AVLNode* targetNode, AVLNode* parentNode);

	void RRRotation(AVLNode* targetNode, AVLNode* parentNode);

	void UpdateHeight(AVLNode* targetNode) {
		int heightFromLChild = 0;
		int heightFromRChild = 0;
		if (targetNode->m_lChild != NULL) heightFromLChild = 1 + targetNode->m_lChild->m_heightFromLeaf;
		if (targetNode->m_rChild != NULL) heightFromRChild = 1 + targetNode->m_rChild->m_heightFromLeaf;
		targetNode->m_heightFromLeaf = Max(heightFromLChild, heightFromRChild);
	}

	int Max(int a, int b) {
		return (a > b) ? a : b;
	}

public :
	AVL_tree() : BSTTemplate() {}

	void Insert(int newKey, int newData);

	void Remove(int targetKey);
};

#endif //AVL_TREE_H