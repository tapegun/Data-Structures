/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include "math.h"
#include <iostream>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if(first[curDim] != second[curDim]){
    return (first[curDim] < second[curDim]);
  }
  return (first < second);

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int currSum = 0;
    int potSum = 0;
    for(int i = 0; i < Dim; i++){
      currSum += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      potSum += (target[i] - potential[i]) * (target[i] - potential[i]);
    }

    // currSum = sqrt(currSum); //unnecessary
    // potSum = sqrt(potSum);

    if(potSum < currSum){
      return true;
    }
    if(potSum > currSum){
      return false;
    }
    return (potential < currentBest);

}




template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & Points, int left, int right, int pivotIndex, int d){
	Point<Dim> pivotValue = Points[pivotIndex];
	Point<Dim> temp = Points[right];
	Points[right] = Points[pivotIndex];
	Points[pivotIndex] = temp;  
	int storeIndex = left;
	for (int i=left; i<right; i++) {
		if (smallerDimVal(Points[i], pivotValue, d)) {
			temp = Points[i];
			Points[i] = Points[storeIndex];
			Points[storeIndex] = temp; 
			storeIndex++;
		}
	}
	temp = Points[storeIndex];
	Points[storeIndex] = Points[right];
	Points[right] = temp;  
	return storeIndex;
}

template<int Dim>
void KDTree<Dim>::select(vector<Point<Dim>> & Points, int left, int right, int k, int d){
	if (left==right) return;
	int pivotIndex = (left+right)/2;
	pivotIndex = partition(Points, left, right, pivotIndex, d);
	if (k == pivotIndex) return;
	else if (k < pivotIndex) return select(Points, left, pivotIndex-1, k, d);
	else return select(Points, pivotIndex+1, right, k, d);
	return;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::makeTree(vector<Point<Dim>>& Points, int left, int right, int d)
{

	if (right < left) return NULL;
	KDTreeNode * node = new KDTreeNode();
	int middle = (left+right)/2;
	select(Points, left, right, middle, d%Dim);
	node->point = Points[middle];
	node->left = makeTree(Points, left, middle-1, (d+1)%Dim);
	node->right = makeTree(Points, middle+1, right, (d+1)%Dim);
	return node;
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  vector<Point<Dim>> Points(newPoints);
  notATree = newPoints;
	size = Points.size();
	root = makeTree(Points, 0, Points.size()-1, 0);
     
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
   size = other.size();
   notATree = other.notATree;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if (this != &rhs) {   //make sure not a pointer to self
    clear(root);
    root = copy(rhs.root);
		size = rhs.size();
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root);
}

template <int Dim>
void KDTree<Dim>::clear()   //general helper func for clearing without pluggin in root
{
    clear(root);
    root = NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(const KDTreeNode* subRoot)
{
    if (subRoot == NULL)
        {return NULL;}

    KDTreeNode* newNode = new KDTreeNode(subRoot->point);
    newNode->right = copy(subRoot->right);        //recursive copy left and right
    newNode->left = copy(subRoot->left);
    return newNode;
}

template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode* subRoot)
{
    if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

template<int Dim>
int KDTree<Dim>::distance(const Point<Dim> &a, const Point<Dim>&b) const
{
    int ret = 0;
    for (int i = 0; i < Dim; i++)
    {
        ret+= pow(a[i]-b[i],2);
    }
    return ret;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  Point<Dim> pointAnswer = findNearestHelper(0, query, 0, notATree.size()-1, notATree[(notATree.size()-1)/2]);
     
    return pointAnswer;
}


template<int Dim>
Point<Dim>  KDTree<Dim>::findNearestHelper(int curDim, const Point<Dim> &query, int left, int right, const Point<Dim> &currentBest) const
{
    Point<Dim> answer = currentBest;
    bool shouldLeft = true;
    if (left == right)
    {
        if (shouldReplace(query, currentBest, notATree[left]))
        {
             answer = notATree[left]; //found answer
            return answer;
        }
        answer = currentBest;
        return answer;
    }
    int median = (left + right)/2;
    int otherSubMedian;
    if (smallerDimVal(notATree[median], query, curDim) && right > median){   //check dimension
        answer = findNearestHelper((curDim+1)%Dim, query, median+1, right, currentBest);
        shouldLeft = false;
        otherSubMedian = (left+median-1)/2;
    }
    if (smallerDimVal(query, notATree[median], curDim) && left < median){   
        answer = findNearestHelper((curDim+1)%Dim, query, left, median-1, currentBest);
        shouldLeft = true;
        otherSubMedian = (median+1+right-1)/2;
    }

    if (shouldReplace(query, answer, notATree[median])){
        answer = notATree[median];
    }
    
    Point<Dim> pnt = notATree[median];    //midpoint
    if (pow(pnt[curDim] - query[curDim],2) <= distance(query, answer)){
        if (shouldLeft && right > median){
            answer = findNearestHelper((curDim+1)%Dim, query, median+1, right, answer);
        }
        if (!shouldLeft && left < median){
            answer = findNearestHelper((curDim+1)%Dim, query, left, median-1, answer);
        }
    }
    return answer;
}
