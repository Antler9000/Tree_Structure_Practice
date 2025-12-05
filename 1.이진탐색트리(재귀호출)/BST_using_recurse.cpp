#include <iostream>
#include "BST_using_recurse.h"
using namespace std;

void BST::ReplaceWithInorderPredecessor(Node* removeTargetNode) {
	Node* previousPtr = NULL;
	Node* traversePtr = removeTargetNode->m_lChild;
	while (traversePtr->m_rChild != NULL) {
		previousPtr = traversePtr;
		traversePtr = traversePtr->m_rChild;
	}
	if (previousPtr != NULL) previousPtr->m_rChild = traversePtr->m_lChild;
	else removeTargetNode->m_lChild = traversePtr->m_lChild;
	removeTargetNode->m_key = traversePtr->m_key;
	removeTargetNode->m_data = traversePtr->m_data;
	delete traversePtr;
	if (previousPtr != NULL) previousPtr->m_rChild = NULL;
}

void BST::ReplaceWithInorderSuccessor(Node* removeTargetNode) {
	Node* previous_ptr = NULL;
	Node* traverse_ptr = removeTargetNode->m_rChild;
	while (traverse_ptr->m_lChild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->m_lChild;
	}
	if (previous_ptr != NULL) previous_ptr->m_lChild = traverse_ptr->m_rChild;
	else removeTargetNode->m_rChild = traverse_ptr->m_rChild;
	removeTargetNode->m_key = traverse_ptr->m_key;
	removeTargetNode->m_data = traverse_ptr->m_data;
	delete traverse_ptr;
	if (previous_ptr != NULL) previous_ptr->m_lChild = NULL;
}

void BST::RemoveTarget(Node*& removeTargetNode) {
	if (removeTargetNode->m_lChild != NULL && removeTargetNode->m_rChild != NULL) {								//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		ReplaceWithInorderSuccessor(removeTargetNode);
	}
	else if (removeTargetNode->m_lChild == NULL && removeTargetNode->m_rChild != NULL) {
		ReplaceWithInorderSuccessor(removeTargetNode);
	}
	else if (removeTargetNode->m_lChild != NULL && removeTargetNode->m_rChild == NULL) {
		ReplaceWithInorderPredecessor(removeTargetNode);
	}
	else {
		delete removeTargetNode;
		removeTargetNode = NULL;
	}
}

void BST::InsertRecurse(Node* searchTargetNode, int newKey, int newData) {
	if (newKey < searchTargetNode->m_key) {
		if(searchTargetNode->m_lChild == NULL) searchTargetNode->m_lChild = new Node(newKey, newData);
		else InsertRecurse(searchTargetNode->m_lChild, newKey, newData);
	}
	else if(searchTargetNode->m_key < newKey) {
		if (searchTargetNode->m_rChild == NULL) searchTargetNode->m_rChild = new Node(newKey, newData);
		else InsertRecurse(searchTargetNode->m_rChild, newKey, newData);
	}
	else {
		cout << "cannot insert! key is same! If it is dummy_room_node, then it is okay" << endl;
	}
}

int BST::RetrieveRecurse(Node* searchTargetNode, int retrieveTargetKey) {
	if (retrieveTargetKey < searchTargetNode->m_key) {
		if (searchTargetNode->m_lChild != NULL) return RetrieveRecurse(searchTargetNode->m_lChild, retrieveTargetKey);
		else  cout << "there is no such key in searching." << endl;
	}
	else if (retrieveTargetKey > searchTargetNode->m_key) {
		if (searchTargetNode->m_rChild != NULL) return RetrieveRecurse(searchTargetNode->m_rChild, retrieveTargetKey);
		else  cout << "there is no such key in searching." << endl;
	}
	else {
		return searchTargetNode->m_data;
	}
}

void BST::RemoveRecurse(Node* searchTargetNode, int removeTargetKey) {
	if (removeTargetKey < searchTargetNode->m_key) {
		if (searchTargetNode->m_lChild->m_key == removeTargetKey) {
			RemoveTarget(searchTargetNode->m_lChild);
		}
		else {
			RemoveRecurse(searchTargetNode->m_lChild, removeTargetKey);
		}
	}
	else if (removeTargetKey > searchTargetNode->m_key) {
		if (searchTargetNode->m_rChild->m_key == removeTargetKey) {
			RemoveTarget(searchTargetNode->m_rChild);
		}
		else {
			RemoveRecurse(searchTargetNode->m_rChild, removeTargetKey);
		}
	}
	else {
		cout << "should not reach here while RemoveRecurse()" << endl;
	}
}


