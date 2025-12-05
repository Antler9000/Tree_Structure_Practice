#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;

class BST;

class Node {
	int m_data;
	int m_key;
	Node* m_lChild;
	Node* m_rChild;

	friend BST;

	Node(int key, int data) {
		this->m_key = key;
		this->m_data = data;
		this->m_lChild = NULL;
		this->m_rChild = NULL;
	}

	~Node() {
		delete m_lChild;
		delete m_rChild;
	}
};

class BST {
	Node* m_head;

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꿔야하므로, 레퍼런스 인자로 받음
	void RemoveTarget(Node*& removeTargetNode);

	void ReplaceWithInorderPredecessor(Node* removeTargetNode);

	void ReplaceWithInorderSuccessor(Node* removeTargetNode);

public:
	BST() {
		m_head = NULL;
	}

	~BST() {
		RemoveAll();
	}

	//삽입
	void Insert(int newKey, int newData) {
		cout << "inserting Node.... (key : " << newKey << ", data : " << newData << " )" << endl;
		if (m_head == NULL) {
			m_head = new Node(newKey, newData);
		}
		else {
			InsertRecurse(m_head, newKey, newData);
		}
		cout << "insert ended" << endl;
	}

	void InsertRecurse(Node* searchTargetNode, int newKey, int newData);

	//검색
	int Retrieve(int retrieveTargetKey) {
		if (m_head == NULL) {
			cout << "cannot retrieve. becuase tree is null." << endl;
			return -1;
		}

		cout << "retrieving Node.... (key : " << retrieveTargetKey << " )" << endl;
		int retrieveValue = RetrieveRecurse(m_head, retrieveTargetKey);
		cout << "retrieving ended" << endl;
		return retrieveValue;
	}

	int RetrieveRecurse(Node* searchTargetNode, int retrieiveTargetKey);

	//삭제
	void Remove(int removeTargetKey) {
		if (m_head == NULL) {
			cout << "cannot remove. becuase tree is null." << endl;
			return;
		}
		
		if (m_head->m_key == removeTargetKey) {
			RemoveTarget(m_head);
		}
		else {
			cout << "removing Node.... (key : " << removeTargetKey << " )" << endl;
			RemoveRecurse(m_head, removeTargetKey);
			cout << "removing ended" << endl;
		}
	}

	void RemoveRecurse(Node* searchTargetNode, int removeTargetKey);

	//트리 복사
	void CopyFrom(BST* sourceBST) {		
		if (sourceBST == NULL) {
			cout << "cannot copying. becuase tree is null." << endl;
			return;
		}
		
		if (sourceBST->m_head == NULL) {
			cout << "cannot coping. becuase m_head is null." << endl;
			return;
		}

		cout << "copying tree..." << endl;
		CopyFromRecurse(sourceBST->m_head);
		cout << "copying dended" << endl;
	}

	void CopyFromRecurse(Node* sourceNode) {
		Insert(sourceNode->m_key, sourceNode->m_data);
		if (sourceNode->m_lChild != NULL) CopyFromRecurse(sourceNode->m_lChild);
		if (sourceNode->m_rChild != NULL) CopyFromRecurse(sourceNode->m_rChild);
	}

	//트리 삭제
	void RemoveAll() {
		delete m_head;
		m_head = NULL;
	}

	//전위 순회
	void PreorderPrint() {
		if (m_head == NULL) {
			cout << "cannot traverse print. becuase m_head is null." << endl;
			return;
		}

		cout << "preorder traverse..." << endl;
		PreorderPrintRecurse(m_head);
		cout << "traverse ended" << endl;
	}

	void PreorderPrintRecurse(Node* targetNode) {
		cout << "node m_key : " << targetNode->m_key << " / node m_data : " << targetNode->m_data << endl;
		if (targetNode->m_lChild != NULL) PreorderPrintRecurse(targetNode->m_lChild);
		if (targetNode->m_rChild != NULL) PreorderPrintRecurse(targetNode->m_rChild);
	}

	//중위 순회
	void InorderPrint() {
		if (m_head == NULL) {
			cout << "cannot traverse print. becuase m_head is null." << endl;
			return;
		}

		cout << "inorder traverse..." << endl;
		InorderPrintRecurse(m_head);
		cout << "traverse ended" << endl;
	}

	void InorderPrintRecurse(Node* targetNode) {
		if (targetNode->m_lChild != NULL) InorderPrintRecurse(targetNode->m_lChild);
		cout << "node m_key : " << targetNode->m_key << " / node m_data : " << targetNode->m_data << endl;
		if (targetNode->m_rChild != NULL) InorderPrintRecurse(targetNode->m_rChild);
	}

	//후위 순회
	void PostOrderPrint() {
		if (m_head == NULL) {
			cout << "cannot traverse print. becuase m_head is null." << endl;
			return;
		}

		cout << "postorder traverse..." << endl;
		PostOrderPrintRecurse(m_head);
		cout << "traverse ended" << endl;
	}

	void PostOrderPrintRecurse(Node* targetNode) {
		if (targetNode->m_lChild != NULL) PostOrderPrintRecurse(targetNode->m_lChild);
		if (targetNode->m_rChild != NULL) PostOrderPrintRecurse(targetNode->m_rChild);
		cout << "node m_key : " << targetNode->m_key << " / node m_data : " << targetNode->m_data << endl;
	}

};

#endif //BST_USING_RECURSE_H