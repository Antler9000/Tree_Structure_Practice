#include "BST_using_recurse.h"	//(yes-essential) 본 단원에서 재귀를 이용해 구현한 BST
#include "string.h"			//(non-essential) 트리에 담길 데이터의 타입으로 string이 가능한지 테스팅 용도

int main()
{
	cout << "testing 1 : BST<int>--------------------------------------------------------------------------" << endl;
	//선언
	BST<int> int_test_BST;
	
	//삽입
	cout << endl;
	int_test_BST.Insert(5, 1515);
	int_test_BST.Insert(7, 2727);
	int_test_BST.Insert(3, 1313);
	int_test_BST.Insert(4, 2424);
	int_test_BST.Insert(6, 3636);
	int_test_BST.PreorderPrint();

	//복사 및 전체 삭제
	cout << endl;
	BST<int> int_copy_test_BST;
	int_copy_test_BST.CopyFrom(int_test_BST);
	int_copy_test_BST.PreorderPrint();
	int_copy_test_BST.RemoveAll();

	//요소별 삭제
	cout << endl;
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
	//선언
	BST<float> float_test_BST;
	
	//삽입
	cout << endl;
	float_test_BST.Insert(5, 1.515);
	float_test_BST.Insert(7, 2.727);
	float_test_BST.Insert(3, 1.313);
	float_test_BST.Insert(4, 2.424);
	float_test_BST.Insert(6, 3.636);
	float_test_BST.PreorderPrint();

	//복사 및 전체 삭제
	cout << endl;
	BST<float> float_copy_test_BST;
	float_copy_test_BST.CopyFrom(float_test_BST);
	float_copy_test_BST.PreorderPrint();
	float_copy_test_BST.RemoveAll();

	//요소별 삭제
	cout << endl;
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
	//선언
	BST<string> string_test_BST;
	
	//삽입
	cout << endl;
	string_test_BST.Insert(5, "Panther");
	string_test_BST.Insert(7, "Sherman");
	string_test_BST.Insert(3, "Crusader");
	string_test_BST.Insert(4, "Comet");
	string_test_BST.Insert(6, "Tiger");
	string_test_BST.PreorderPrint();

	//복사 및 전체 삭제
	cout << endl;
	BST<string> string_copy_test_BST;
	string_copy_test_BST.CopyFrom(string_test_BST);
	string_copy_test_BST.PreorderPrint();
	string_copy_test_BST.RemoveAll();

	//요소별 삭제
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