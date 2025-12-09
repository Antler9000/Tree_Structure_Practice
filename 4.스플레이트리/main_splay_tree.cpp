#include "splay_tree.h"

int main() {
	SplayTree& test_tree = *(new SplayTree());
	test_tree.Insert(5, 1515);
	test_tree.Insert(7, 2727);
	test_tree.Insert(3, 1313);
	test_tree.Insert(4, 2424);
	test_tree.Insert(6, 3636);
	test_tree.Insert(1, 5151);
	test_tree.Insert(8, 5858);
	test_tree.PreorderPrint();

	cout << "Retrieve test 8" << endl;
	test_tree.Retrieve(8);
	test_tree.PreorderPrint();

	cout << "Retrieve test 4" << endl;
	test_tree.Retrieve(4);
	test_tree.PreorderPrint();

	cout << "Retrieve test 3" << endl;
	test_tree.Retrieve(3);
	test_tree.PreorderPrint();

	cout << "Retrieve test 3" << endl;
	test_tree.Retrieve(3);
	test_tree.PreorderPrint();

	cout << "Retrieve test 7" << endl;
	test_tree.Retrieve(7);
	test_tree.PreorderPrint();

	cout << "Retrieve test 5" << endl;
	test_tree.Retrieve(5);
	test_tree.PreorderPrint();


	SplayTree& copied_test_tree = *(new SplayTree());
	copied_test_tree.CopyFrom(&test_tree);
	copied_test_tree.PreorderPrint();

	test_tree.Remove(7);
	test_tree.PreorderPrint();

	test_tree.Remove(3);
	test_tree.PreorderPrint();

	test_tree.Remove(5);
	test_tree.PreorderPrint();

	test_tree.Remove(4);
	test_tree.PreorderPrint();

	test_tree.Remove(6);
	test_tree.PreorderPrint();

	test_tree.Remove(1);
	test_tree.PreorderPrint();

	test_tree.Remove(8);
	test_tree.PreorderPrint();

	delete& test_tree;
	return 0;
}