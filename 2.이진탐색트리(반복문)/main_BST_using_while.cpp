#include "BST_using_while.h"

int main()
{
	BST& testBST = *(new BST());
	testBST.Insert(5, 1515);
	testBST.Insert(7, 2727);
	testBST.Insert(3, 1313);
	testBST.Insert(4, 2424);
	testBST.Insert(6, 3636);
	testBST.Insert(1, 5151);
	testBST.Insert(8, 5858);
	testBST.PreorderPrint();

	cout << "copy test" << endl;
	BST& copied_test_BST = *(new BST());
	copied_test_BST.CopyFrom(&testBST);
	copied_test_BST.PreorderPrint();

	testBST.Remove(7);
	testBST.PreorderPrint();

	testBST.Remove(3);
	testBST.PreorderPrint();

	testBST.Remove(5);
	testBST.PreorderPrint();

	testBST.Remove(4);
	testBST.PreorderPrint();

	testBST.Remove(6);
	testBST.PreorderPrint();

	testBST.Remove(1);
	testBST.PreorderPrint();

	testBST.Remove(8);
	testBST.PreorderPrint();

	cout << "copy test" << endl;
	copied_test_BST.PreorderPrint();

	delete& testBST;
	delete& copied_test_BST;

	return 0;
}