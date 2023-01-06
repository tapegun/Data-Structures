#include "dsets.h"
void DisjointSets::addelements (int num)
{
	for(int i = 0; i < num; i++)
	{
		sets.push_back(-1);
	}
	return;
}

int DisjointSets::find (int elem)
{
	if(sets[elem] < 0)
		return elem;
	sets[elem] = find(sets[elem]);   //go up the line of numbers
    return sets[elem];
}

void DisjointSets::setunion (int a, int b)
{
    int root1 = find(a);
	int root2 = find(b);
	int newsize = this->size(a) + this->size(b);
	if (this->size(a) > this->size(b))
	{
		sets[root2] = root1;
		sets[root1] = -1*newsize;
	}
	else
	{
		sets[root1] = root2;
		sets[root2] = -1*newsize;
	}
}

int DisjointSets::size (int elem){ //finding the size of the set
    // int size = 0;
    // for(size_t i = 0; i < sets.size(); i++)
	// {
	// 	size += (sets[i] == elem);
	// }
	// return size;
	return -1*sets[find(elem)];     //get to the location that defines the set and multiply the size by -1
}

