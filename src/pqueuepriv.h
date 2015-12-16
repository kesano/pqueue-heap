/*
 * File: pqueuepriv.h
 * ------------------
 * This file contains the private section of the heap-based PriorityQueue class.
 */

/*
 * Implementation notes: Priority queue data structure
 * ---------------------------------------------------
 * This implementation uses a heap data structure to represent a priority queue.
 * Using a heap allows for operations on the priority queue to run in O(logN)
 * time.
 *
 * A heap consists of an array, in which the operation of a partially ordered
 * tree is simulated. A partially ordered tree is a binary tree, wherein the
 * following properties hold:
 *
 *  1. The tree is balanced, meaning that: the nodes are arranged in a pattern
 *     as close to that of a completely symmetrical tree as possible; the number
 *     of nodes along any path in the tree can never differ by more than one.
 *     The bottom level of the tree must also be filled in a strictly
 *     left-to-right order.
 *  2. Each node contains a key representing the priority of that element. A
 *     node's key is always less than or equal to the key in its children.
 *     Thus, the smallest key in the tree is always at the root.
 *
 *  Note: key values in a heap are not sorted the same way as key values in a binary
 *  search tree, in which the key value of a parent node is greater than its left
 *  children and less than its right children.
 *
 * The following diagram illustrates a partially ordered tree of nodes
 * containing the values (and inserted in the order) G, F, E, D, C, B, and A,
 * associated with keys 7, 6, 5, 4, 3, 2, and 1, respectively:
 *
 *                                         +-----+
 *                                         |  A  |
 *                                         +-----+
 *                                         |  1  |
 *                                         +-----+
 *                                      /           \
 *                                    /               \
 *                            +-----+                   +-----+
 *                            |  D  |                   |  B  |
 *                            +-----+                   +-----+
 *                            |  4  |                   |  2  |
 *                            +-----+                   +-----+
 *                           /       \                 /       \
 *                         /           \             /           \
 *                     +-----+       +-----+     +-----+       +-----+
 *                     |  G  |       |  E  |     |  F  |       |  C  |
 *                     +-----+       +-----+     +-----+       +-----+
 *                     |  7  |       |  5  |     |  6  |       |  3  |
 *                     +-----+       +-----+     +-----+       +-----+
 *
 *
 */

private:

/* Type used for each node in the tree */

    struct Node {
        double key;
        ValueType value;
    };

/* Constants */

    static const int INITIAL_CAPACITY = 10;

/* Instance variables */

    Node *array;        // Pointer to dynamic array representing the heap
    int capacity;       // Allocated size of array
    int count;          // Effective size of array

/* Private method prototypes */

    void swapNodes(int i, int j);
    void swapKeyDownward();
    void expandCapacity();
    void deepCopy(const PriorityQueue & src);
