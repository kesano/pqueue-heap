/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

/*
 * Implementation notes: constructor
 * ---------------------------------
 * Initializes an empty heap and sets the fields of the priority queue
 * object.
 */

PriorityQueue::PriorityQueue() {
    capacity = INITIAL_CAPACITY;
    array = new Node[capacity];
    count = 0;
}

/*
 * Implementation notes: destructor
 * --------------------------------
 * Frees the heap memory associated with the priority queue object,
 * which consists of the dynamic array.
 */

PriorityQueue::~PriorityQueue() {
    delete[] array;
}

int PriorityQueue::size() const {
    return count;
}

bool PriorityQueue::isEmpty() const {
    return count == 0;
}

void PriorityQueue::clear() {
    count = 0;
}

/*
 * Implementation notes: enqueue
 * -----------------------------
 * This method inserts a new node at the correct level in the
 * partially ordered tree. In order for the new node to be placed
 * in its correct position, this implementation begins by inserting
 * the node as a new leaf in the next available leftmost position in
 * the tree. Once inserted, this method traverses through each level
 * of the tree. At any level the node's key is found to be less than
 * (higher in priority) or equal to that of its parent, the node is
 * swapped with its parent, so that the node becomes the parent and
 * the old parent takes the place the node previously occupied. Swapping
 * the node with its parent when its key value is the same as its parent
 * ensures that nodes with equal keys are ordered in the heap by the node
 * that has spent the longest time in the tree. This process repeats
 * until either the node's key is greater than its parent's key, or the
 * node is at the root.
 */

void PriorityQueue::enqueue(string value, double priority) {
    if (count == capacity) expandCapacity();
    Node t;
    t.key = priority;
    t.value = value;
    array[count] = t;
    if (!isEmpty()) {
        int i = count;
        int parentPos = (i - 1) / 2;
        while (array[i].key <= array[parentPos].key) {
            swapNodes(i, parentPos);
            i = parentPos;
            parentPos = (i - 1) / 2;
            if (i == 0 && parentPos == 0) break;
        }
    }
    count++;
}

/*
 * Implementation notes: dequeue
 * -----------------------------
 * This implementation replaces the key in the root with the key
 * in the node to be deleted and then swaps keys down the tree
 * until the ordering property is restored.
 */

string PriorityQueue::dequeue() {
    if (isEmpty()) error("dequeue: Attempting to dequeue an empty priority queue");
    Node result = array[0];
    if (--count >= 1) {
        array[0] = array[count];
        swapKeyDownward();
    }
    return result.value;
}

string PriorityQueue::peek() const {
    if (isEmpty()) error("peek: Attempting to peek an empty priority queue");
    return array[0].value;
}

double PriorityQueue::peekPriority() const {
    if (isEmpty()) error("peekPriority: Attempting to peek an empty priority queue");
    return array[0].key;
}

/*
 * Implementation notes: swapKeyDownward
 * -------------------------------------
 * This helper method swaps the key that was moved into the root
 * position down the tree until the tree's ordering property is
 * restored. If the left and right children have the same key value
 * which is lower than the key traversing downward, that key is swapped
 * with the right child. This ensures that nodes with equal keys are
 * dequeued on a FIFO basis.
 */

void PriorityQueue::swapKeyDownward() {
    int i = 0;
    while (i < count - 1) {
        int leftChildPos = 2 * i + 1;
        int rightChildPos = 2 * i + 2;
        if (leftChildPos < count && rightChildPos < count) {
            if (array[leftChildPos].key < array[rightChildPos].key) {
                if (array[leftChildPos].key < array[i].key) swapNodes(i, leftChildPos);
                i = leftChildPos;
            } else {
                if (array[rightChildPos].key < array[i].key) swapNodes(i, rightChildPos);
                i = rightChildPos;
            }
        } else {
            if (leftChildPos < count && rightChildPos >= count) {
                if (array[leftChildPos].key < array[i].key) swapNodes(i, leftChildPos);
            }
            i = leftChildPos;
        }
    }
}

/*
 * Implementation notes: swapNodes
 * -------------------------------
 * This helper method swaps two nodes, so that they both assume the
 * index position of the other in the heap. Before performing the swap,
 * this implementation makes a copy of one of the nodes so that it is
 * accessible to be placed in its new index position, after its old
 * position has been overwritten.
 */

void PriorityQueue::swapNodes(int i, int j) {
    Node tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

/*
 * Implementation notes: copy constructor
 * --------------------------------------
 * Initializes the current object to be a deep copy of the argument.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

/*
 * Implementation notes: assignment operator
 * Usage: q1 = q2;
 * -----------------------------------------
 * Assigns q2 to q1 so that the two priority queues function as
 * independent copies. For the PriorityQueue class, this kind of
 * assignment requires making a deep copy that includes the dynamic
 * array.
 */

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This method doubles the capacity of the priority queue by copying
 * values from the array into a new dynamic array. Because the new
 * array has more space, values from the old array are copied starting
 * at the first element of the new array. This method frees the heap
 * memory associated with the old array as it is no longer in use.
 */

void PriorityQueue::expandCapacity() {
    capacity *= 2;
    Node *oldArray = array;
    array = new Node[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This method copies all the data from the PriorityQueue passed as
 * an argument into the current object, including the values in the
 * dynamic array.
 */

void PriorityQueue::deepCopy(const PriorityQueue & src) {
    count = src.count;
    capacity = src.capacity;
    if (capacity < INITIAL_CAPACITY) capacity = INITIAL_CAPACITY;
    array = new Node[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = src.array[i];
    }
}








