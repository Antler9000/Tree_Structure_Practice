#include "BST_using_recurse.h"

int main()
{
	BST<int> testBST;
	testBST.Insert(5, 1515);
	testBST.Insert(7, 2727);
	testBST.Insert(3, 1313);
	testBST.Insert(4, 2424);
	testBST.Insert(6, 3636);
	testBST.PreorderPrint();

	BST<int> copied_BST;
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


	BST<float> testBST2;
	testBST2.Insert(5, 1.515);
	testBST2.Insert(7, 2.727);
	testBST2.Insert(3, 1.313);
	testBST2.Insert(4, 2.424);
	testBST2.Insert(6, 3.636);
	testBST2.PreorderPrint();

	return 0;
}