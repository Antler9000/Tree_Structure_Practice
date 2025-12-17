#include "splay_tree.h"

int main()
{
	SplayTree& testTree = *(new SplayTree());

	testTree.Insert(5, 1515);
	testTree.Insert(7, 2727);
	testTree.Insert(3, 1313);
	testTree.Insert(4, 2424);
	testTree.Insert(6, 3636);
	testTree.Insert(1, 5151);
	testTree.Insert(8, 5858);
	testTree.PreorderPrint();

	cout << "Retrieve test 8" << endl;
	testTree.Retrieve(8);
	testTree.PreorderPrint();

	cout << "Retrieve test 4" << endl;
	testTree.Retrieve(4);
	testTree.PreorderPrint();

	cout << "Retrieve test 3" << endl;
	testTree.Retrieve(3);
	testTree.PreorderPrint();

	cout << "Retrieve test 3" << endl;
	testTree.Retrieve(3);
	testTree.PreorderPrint();

	cout << "Retrieve test 7" << endl;
	testTree.Retrieve(7);
	testTree.PreorderPrint();

	cout << "Retrieve test 5" << endl;
	testTree.Retrieve(5);
	testTree.PreorderPrint();


	SplayTree& copied_test_tree = *(new SplayTree());
	copied_test_tree.CopyFrom(&testTree);
	copied_test_tree.PreorderPrint();

	testTree.Remove(7);
	testTree.PreorderPrint();

	testTree.Remove(3);
	testTree.PreorderPrint();

	testTree.Remove(5);
	testTree.PreorderPrint();

	testTree.Remove(4);
	testTree.PreorderPrint();

	testTree.Remove(6);
	testTree.PreorderPrint();

	testTree.Remove(1);
	testTree.PreorderPrint();

	testTree.Remove(8);
	testTree.PreorderPrint();

	delete& testTree;
	return 0;
}