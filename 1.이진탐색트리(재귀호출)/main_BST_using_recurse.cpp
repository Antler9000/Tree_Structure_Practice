#include "BST_using_recurse.h"	//본 단원에서 재귀를 이용해 구현한 BST을 호출해서 시험함

template <typename DataType>
inline void RetrieveResultPrint(int key, DataType retrievedData)
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
	int intRetrievedData1 = 0;
	intTestBST.Retrieve(5, intRetrievedData1);
	RetrieveResultPrint(5, intRetrievedData1);

	int intRetrievedData2 = 0;
	intTestBST.Retrieve(3, intRetrievedData2);
	RetrieveResultPrint(3, intRetrievedData2);
	
	cout << endl << "복사 및 전체 삭제" << endl;
	BST<int> intCopyTestBST;
	intCopyTestBST.CopyTree(intTestBST);
	intCopyTestBST.PreorderPrint();
	intCopyTestBST.RemoveTree();

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
	float floatRetrievedData1 = 0;
	floatTestBST.Retrieve(5, floatRetrievedData1);
	RetrieveResultPrint(5, floatRetrievedData1);

	float floatRetrievedData2 = 0;
	floatTestBST.Retrieve(3, floatRetrievedData2);
	RetrieveResultPrint(3, floatRetrievedData2);

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<float> floatCopyTestBST;
	floatCopyTestBST.CopyTree(floatTestBST);
	floatCopyTestBST.PreorderPrint();
	floatCopyTestBST.RemoveTree();

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
	string stringRetrievedData1 = "";
	stringTestBST.Retrieve(5, stringRetrievedData1);
	RetrieveResultPrint(5, stringRetrievedData1);

	string stringRetrievedData2 = "";
	stringTestBST.Retrieve(3, stringRetrievedData2);
	RetrieveResultPrint(3, stringRetrievedData2);

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<string> stringCopyTestBST;
	stringCopyTestBST.CopyTree(stringTestBST);
	stringCopyTestBST.PreorderPrint();
	stringCopyTestBST.RemoveTree();

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