#include "AVL_tree.h"

int main() {
	AVL_tree& test_tree = *(new AVL_tree());
	test_tree.Insert(5, 55);
	test_tree.Insert(9, 99);
	test_tree.Insert(8, 88);
	test_tree.Insert(7, 77);
	test_tree.Insert(1, 11);
	test_tree.Insert(2, 22);
	test_tree.Insert(3, 33);
	test_tree.PreorderPrint();

	AVL_tree& copied_test_tree = *(new AVL_tree());
	copied_test_tree.CopyFrom(&test_tree);
	copied_test_tree.PreorderPrint();

	test_tree.Remove(1);
	test_tree.PreorderPrint();

	test_tree.Remove(2);
	test_tree.PreorderPrint();

	test_tree.Remove(3);
	test_tree.PreorderPrint();

	test_tree.Remove(5);
	test_tree.PreorderPrint();

	test_tree.Remove(7);
	test_tree.PreorderPrint();

	test_tree.Remove(8);
	test_tree.PreorderPrint();

	test_tree.Remove(9);
	test_tree.PreorderPrint();

	delete& test_tree;
	return 0;
}