#include "BST_using_recurse.h"	//(essential) 본 단원에서 재귀를 이용해 구현한 BST을 호출해서 시험함
#include <iostream>			//(non-essential) 테스트 수행 출력문을 위해 사용함
#include <string>				//(non-essential) BST<string> 테스트를 위해 사용함

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
	intTestBST.Retrieve(5, intRetrievedData);
	cout << "retrieve key : " << 5 << ", retrieved data : " << intRetrievedData << endl;
	intTestBST.Retrieve(3, intRetrievedData);
	cout << "retrieve key : " << 3 << ", retrieved data : " << intRetrievedData << endl;
	
	cout << endl << "복사 및 전체 삭제" << endl;
	BST<int> intCopyTestBST;
	intCopyTestBST.CopyFrom(intTestBST);
	intCopyTestBST.PreorderPrint();
	intCopyTestBST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	intTestBST.Remove(7);
	intTestBST.PreorderPrint();

	intTestBST.Remove(5);
	intTestBST.PreorderPrint();

	intTestBST.Remove(6);
	intTestBST.PreorderPrint();

	intTestBST.Remove(4);
	intTestBST.PreorderPrint();

	intTestBST.Remove(3);
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
	floatTestBST.Retrieve(5, floatRetrievedData);
	cout << "retrieve key : " << 5 << ", retrieved data : " << floatRetrievedData << endl;
	floatTestBST.Retrieve(3, floatRetrievedData);
	cout << "retrieve key : " << 3 << ", retrieved data : " << floatRetrievedData << endl;

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<float> floatCopyTestBST;
	floatCopyTestBST.CopyFrom(floatTestBST);
	floatCopyTestBST.PreorderPrint();
	floatCopyTestBST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	floatTestBST.Remove(7);
	floatTestBST.PreorderPrint();

	floatTestBST.Remove(5);
	floatTestBST.PreorderPrint();

	floatTestBST.Remove(6);
	floatTestBST.PreorderPrint();

	floatTestBST.Remove(4);
	floatTestBST.PreorderPrint();

	floatTestBST.Remove(3);
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
	stringTestBST.Retrieve(5, stringRetrievedData);
	cout << "retrieve key : " << 5 << ", retrieved data : " << stringRetrievedData << endl;
	stringTestBST.Retrieve(3, stringRetrievedData);
	cout << "retrieve key : " << 3 << ", retrieved data : " << stringRetrievedData << endl;

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<string> stringCopyTestBST;
	stringCopyTestBST.CopyFrom(stringTestBST);
	stringCopyTestBST.PreorderPrint();
	stringCopyTestBST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	stringTestBST.Remove(7);
	stringTestBST.PreorderPrint();

	stringTestBST.Remove(5);
	stringTestBST.PreorderPrint();

	stringTestBST.Remove(6);
	stringTestBST.PreorderPrint();

	stringTestBST.Remove(4);
	stringTestBST.PreorderPrint();

	stringTestBST.Remove(3);
	stringTestBST.PreorderPrint();

	return 0;
}