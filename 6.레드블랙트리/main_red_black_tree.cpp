#include "red_black_tree.h"

int main() {
	RedBlackTree& testTree = *(new RedBlackTree());
	testTree.Insert(5, 55);
	testTree.Insert(9, 99);
	testTree.Insert(8, 88);
	testTree.Insert(6, 66);
	testTree.Insert(7, 77);
	testTree.Insert(1, 11);
	testTree.Insert(2, 22);
	testTree.Insert(3, 33);
	testTree.Insert(4, 44);
	testTree.PreorderPrint();

	RedBlackTree& copiedTestTree = *(new RedBlackTree());
	copiedTestTree.CopyFrom(&testTree);
	copiedTestTree.PreorderPrint();

	testTree.Remove(1);
	testTree.PreorderPrint();

	testTree.Remove(2);
	testTree.PreorderPrint();

	testTree.Remove(3);
	testTree.PreorderPrint();

	testTree.Remove(4);
	testTree.PreorderPrint();

	testTree.Remove(5);
	testTree.PreorderPrint();

	testTree.Remove(6);
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