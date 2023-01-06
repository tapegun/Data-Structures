
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx +1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return currentIdx*2< _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    size_t leftchild = leftChild(currentIdx);
    size_t rightchild = rightChild(currentIdx);
    if (currentIdx*2+1<_elems.size())
        return (higherPriority(_elems[leftchild], _elems[rightchild]))? leftchild:rightchild;
    return currentIdx*2;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx))
    {
        size_t childIdx = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[childIdx], _elems[currentIdx]))
        {
            std::swap(_elems[currentIdx], _elems[childIdx]);
            heapifyDown(childIdx);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    size = 0;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
     _elems.push_back(T());
    for (int i = 0; i < (int)elems.size(); i++)
        _elems.push_back(elems[i]);
    for (int i = parent(_elems.size()); i > 0; i--)
        heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T val = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(1);
    return val;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
   return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    if(_elems.size()>idx){
        if(_elems[root()] < elem){
            _elems[idx] = elem;
            heapifyDown(idx);
        }
        if(_elems[root()] > elem){
            _elems[idx] = elem;
            heapifyUp(idx);
        }
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.size()==1;

}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
