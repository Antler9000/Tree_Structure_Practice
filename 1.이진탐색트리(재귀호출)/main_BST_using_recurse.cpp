#include "BST_using_recurse.h"

int main() {
	BST test_BST;
	test_BST.Insert(5, 1515);
	test_BST.Insert(7, 2727);
	test_BST.Insert(3, 1313);
	test_BST.Insert(4, 2424);
	test_BST.Insert(6, 3636);
	test_BST.PreorderPrint();

	BST copied_BST;
	copied_BST.CopyFrom(&test_BST);
	copied_BST.PreorderPrint();

	test_BST.Remove(7);
	test_BST.PreorderPrint();

	test_BST.Remove(5);
	test_BST.PreorderPrint();

	test_BST.Remove(6);
	test_BST.PreorderPrint();

	test_BST.Remove(4);
	test_BST.PreorderPrint();

	test_BST.Remove(3);
	test_BST.PreorderPrint();

	test_BST.RemoveAll();
	test_BST.PreorderPrint();

	return 0;
}