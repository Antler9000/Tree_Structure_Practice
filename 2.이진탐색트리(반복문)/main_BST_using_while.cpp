#include "BST_using_while.h"

int main() {
	BST& test_BST = *(new BST());
	test_BST.Insert(5, 1515);
	test_BST.Insert(7, 2727);
	test_BST.Insert(3, 1313);
	test_BST.Insert(4, 2424);
	test_BST.Insert(6, 3636);
	test_BST.Insert(1, 5151);
	test_BST.Insert(8, 5858);
	test_BST.PreorderPrint();

	BST& copied_test_BST = *(new BST());
	copied_test_BST.CopyFrom(&test_BST);
	copied_test_BST.PreorderPrint();

	test_BST.Remove(7);
	test_BST.PreorderPrint();

	test_BST.Remove(3);
	test_BST.PreorderPrint();

	test_BST.Remove(5);
	test_BST.PreorderPrint();

	test_BST.Remove(4);
	test_BST.PreorderPrint();

	test_BST.Remove(6);
	test_BST.PreorderPrint();

	test_BST.Remove(1);
	test_BST.PreorderPrint();

	test_BST.Remove(8);
	test_BST.PreorderPrint();

	delete& test_BST;
	delete& copied_test_BST;
	return 0;
}