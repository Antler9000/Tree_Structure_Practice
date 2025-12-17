#include "AVL_tree.h"

int main()
{
	AVL_tree& testTree = *(new AVL_tree());

	testTree.Insert(5, 55);
	testTree.Insert(9, 99);
	testTree.Insert(8, 88);
	testTree.Insert(7, 77);
	testTree.Insert(1, 11);
	testTree.Insert(2, 22);
	testTree.Insert(3, 33);
	testTree.PreorderPrint();

	AVL_tree& copied_test_tree = *(new AVL_tree());

	copied_test_tree.CopyFrom(&testTree);
	copied_test_tree.PreorderPrint();

	testTree.Remove(1);
	testTree.PreorderPrint();

	testTree.Remove(2);
	testTree.PreorderPrint();

	testTree.Remove(3);
	testTree.PreorderPrint();

	testTree.Remove(5);
	testTree.PreorderPrint();

	testTree.Remove(7);
	testTree.PreorderPrint();

	testTree.Remove(8);
	testTree.PreorderPrint();

	testTree.Remove(9);
	testTree.PreorderPrint();

	delete& testTree;

	return 0;
}