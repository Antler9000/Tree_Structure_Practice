#include "BST_using_recurse.h"	//(essential) 본 단원에서 재귀를 이용해 구현한 BST을 호출해서 시험함
#include <iostream>			//(non-essential) 테스트 수행 출력문을 위해 사용함
#include <string>				//(non-essential) BST<string> 테스트를 위해 사용함

int main()
{
	cout << "testing 1 : BST<int>--------------------------------------------------------------------------" << endl;

	cout << endl << "선언" << endl;
	BST<int> int_test_BST;
	
	cout << endl << "삽입" << endl;
	int_test_BST.Insert(5, 1515);
	int_test_BST.Insert(7, 2727);
	int_test_BST.Insert(3, 1313);
	int_test_BST.Insert(4, 2424);
	int_test_BST.Insert(6, 3636);
	int_test_BST.PreorderPrint();

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<int> int_copy_test_BST;
	int_copy_test_BST.CopyFrom(int_test_BST);
	int_copy_test_BST.PreorderPrint();
	int_copy_test_BST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	int_test_BST.Remove(7);
	int_test_BST.PreorderPrint();

	int_test_BST.Remove(5);
	int_test_BST.PreorderPrint();

	int_test_BST.Remove(6);
	int_test_BST.PreorderPrint();

	int_test_BST.Remove(4);
	int_test_BST.PreorderPrint();

	int_test_BST.Remove(3);
	int_test_BST.PreorderPrint();

	cout << "testing 2 : BST<float>--------------------------------------------------------------------------" << endl;

	cout << endl << "선언" << endl;
	BST<float> float_test_BST;
	
	cout << endl << "삽입" << endl;
	float_test_BST.Insert(5, 1.515);
	float_test_BST.Insert(7, 2.727);
	float_test_BST.Insert(3, 1.313);
	float_test_BST.Insert(4, 2.424);
	float_test_BST.Insert(6, 3.636);
	float_test_BST.PreorderPrint();

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<float> float_copy_test_BST;
	float_copy_test_BST.CopyFrom(float_test_BST);
	float_copy_test_BST.PreorderPrint();
	float_copy_test_BST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	float_test_BST.Remove(7);
	float_test_BST.PreorderPrint();

	float_test_BST.Remove(5);
	float_test_BST.PreorderPrint();

	float_test_BST.Remove(6);
	float_test_BST.PreorderPrint();

	float_test_BST.Remove(4);
	float_test_BST.PreorderPrint();

	float_test_BST.Remove(3);
	float_test_BST.PreorderPrint();

	cout << "testing 3 : BST<string>--------------------------------------------------------------------------" << endl;

	cout << endl << "선언" << endl;
	BST<string> string_test_BST;
	
	cout << endl << "삽입" << endl;
	string_test_BST.Insert(5, "Panther");
	string_test_BST.Insert(7, "Sherman");
	string_test_BST.Insert(3, "Crusader");
	string_test_BST.Insert(4, "Comet");
	string_test_BST.Insert(6, "Tiger");
	string_test_BST.PreorderPrint();

	cout << endl << "복사 및 전체 삭제" << endl;
	BST<string> string_copy_test_BST;
	string_copy_test_BST.CopyFrom(string_test_BST);
	string_copy_test_BST.PreorderPrint();
	string_copy_test_BST.RemoveAll();

	cout << endl << "요소별 삭제" << endl;
	string_test_BST.Remove(7);
	string_test_BST.PreorderPrint();

	string_test_BST.Remove(5);
	string_test_BST.PreorderPrint();

	string_test_BST.Remove(6);
	string_test_BST.PreorderPrint();

	string_test_BST.Remove(4);
	string_test_BST.PreorderPrint();

	string_test_BST.Remove(3);
	string_test_BST.PreorderPrint();

	return 0;
}