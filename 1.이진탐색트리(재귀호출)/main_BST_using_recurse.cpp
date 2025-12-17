#include "BST_using_recurse.h"

int main()
{
	BST testBST;
	testBST.Insert(5, 1515);
	testBST.Insert(7, 2727);
	testBST.Insert(3, 1313);
	testBST.Insert(4, 2424);
	testBST.Insert(6, 3636);
	testBST.PreorderPrint();

	BST copied_BST;
	copied_BST.CopyFrom(&testBST);
	copied_BST.PreorderPrint();

	testBST.Remove(7);
	testBST.PreorderPrint();

	testBST.Remove(5);
	testBST.PreorderPrint();

	testBST.Remove(6);
	testBST.PreorderPrint();

	testBST.Remove(4);
	testBST.PreorderPrint();

	testBST.Remove(3);
	testBST.PreorderPrint();

	testBST.RemoveAll();
	testBST.PreorderPrint();

	return 0;
}