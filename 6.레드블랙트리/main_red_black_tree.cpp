#include "red_black_tree.h"

int main()
{
	cout << "----------------------------------1st tree insert-----------------------------" << endl;
	RedBlackTree testTree1 = RedBlackTree();
	
	testTree1.Insert(5, 55);
	testTree1.PreorderPrint();

	testTree1.Insert(9, 99);
	testTree1.PreorderPrint();

	testTree1.Insert(8, 88);
	testTree1.PreorderPrint();

	testTree1.Insert(6, 66);
	testTree1.PreorderPrint();

	testTree1.Insert(7, 77);
	testTree1.PreorderPrint();

	testTree1.Insert(1, 11);
	testTree1.PreorderPrint();
	
	testTree1.Insert(2, 22);
	testTree1.PreorderPrint();

	testTree1.Insert(3, 33);
	testTree1.PreorderPrint();
	
	testTree1.Insert(4, 44);
	testTree1.PreorderPrint();

	cout << "do copy!" << endl;
	RedBlackTree copyTestTree = RedBlackTree();
	copyTestTree.CopyFrom(&testTree1);
	copyTestTree.PreorderPrint();

	cout << "----------------------------------1st tree remove-----------------------------" << endl;
	testTree1.Remove(1);
	testTree1.PreorderPrint();

	testTree1.Remove(2);
	testTree1.PreorderPrint();

	testTree1.Remove(3);
	testTree1.PreorderPrint();

	testTree1.Remove(4);
	testTree1.PreorderPrint();

	testTree1.Remove(5);
	testTree1.PreorderPrint();

	testTree1.Remove(6);
	testTree1.PreorderPrint();

	testTree1.Remove(7);
	testTree1.PreorderPrint();

	testTree1.Remove(8);
	testTree1.PreorderPrint();

	testTree1.Remove(9);
	testTree1.PreorderPrint();

	cout << "----------------------------------2nd tree insert-----------------------------" << endl;
	RedBlackTree testTree2 = RedBlackTree();

	testTree2.Insert(1, 11);
	testTree2.PreorderPrint();

	testTree2.Insert(2, 22);
	testTree2.PreorderPrint();

	testTree2.Insert(3, 33);
	testTree2.PreorderPrint();

	testTree2.Insert(4, 44);
	testTree2.PreorderPrint();
	
	testTree2.Insert(5, 55);
	testTree2.PreorderPrint();
	
	testTree2.Insert(6, 66);
	testTree2.PreorderPrint();

	testTree2.Insert(7, 77);
	testTree2.PreorderPrint();

	cout << "----------------------------------2nd tree remove-----------------------------" << endl;
	testTree2.Remove(1);
	testTree2.PreorderPrint();

	testTree2.Remove(2);
	testTree2.PreorderPrint();

	testTree2.Remove(3);
	testTree2.PreorderPrint();

	testTree2.Remove(4);
	testTree2.PreorderPrint();

	testTree2.Remove(5);
	testTree2.PreorderPrint();

	testTree2.Remove(6);
	testTree2.PreorderPrint();

	testTree2.Remove(7);
	testTree2.PreorderPrint();


	cout << "----------------------------------3rd tree insert-----------------------------" << endl;
	RedBlackTree testTree3 = RedBlackTree();

	testTree3.Insert(7, 77);
	testTree3.PreorderPrint();

	testTree3.Insert(6, 66);
	testTree3.PreorderPrint();

	testTree3.Insert(5, 55);
	testTree3.PreorderPrint();

	testTree3.Insert(4, 44);
	testTree3.PreorderPrint();

	testTree3.Insert(3, 33);
	testTree3.PreorderPrint();

	testTree3.Insert(2, 22);
	testTree3.PreorderPrint();

	testTree3.Insert(1, 11);
	testTree3.PreorderPrint();

	cout << "----------------------------------3rd tree remove-----------------------------" << endl;
	testTree3.Remove(7);
	testTree3.PreorderPrint();

	testTree3.Remove(6);
	testTree3.PreorderPrint();

	testTree3.Remove(5);
	testTree3.PreorderPrint();

	testTree3.Remove(4);
	testTree3.PreorderPrint();

	testTree3.Remove(3);
	testTree3.PreorderPrint();

	testTree3.Remove(2);
	testTree3.PreorderPrint();

	testTree3.Remove(1);
	testTree3.PreorderPrint();

	cout << "----------------------------------4th tree insert-----------------------------" << endl;
	RedBlackTree testTree4 = RedBlackTree();

	testTree4.Insert(1, 11);
	testTree4.PreorderPrint();

	testTree4.Insert(7, 77);
	testTree4.PreorderPrint();

	testTree4.Insert(2, 22);
	testTree4.PreorderPrint();

	testTree4.Insert(6, 66);
	testTree4.PreorderPrint();

	testTree4.Insert(3, 33);
	testTree4.PreorderPrint();

	testTree4.Insert(5, 55);
	testTree4.PreorderPrint();

	testTree4.Insert(4, 44);
	testTree4.PreorderPrint();

	cout << "----------------------------------3rd tree remove-----------------------------" << endl;
	testTree4.Remove(1);
	testTree4.PreorderPrint();

	testTree4.Remove(7);
	testTree4.PreorderPrint();

	testTree4.Remove(2);
	testTree4.PreorderPrint();

	testTree4.Remove(6);
	testTree4.PreorderPrint();

	testTree4.Remove(3);
	testTree4.PreorderPrint();

	testTree4.Remove(5);
	testTree4.PreorderPrint();

	testTree4.Remove(4);
	testTree4.PreorderPrint();

	return 0;
}