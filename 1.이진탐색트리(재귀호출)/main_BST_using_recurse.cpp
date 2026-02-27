#define TREE_LOG				//로그 콘솔 출력문들을 활성화함
#define TREE_ERROR				//에러 콘솔 출력문들을 활성화함
#define TREE_WARNING			//경고 콘솔 출력문들을 활성화함

#include "BST_using_recurse.h"	//본 단원에서 재귀를 이용해 구현한 BST을 호출해서 시험함

template <typename DataType>
inline void RetrieveResultPrint(const int key, const DataType retrievedData)
{
	cout << "retrieve key : " << key << ", retrieved data : " << retrievedData << endl;
}

int main()
{
	cout << endl << "testing 1 : BST<int>--------------------------------------------------------------------------" << endl;

	BST<int> intTestBST;
	
	cout << endl << "삽입" << endl;
	intTestBST.Insert(5, 1515);
	intTestBST.Insert(7, 2727);
	intTestBST.Insert(3, 1313);
	intTestBST.Insert(4, 2424);
	intTestBST.Insert(6, 3636);
	intTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	int intRetrievedData = 0;
	intTestBST.Retrieve(3, intRetrievedData);
	RetrieveResultPrint(3, intRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<int> intExplicitCopyTestBST;
	intExplicitCopyTestBST.CopyTree(intTestBST);
	intExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<int> intCopyConstructorTestBST = intTestBST;
	intCopyConstructorTestBST.PreorderPrint();
	
	cout << endl << "복사 할당 연산자" << endl;
	BST<int> intCopyAssignmentTestBST;
	intCopyAssignmentTestBST = intTestBST;
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<int> intMoveConstructorTestBST = move(intCopyConstructorTestBST);
	intMoveConstructorTestBST.PreorderPrint();
	intCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<int> intMoveAssignmentTestBST;
	intMoveAssignmentTestBST = move(intCopyAssignmentTestBST);
	intMoveAssignmentTestBST.PreorderPrint();
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	intTestBST.Remove(7);
	intTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	intTestBST.RemoveTree();
	intTestBST.PreorderPrint();

	cout << endl << "testing 2 : BST<float>--------------------------------------------------------------------------" << endl;

	BST<float> floatTestBST;
	
	cout << endl << "삽입" << endl;
	floatTestBST.Insert(5, 1.515f);
	floatTestBST.Insert(7, 2.727f);
	floatTestBST.Insert(3, 1.313f);
	floatTestBST.Insert(4, 2.424f);
	floatTestBST.Insert(6, 3.636f);
	floatTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	float floatRetrievedData = 0;
	floatTestBST.Retrieve(3, floatRetrievedData);
	RetrieveResultPrint(3, floatRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<float> floatExplicitCopyTestBST;
	floatExplicitCopyTestBST.CopyTree(floatTestBST);
	floatExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<float> floatCopyConstructorTestBST = floatTestBST;
	floatCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자" << endl;
	BST<float> floatCopyAssignmentTestBST;
	floatCopyAssignmentTestBST = floatTestBST;
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<float> floatMoveConstructorTestBST = move(floatCopyConstructorTestBST);
	floatMoveConstructorTestBST.PreorderPrint();
	floatCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<float> floatMoveAssignmentTestBST;
	floatMoveAssignmentTestBST = move(floatCopyAssignmentTestBST);
	floatMoveAssignmentTestBST.PreorderPrint();
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	floatTestBST.Remove(7);
	floatTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	floatTestBST.RemoveTree();
	floatTestBST.PreorderPrint();

	cout << endl << "testing 3 : BST<string>--------------------------------------------------------------------------" << endl;

	BST<string> stringTestBST;
	
	cout << endl << "삽입" << endl;
	stringTestBST.Insert(5, "Panther");
	stringTestBST.Insert(7, "Sherman");
	stringTestBST.Insert(3, "Crusader");
	stringTestBST.Insert(4, "Comet");
	stringTestBST.Insert(6, "Tiger");
	stringTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	string stringRetrievedData = "";
	stringTestBST.Retrieve(3, stringRetrievedData);
	RetrieveResultPrint(3, stringRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<string> stringExplicitCopyTestBST;
	stringExplicitCopyTestBST.CopyTree(stringTestBST);
	stringExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<string> stringCopyConstructorTestBST = stringTestBST;
	stringCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자" << endl;
	BST<string> stringCopyAssignmentTestBST;
	stringCopyAssignmentTestBST = stringTestBST;
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<string> stringMoveConstructorTestBST = move(stringCopyConstructorTestBST);
	stringMoveConstructorTestBST.PreorderPrint();
	stringCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<string> stringMoveAssignmentTestBST;
	stringMoveAssignmentTestBST = move(stringCopyAssignmentTestBST);
	stringMoveAssignmentTestBST.PreorderPrint();
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	stringTestBST.Remove(7);
	stringTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	stringTestBST.RemoveTree();
	stringTestBST.PreorderPrint();

	return 0;
}