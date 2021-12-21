// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>
#include <istream>

using namespace std;

TEST(empty_test0) {
    BinarySearchTree<int> b;
    ASSERT_TRUE(b.empty());
}

TEST(empty_test1) {
    BinarySearchTree<int> b;
    b.insert(2);
    b.insert(1);
    b.insert(3);
    cout << b.to_string() << endl;
    ASSERT_FALSE(b.empty());
}

TEST(size0) {
    BinarySearchTree<int> b;
    ASSERT_TRUE(b.size() == 0);
}

TEST(size1) {
    BinarySearchTree<int> b;
    b.insert(0);
    b.insert(1);
    b.insert(9999);
    cout << b.to_string() << endl;
    ASSERT_EQUAL(b.size(), 3);
}

TEST(size2) {
    BinarySearchTree <int> left;
    BinarySearchTree <int> right;

    left.insert(0);
    left.insert(-1);
    left.insert(-2);
    left.insert(-3);

    right.insert(0);
    right.insert(1);
    right.insert(2);

    ASSERT_EQUAL(left.size(), 4);
    ASSERT_EQUAL(right.size(), 3);
}

TEST(height0) {
    BinarySearchTree<int> b;
    ASSERT_TRUE(b.height() == 0);
    b.insert(3);
    b.insert(5);
    b.insert(7);
    b.insert(9);
    cout << b.to_string() << endl;
    ASSERT_TRUE(b.height() == 4);
}

TEST(height1) {
    BinarySearchTree<int> b;
    b.insert(8);
    b.insert(4);
    b.insert(12);
    b.insert(-1);
    b.insert(6);
    b.insert(10);
    b.insert(14);
    cout << b.to_string() << endl;
    ASSERT_EQUAL(b.height(), 3);
    ASSERT_TRUE(b.check_sorting_invariant());
}

TEST(height2) {
    BinarySearchTree <double> left;
    left.insert(5.0);
    left.insert(4.9);
    left.insert(4.5);
    left.insert(4.0);

    ASSERT_EQUAL(left.height(), 4);
}

TEST(max0) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(-5);
    b.insert(4);
    b.insert(8);
    b.insert(5);
    b.insert(9);
    cout << b.to_string() << endl;
    ASSERT_TRUE(*b.max_element() == 9);
    ASSERT_FALSE(*b.max_element() == 1);
    //BinarySearchTree<int>::Iterator i = b.begin();
    //i++;
    //i++;
    //*i = 99;
    //cout << b.to_string() << endl;
    //ASSERT_TRUE(*b.max_element() == 99);
}

TEST(max1) {
    BinarySearchTree<double> b;
    ASSERT_TRUE(b.max_element() == b.end());
    b.insert(1.1);
    ASSERT_TRUE(*b.max_element() == 1.1);
}

TEST(max2) {
    BinarySearchTree <int> left;
    BinarySearchTree <double> right;
    left.insert(5);
    left.insert(3);
    left.insert(1);

    right.insert(0.0);
    right.insert(10.0);
    right.insert(100.0);

    ASSERT_EQUAL(*left.max_element(), 5);
    ASSERT_EQUAL(*right.max_element(), 100.0);
}

TEST(min0) {
    BinarySearchTree<int> b;
    b.insert(2);
    b.insert(3);
    b.insert(4);
    b.insert(9999);
    b.insert(-9999);
    b.insert(1);
    b.insert(-5);
    b.insert(8);
    b.insert(5);
    b.insert(9);
    ASSERT_TRUE(*b.min_element() == -9999);
    //BinarySearchTree<int>::Iterator i = b.begin();
    //i++;
    //i++;
    //*i = -99999;
    //cout << b.to_string() << endl;
    //ASSERT_TRUE(*b.min_element() == -99999);
}

TEST(min1) {
    BinarySearchTree<double> b;
    ASSERT_TRUE(b.min_element() == b.end());
    b.insert(2.0);
    ASSERT_TRUE(*b.min_element() == 2.0);
}

TEST(min2) {
    BinarySearchTree <int> left;
    BinarySearchTree <double> right;
    left.insert(5);
    left.insert(3);
    left.insert(1);

    right.insert(0.0);
    right.insert(10.0);
    right.insert(100.0);

    ASSERT_EQUAL(*left.min_element(), 1);
    ASSERT_EQUAL(*right.min_element(), 0.0);
}

TEST(find0) {
    BinarySearchTree<int> b;
    b.insert(3);
    b.insert(5);
    b.insert(9);
    b.insert(-2);
    BinarySearchTree<int>::Iterator i = b.find(5);
    BinarySearchTree<int>::Iterator t = b.find(-2);
    BinarySearchTree<int>::Iterator h = b.find(3);
    BinarySearchTree<int>::Iterator k = b.find(9);
    BinarySearchTree<int>::Iterator s = b.find(999);
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(*t == -2);
    ASSERT_TRUE(*h == 3);
    ASSERT_TRUE(*k == 9);
    ASSERT_TRUE(s == b.end());
    *i = 4;
    ASSERT_TRUE(b.find(5) == b.end());
}

TEST(find1) {
    BinarySearchTree<int> b;
    BinarySearchTree<int>::Iterator i = b.find(5);
    ASSERT_TRUE(i == b.end());
}

TEST(find2) {
    BinarySearchTree <int> left;
    BinarySearchTree <double> right;
    left.insert(5);
    left.insert(3);
    left.insert(1);

    right.insert(0.0);
    right.insert(10.0);
    right.insert(100.0);

    BinarySearchTree<int>::Iterator in_left = left.find(3);
    BinarySearchTree<int>::Iterator not_in_left = left.find(10);
    BinarySearchTree<double>::Iterator in_right = right.find(10.0);
    BinarySearchTree<double>::Iterator not_in_right = right.find(50.0);

    ASSERT_EQUAL(*in_left, 3);
    ASSERT_EQUAL(*in_right, 10.0);
    ASSERT_EQUAL(not_in_left, left.end());
    ASSERT_EQUAL(not_in_right, right.end());
}

TEST(copy0) {
    BinarySearchTree<int> b0;
    BinarySearchTree<int> b1;
    ASSERT_EQUAL(b0.size(), b1.size());

    b0.insert(3);
    b0.insert(1);
    b0.insert(5);
    b1 = b0;
    ASSERT_TRUE(b1.check_sorting_invariant());
    ASSERT_TRUE(b1.size() == 3);
    ASSERT_TRUE(b1.height() == 2);
    ASSERT_TRUE(!b1.empty());
    ASSERT_TRUE(*b1.find(1) == *b0.find(1));
    b1.insert(2);
    cout << b1.to_string() << endl;
    cout << b0.to_string() << endl;
    ASSERT_TRUE(*b1.min_greater_than(0) == *b0.min_greater_than(0));
    ASSERT_TRUE(b1.min_greater_than(1) != b0.min_greater_than(1));

}

TEST(copy1) {
    BinarySearchTree<int> b0;
    BinarySearchTree<int> b1;
    ASSERT_EQUAL(b0.size(), b1.size());
    b1 = b0;
    ASSERT_TRUE(b1.check_sorting_invariant());
    ASSERT_TRUE(b1.size() == 0);
    ASSERT_TRUE(b1.height() == 0);
    ASSERT_TRUE(b1.empty());
    b1.insert(0);
    b1.insert(1);
    ASSERT_TRUE(b1.min_greater_than(1) == b0.min_greater_than(0));
    ASSERT_TRUE(b1.min_greater_than(0) != b1.end());
}

TEST(sort0) {
    BinarySearchTree<int> b;
    b.insert(3);
    b.insert(5);
    b.insert(9);
    b.insert(-2);
    ASSERT_TRUE(b.check_sorting_invariant());
    *b.begin() = 9999;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(sort1) {
    BinarySearchTree<double> b;
    ASSERT_TRUE(b.check_sorting_invariant());
}

// tree grows in one side only
TEST(sort2) {
    BinarySearchTree <int> left;
    BinarySearchTree <double> right;
    left.insert(5);
    left.insert(3);
    left.insert(1);

    right.insert(0.0);
    right.insert(10.0);
    right.insert(100.0);

    BinarySearchTree<int>::Iterator i = left.find(3);
    *i = 6;
    ASSERT_FALSE(left.check_sorting_invariant());

    BinarySearchTree<double>::Iterator j = right.find(10.0);
    *j = 20.0;
    ASSERT_TRUE(right.check_sorting_invariant());
}

// modify leaf node value
TEST(sort3) {
    BinarySearchTree <int> b;
    b.insert(7);
    b.insert(4);
    b.insert(2);
    b.insert(6);
    b.insert(10);
    b.insert(8);
    b.insert(12);

    BinarySearchTree <int>::Iterator i = b.find(2);
    *i = 0;
    ASSERT_TRUE(b.check_sorting_invariant());

    BinarySearchTree<int>::Iterator j = b.find(12);
    *j = 9;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(preorder0) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(7);
    b.insert(3);
    ostringstream oss_preorder;
    b.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");
}

TEST(preorder1) {
    BinarySearchTree<int> b;
    ostringstream oss_preorder;
    b.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "");
}

TEST(preorder2) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(2);
    b.insert(1);
    b.insert(3);
    b.insert(7);
    b.insert(6);
    b.insert(8);

    ostringstream oss_preorder;
    b.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 2 1 3 7 6 8 ");
}

TEST(inorder0) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(7);
    b.insert(3);
    ostringstream oss_inorder;
    b.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(inorder1) {
    BinarySearchTree<int> b;
    ostringstream oss_inorder;
    b.traverse_preorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "");
}

TEST(inorder2) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(2);
    b.insert(1);
    b.insert(3);
    b.insert(7);
    b.insert(6);
    b.insert(8);

    ostringstream oss_inorder;
    b.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 5 6 7 8 ");
}

TEST(min_greater0) {
    BinarySearchTree<int> b;
    BinarySearchTree<int>::Iterator i0 = b.min_greater_than(5);
    ASSERT_TRUE(i0 == b.end());
    b.insert(5);
    BinarySearchTree<int>::Iterator i1 = b.min_greater_than(5);
    ASSERT_TRUE(i1 == b.end());
    b.insert(3);
    b.insert(7);
    BinarySearchTree<int>::Iterator i2 = b.min_greater_than(5);
    ASSERT_TRUE(*i2 == 7);
    b.insert(0);
    b.insert(99);
    BinarySearchTree<int>::Iterator i3 = b.min_greater_than(5);
    ASSERT_TRUE(*i3 == 7);
}

TEST(min_greater1) {
    BinarySearchTree<int> b;
    BinarySearchTree<int>::Iterator i0 = b.min_greater_than(5);
    ASSERT_TRUE(i0 == b.end());
}

TEST(min_greater2) {
    BinarySearchTree<int> b;
    b.insert(9);
    b.insert(6);
    b.insert(12);
    b.insert(17);
    b.insert(10);
    b.insert(11);
    b.insert(15);
    b.insert(3);
    b.insert(8);
    b.insert(5);

    BinarySearchTree<int>::Iterator i = b.begin();
    i++;
    i++;
    i++;
    i++;
    *i = 7;
    ASSERT_TRUE(*b.min_greater_than(8) == 10);
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(min_greater3) {
    BinarySearchTree <int> left;
    BinarySearchTree <double> right;
    left.insert(5);
    left.insert(3);
    left.insert(1);

    right.insert(0.0);
    right.insert(10.0);
    right.insert(100.0);

    ASSERT_TRUE(left.min_greater_than(10) == left.end());
    ASSERT_TRUE(right.min_greater_than(1000.0) == right.end());

    ASSERT_EQUAL(*left.min_greater_than(0), 1);
    ASSERT_EQUAL(*left.min_greater_than(2), 3);

    ASSERT_EQUAL(*right.min_greater_than(5.0), 10.0);
    ASSERT_EQUAL(*right.min_greater_than(80.0), 100.0);
}

TEST(general0) {
    BinarySearchTree<int> b;
    b.insert(9);
    b.insert(6);
    b.insert(12);
    b.insert(17);
    b.insert(10);
    b.insert(11);
    b.insert(15);
    b.insert(3);
    b.insert(8);
    b.insert(5);

    cout << b.to_string() << endl;
    ASSERT_TRUE(b.size() == 10);
    ASSERT_TRUE(b.height() == 4);
    ASSERT_TRUE(*b.max_element() == 17);

    ASSERT_TRUE(*b.min_element() == 3);
    ASSERT_TRUE(b.empty() == false);
    ASSERT_TRUE(b.check_sorting_invariant() == true);

    ///////////////
    BinarySearchTree<int>::Iterator i0 = b.find(16);
    BinarySearchTree<int>::Iterator i1 = b.min_greater_than(11);
    ASSERT_TRUE(i0 == b.end());
    ASSERT_TRUE(*i1 == 12);

    BinarySearchTree<int>::Iterator i2 = b.min_greater_than(6);
    BinarySearchTree<int>::Iterator i3 = b.min_greater_than(12);
    BinarySearchTree<int>::Iterator i4 = b.min_greater_than(10);
    BinarySearchTree<int>::Iterator i5 = b.min_greater_than(17);
    ASSERT_TRUE(*i2 == 8);
    ASSERT_TRUE(*i3 == 15);
    ASSERT_TRUE(*i4 == 11);
    ASSERT_TRUE(i5 == b.end());
}
TEST_MAIN()
