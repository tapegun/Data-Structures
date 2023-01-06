/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
    //your code here
}


template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    if(subRoot == NULL){return;}
    Node* temp = subRoot->right;
    subRoot->right = subRoot->left;
    subRoot->left = temp;
    mirror(subRoot->right);
    mirror(subRoot->left);
}
/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    std::stack<T> values;
    int biggest;
    InorderTraversal<int> trav(this->getRoot());
    for(auto track = trav.begin(); track!=trav.end(); ++track){
        values.push((*track)->elem);
    }
    if (!values.empty()){ 
		biggest = values.top(); //we will make sure that this value is the biggest... the order must be due to magnitude
		values.pop();
	}
    while (!values.empty())
	{
		if (biggest < values.top()) //going down stack to check for bigger than next value.. stack is in "order"
		{
			return false;
		}
		biggest = values.top();

		values.pop();
	}
    return true;
    // return false;
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    InorderTraversal<int> trav(this->getRoot());
    auto track = trav.begin();
    T& first = (*track)->elem;
    bool anstemp = true;
    bool & ans = anstemp;
    return isOrderedRecursive(root, ans, first);
    // your code here
}


template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot, bool& val, T& side) const{
    
    if(subRoot == NULL){return true;}
    isOrderedRecursive(subRoot->left, val, side);
    if(subRoot->elem < side){
        val = false;
    }
    side = subRoot->elem;
    isOrderedRecursive(subRoot->right, val, side);
    
    return val;


    
}

template <typename T>
int BinaryTree<T>::findMax(Node* subRoot) const //useless
{
    // if(subRoot==NULL)
	InorderTraversal<int> trav(subRoot);
	int max = 0;//subRoot->elem;
	for (auto track = trav.begin(); track != trav.end(); ++track) {
		if ((*track)->elem > max)
			max = (*track)->elem;
	}
	return max;

}


template <typename T>
int BinaryTree<T>::findMin(Node* subRoot) const //useless
{
    InorderTraversal<int> trav(subRoot);
	int min = 0;//subRoot->elem;
	for (auto track = trav.begin(); track != trav.end(); ++track) {
		if ((*track)->elem < min)
			min = (*track)->elem;
	}
	return min;
}


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */

