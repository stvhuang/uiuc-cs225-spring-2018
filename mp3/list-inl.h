/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode *curr = head_;
  ListNode *prev = NULL;

  while (curr != NULL) {
    prev = curr;
    curr = curr->next;
    delete prev;
  }

  curr = NULL;
  prev = NULL;

  head_ = NULL;
  tail_ = NULL;
  length_ = 0;

  return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode *insert = new ListNode(ndata);

  if (head_ != NULL) {
    insert->next = head_;
    head_->prev = insert;
    head_ = insert;
  } else {  // head == NULL
    insert->prev = NULL;
    insert->next = NULL;
    head_ = insert;
    tail_ = insert;
  }

  insert = NULL;

  ++length_;

  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *insert = new ListNode(ndata);

  if (tail_ != NULL) {
    insert->prev = tail_;
    tail_->next = insert;
    tail_ = insert;
  } else {  // tail_ == NULL
    insert->prev = NULL;
    insert->next = NULL;
    head_ = insert;
    tail_ = insert;
  }

  insert = NULL;

  ++length_;

  return;
}

/**
 * Reverses the current List.
 */
template <class T>
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
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if ((startPoint == endPoint) || (startPoint == NULL) || (endPoint == NULL)) {
    return;
  }

  ListNode *oriStart = startPoint;
  ListNode *oriStartPrev = startPoint->prev;
  ListNode *oriEnd = endPoint;
  ListNode *oriEndNext = endPoint->next;
  ListNode *tmp = NULL;

  while (startPoint != endPoint) {
    tmp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = tmp;
    startPoint = startPoint->prev;
  }

  tmp = startPoint->prev;
  startPoint->prev = oriStartPrev;
  startPoint->next = tmp;
  endPoint = oriStart;
  endPoint->next = oriEndNext;

  if (oriStartPrev == NULL) {
    head_ = startPoint;
  } else {
    oriStartPrev->next = startPoint;
  }

  if (oriEndNext == NULL) {
    tail_ = endPoint;
  } else {
    oriEndNext->prev = endPoint;
  }

  oriStart = NULL;
  oriStartPrev = NULL;
  oriEnd = NULL;
  oriEndNext = NULL;
  tmp = NULL;

  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (head_ == NULL) {
    return;
  }

  ListNode *start = head_;
  ListNode *end = head_;

  while ((end->next != NULL) && (start->next != NULL)) {
    end = start;
    for (int i = 0; i < n - 1; ++i) {
      if (end->next != NULL) {
        end = end->next;
      }
    }

    reverse(start, end);
    start = end->next;
  }

  start = NULL;
  end = NULL;

  return;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if ((head_ == NULL) || (head_->next == NULL)) {
    return;
  }

  ListNode* curr = head_;
  ListNode* next = NULL;

  while ((curr->next != NULL) && (curr->next->next != NULL)) {
    curr = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    next = curr->next;
    tail_->next = curr;
    curr->prev = tail_;
    curr->next = NULL;
    tail_ = curr;
    curr = next;
  }

  curr = NULL;
  next = NULL;

  return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if ((start == NULL) || (splitPoint == 0)) {
    return start;
  }

  ListNode* newHead = head_;

  for (int i = 0; i < splitPoint; ++i) {
    newHead = newHead->next;
  }

  tail_ = newHead->prev;
  newHead->prev->next = NULL;
  newHead->prev = NULL;

  return newHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
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
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if ((first == NULL) || (second == NULL)) {
    return NULL;
  }

  if (first == second) {
    return first;
  }

  ListNode *newHead = NULL;
  ListNode *trackFirst = first;
  ListNode *trackSecond = second;
  ListNode *newEnd = NULL;

  if (first->data < second->data) {
    newHead = first;
    trackFirst = first->next;
  } else {
    newHead = second;
    trackSecond = second->next;
  }

  newEnd = newHead;

  while ((trackFirst != NULL) && (trackSecond != NULL)) {
    if ((trackFirst->data < trackSecond->data) || (trackSecond == NULL)) {
      newEnd->next = trackFirst;
      trackFirst->prev = newEnd;
      newEnd = trackFirst;
      trackFirst = trackFirst->next;
    } else {
      newEnd->next = trackSecond;
      trackSecond->prev = newEnd;
      newEnd = trackSecond;
      trackSecond = trackSecond->next;
    }
  }

  if (trackFirst == NULL) {
    newEnd->next = trackSecond;
    trackSecond->prev = newEnd;
  } else {  // trackSecond == NULL
    newEnd->next = trackFirst;
    trackFirst->prev = newEnd;
  }

  second = NULL;
  trackFirst = NULL;
  trackSecond = NULL;
  newEnd = NULL;

  return newHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode *newHead = start;

  if (chainLength == 1) {
    start->next = NULL;
    start->prev = NULL;
    return start;
  } else {
    ListNode *newStart = start;
    for (int i = 0; i < (chainLength / 2); ++i) {
      newStart = newStart->next;
    }

    newStart->prev->next = NULL;
    newStart->prev = NULL;

    start = mergesort(start, chainLength / 2);
    newStart = mergesort(newStart, chainLength - (chainLength / 2));

    newHead = merge(start, newStart);

    newStart = NULL;
  }

  return newHead;
}
