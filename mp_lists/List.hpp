/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1

    head_= NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* curr = head_;
  while (curr)
  {
      ListNode* nextNode = curr->next;    // get next node
      //delete (&(curr->data));
      delete curr;                         // delete current
      curr = nextNode;                     // set current to "old" next
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  //newNode -> prev = NULL;
  
  if (head_ != NULL) {
    newNode -> next = head_;
    head_ -> prev = newNode;
    head_ = newNode;
  }
  else{
    head_ = newNode;
    tail_ = newNode;
  }
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
    newNode -> prev = tail_;
    tail_ = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start == NULL){
    return NULL;
  }
  if(splitPoint == 0){
    return start;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  curr->prev->next = NULL;
	curr->prev = NULL; 
  // ending and starting NULL terminators
  return curr;

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode* nextStart;
  int firsttime = 0;
  for(int i = 0; i < length_/3; i++){
    nextStart = curr->next->next->next;
    if(!firsttime){
      head_ = curr->next;
      firsttime = 1;
    }else{
      curr->prev->next = curr->next;
    }
    curr->next->prev = curr->prev;
    curr->prev = curr->next->next;
    curr->next->next->next = curr;
    curr->next = nextStart;
    if(nextStart!=NULL){
      nextStart->prev = curr;
      curr = nextStart;
    }
      
  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if (startPoint==NULL || startPoint->next==NULL) // check if it exists
	{
		return;
	}
  ListNode * tracker = startPoint;
  // startPoint = endPoint;     // my mistake was that I was trying to flip it before I had flipped the internal nodes
  // endPoint = tracker;
  while(tracker != endPoint){  // maybe an issue here?
    // std::cout<< tracker->data<< std::endl;
    ListNode * temp = tracker->next;
    tracker->next = tracker->prev;
    tracker->prev = temp;
    tracker = tracker->prev;

  }
  // handle the endpoint which is not in the loop
  ListNode * temp = tracker->next;
  tracker->next = tracker->prev;
  tracker->prev = temp;
  //tracker = tracker->prev;


  //make sure the flipped values at the endpoints point to the right places and that the point back to the right places
  ListNode * temp_start_prev = startPoint->next;
  startPoint->next = endPoint->prev;    
  endPoint->prev = temp_start_prev;
  if(startPoint->next != NULL){startPoint->next->prev = startPoint;}
  if(endPoint->prev != NULL){endPoint->prev->next = endPoint;}
  

  //flip the start and endpoints because they are references
  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;




}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int num = length_/n + 1;
  ListNode * start = head_;
	ListNode * end = head_;
  for (int x=0; x<num; x++)
	{
    if (x<num-1)
		{
			end = start; // iterate end a certain amount of times n to get n spaces ahead of start
			for (int j=0; j<n-1 ; j++){end = end->next;}
		}
    else{end = tail_;}
    reverse(start, end);
    if (x==0){head_ = start;}
		if (x==num-1){tail_ = end;}
		start = end->next;
    

  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
if (chainLength == 1 || chainLength == 0)
	{
		return start;
	}
	//recursive case
	int firstHalf = chainLength/2;
	int secondHalf = chainLength-firstHalf;
	ListNode * splitted = split(start, firstHalf);
  // merge both the "left" and "right" sides of segment below
	return merge(mergesort(start,firstHalf), mergesort(splitted,secondHalf));
}



/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* result = first;
  ListNode* merger = second;
  if (result == NULL)
	{
		return merger;
	}
	if (merger == NULL)
	{
		return result;
	}

  if (merger->data < result->data)
	{
		result->prev = merger;
		second = merger->next;
		if (second != NULL){second->prev = NULL;}   // to handle to first case with nulls and stuff (this is mostly me figuring it out I didnt wanna write the loop yet)
		merger->next = result;
		first = merger;
		merger = second;
	}
  while(merger != NULL){
    if (merger->data < result->data)
    {
      ListNode* temp = result->prev;
      ListNode* temp1 = merger->next;
      result -> prev = merger;
      merger->prev = temp;
      merger->next = result;
      merger->prev->next = merger;
      merger = temp1;
    }
    else if (result->next != NULL){ // only happens if the above fails so result increment will skip if the above is true
      result = result->next;
    }
    else
		{
			result->next = merger;
			merger->prev = result;
      ListNode* temp1 = merger->next;
      merger->next = NULL;
			merger = temp1;
      result = result->next;
		}


  }
  return first;

}

