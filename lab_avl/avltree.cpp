/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */


#include <iostream>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * rightside = t->right;        // swaping the nodes on the right and root
    t->right = rightside->left;
    rightside->left = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    rightside->height = std::max(heightOrNeg1(rightside->left), heightOrNeg1(rightside->right))+1; 
    t = rightside; // make sure the new "root" pointer points to the top of the mountain.
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * leftside = t->left;
    t->left = leftside->right;
    leftside->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    leftside->height = std::max(heightOrNeg1(leftside->right), heightOrNeg1(leftside->left))+1; 
    t = leftside;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int B = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(subtree->left != NULL){
        int Lbal = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (B == -2)        // specifically -2 because left and right are balanced
		{
			if (Lbal == 1) { // specificallly 1 because children are balanced.
                rotateLeftRight(subtree);
            }
			else {
                rotateRight(subtree);
            }
		}
    }
    if (subtree->right != NULL)
	{
		int Rbal = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if (B == 2)     // specifically 2 because left and right are balanced
		{
			if (Rbal == -1){    // specificallly -1 because children are balanced.
                rotateRightLeft(subtree);       // rightBal opposite sign so elbow
            } 
			else rotateLeft(subtree);
		}
	}
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree==NULL) {
		subtree = new Node(key,value);
		return;
	}
	else if (key < subtree->key){
        insert(subtree->left, key, value);
        subtree->height = 1+std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
    } 
	else if (key > subtree->key){
        insert(subtree->right, key, value);
        subtree->height = 1+std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
    }
	rebalance(subtree);

    

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree; // remove node.. base case  this is a leaf
			subtree = NULL;
			return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
			while (temp->right!=NULL){   // closest right value
                temp = temp->right;
            }
			K key_IOP = temp->key;
			V value_IOP = temp->value;
			remove(subtree, key_IOP);
			subtree->key = key_IOP;
			subtree->value = value_IOP;


        } else {
            /* one-child remove */
            // your code here
            if (subtree->left == NULL)
			{
				Node * temp = subtree;
				subtree = subtree->right; // skip over deleted item
				delete temp;
				temp = NULL;
			}
			else
			{
				Node * temp = subtree;
				subtree = subtree->left;    // skip over deleted item
				delete temp;
				temp = NULL;
			}
        }
        // your code here
    }
    subtree->height = 1+std::max(heightOrNeg1(subtree->right),heightOrNeg1(subtree->left));
	rebalance(subtree);
}
