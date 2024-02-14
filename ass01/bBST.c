#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bBST.h"
#include "List.h"

////////////////////////////////////////////////////////////////////////
/* IMPORTANT:
   Do NOT modify the code above this line.
*/
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Auxiliary function prototypes

// Write Auxiliary function prototypes here, and declare them as static
// Group 1 
static void doTreeFree(Node n);
static int doTreeSearch(Node n, int key, int status);
static Node doTreeInsert(Node n, int key, bool* status);
static Node createNewNode(int key);
static Node doTreeDelete(Node n, int key, bool* status);
static Node deleteKey(Node n);
static Node joinTrees(Node n1, Node n2);
static Node rotateRight(Node n1);
static Node rotateLeft(Node n2);
static int height(Node n);
static int max(int height1, int height2);
static int updateHeight(Node n);
static int getBalance(Node n);
static void doTreeToList(Node n, List listHead);
// Group 2 functions
static void doTreeKthSmallest(Node n, int k, int *value, int *count);
static void doTreeKthLargest(Node n, int k, int *value, int *count);
static void doTreeLCA(Node n, int a, int b, int *savedValue);
static void doTreeFloor(Node n, int key, int *savedValue);
static void doTreeCeiling(Node n, int key, int *savedValue);
static void doTreeSearchBetween(Node n, List listHead, int lower, int upper);

////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////

/**
 * Creates a new empty tree.
 * The time complexity of this function must be O(1).
 */
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "couldn't allocate Tree\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

////////////////////////////////////////////////////////////////////////

/**
 * Frees all memory allocated for the given tree.
 * The time complexity of this function must be O(n).
 */
void TreeFree(Tree t) {
    doTreeFree(t->root);
    free(t);
}

// wrapper for TreeFree
static void doTreeFree(Node n) { 
    if (n != NULL) {
        doTreeFree(n->left);
	    doTreeFree(n->right);
	    free(n);
    }
}

////////////////////////////////////////////////////////////////////////

/**
 * Searches the tree for a given key and returns true if the key is in
 * the tree or false otherwise.
 * The time complexity of this function must be O(log n).
 */
bool TreeSearch(Tree t, int key) {
    // empty tree
    if (t == NULL) { 
        return false;
    }
    int status = 0;
    status = doTreeSearch(t->root, key, status);
    // return bool based on status
    if (status == 1) { 
        return true;
    } else { 
        return false;
    }
}

// wrapper for TreeSearch
static int doTreeSearch(Node n, int key, int s) { 
    if (n != NULL) { 
        if (n->key == key) { 
            s = 1;
            return s;
        }
        else if (key < n->key) { 
            return doTreeSearch(n->left, key, s);
        }
        else if (key > n->key) { 
            return doTreeSearch(n->right, key, s);
        }
    } else { 
        s = 0;
        return s;
    }
    return s;
    
}
////////////////////////////////////////////////////////////////////////

/**
 * Inserts the given key into the tree.
 * You must use the proper AVL insertion algorithm.
 * Returns true if the key was inserted successfully, or false if the
 * key was already present in the tree.
 * The time complexity of this function must be O(log n).
 */
bool TreeInsert(Tree t, int key) {
    bool status = true; 
    t->root = doTreeInsert(t->root, key, &status);
    return status;
}

// wrapper for TreeInsert
static Node doTreeInsert(Node n, int key, bool* status) {  
    // make a newnode once you've found the spot to put it
    // insertion of node
    if (n == NULL) { 
        Node insertedNode = createNewNode(key);
        *status = true;
        return insertedNode;
    }
    // key already exists
    else if (key == n->key) { 
        *status = false;
        return n;
    }
    else { 
        if (key < n->key) { 
            n->left = doTreeInsert(n->left, key, status);
        }
        else if (key > n->key) { 
            n->right = doTreeInsert(n->right, key, status);  
        }
        // update height
         n->height = updateHeight(n);
        // balance out the tree
        if ((getBalance(n)) > 1) { 
            if (key > n->left->key) { 
                n->left = rotateLeft(n->left);
            }
            n = rotateRight(n);
        }
        else if (getBalance(n) < -1) { 
            if (key < n->right->key) { 
                n->right = rotateRight(n->right);
            }
            n = rotateLeft(n);
        }
    }
    return n;
}

// Helper function to make a new node 
static Node createNewNode(int key) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

// Helper function to help make the height balance
// Rotates nodes to the right 
// from BSTree.c sample pseudocode from lecture (rotateRight)
static Node rotateRight(Node n1) { 
    if (n1 == NULL || n1->left == NULL) {
        return n1;
    }
    Node n2 = n1->left;
    // rotate 
    n1->left = n2->right;
    n2->right = n1;
    // update height 
    n1->height = updateHeight(n1);
    n2->height = updateHeight(n2);
    return n2;
}

// Helper function to help make the height balance
// Rotates nodes to the right 
// from BSTree.c sample pseudocode (rotateRight)
static Node rotateLeft(Node n2) { 
    if (n2 == NULL || n2->right == NULL) {
        return n2;
    }
    Node n1 = n2->right;
    n2->right = n1->left;
    n1->left = n2;
    //update height
    n2->height = updateHeight(n2);
    n1->height = updateHeight(n1);
    return n1;
}

// find the height of the node
static int height(Node n) { 
    if (n == NULL) { 
        return -1;
    } 
    return n->height;
}

// find the maximum of two integers
static int max(int leftHeight, int rightHeight) { 
    if (leftHeight > rightHeight) { 
        return leftHeight;
    } 
    return rightHeight;
}

// update the height after a rotation
static int updateHeight(Node n) { 
    return 1 + max(height(n->left),height(n->right));
}

// check the balance of the tree
static int getBalance(Node n) { 
    return height(n->left) - height(n->right);
}
////////////////////////////////////////////////////////////////////////

/**
 * Deletes the given key from the tree if it is present.
 * You must use the proper AVL deletion algorithm.
 * Returns true if the key was deleted successfully, or false if the key
 * was not present in the tree.
 * The time complexity of this function must be O(log n).
 */
bool TreeDelete(Tree t, int key) {
    bool status = true;
    t->root = doTreeDelete(t->root, key, &status);
    return status;
}

// wrapper for TreeDelete
static Node doTreeDelete(Node n, int key, bool* status) {
    if (n == NULL) { 
        *status = false;
        return n;
    }
    // found the key, now use deleteKey to delete it
    if (n->key == key) { 
        Node newSubTree = deleteKey(n);
        *status = true;
        return newSubTree;
    }
    // keep traversing tree to find where the node is 
    else if (key < n->key) { 
        n->left = doTreeDelete(n->left, key, status);
    }
    else if (key > n->key) { 
        n->right = doTreeDelete(n->right, key, status);
    } 

    // update height
    n->height = updateHeight(n);

    // balance out the tree
    if (getBalance(n) > 1) { 
        if (getBalance(n->left) < 0) { 
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    }
    else if ((getBalance(n))< -1) { 
        if (getBalance(n->right) > 0) { 
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }
    return n;
}

// Delete the key given the node 
// using pseudocode from BSTree.c (TreeDelete)
static Node deleteKey(Node n) { 
    Node new = NULL;
    // no children case
    if (n->left == NULL && n->right == NULL) { 
        new = NULL;
    }
    else if (n->left == NULL) { 
        new = n->right;
    }
    else if (n->right == NULL) { 
        new = n->left;
    }
    // 2 children case
    else { 
        new = joinTrees(n->left, n->right);
        
    }
    free (n);
    n = new;
    return n;
}

// from lecture code BSTree.c (joinTrees)
// finds the minimum child and makes that the new head node
static Node joinTrees(Node n1, Node n2) { 
    Node curr = n2;
    Node newParent = NULL;
    while (curr->left != NULL) { 
        newParent = curr;
        curr = curr->left;
    }
    if (newParent != NULL) { 
        newParent->left = curr->right;
        curr->right = n2;
    }
    curr->left = n1;
    return curr;
}
////////////////////////////////////////////////////////////////////////

/**
 * Creates a list containing all the keys in the given tree in ascending
 * order.
 * The time complexity of this function must be O(n).
 */
List TreeToList(Tree t) {
    List newList = ListNew();
    doTreeToList(t->root, newList);

    return newList;
}

// wrapper for TreeToList
static void doTreeToList (Node n, List listHead) { 
    if (n != NULL) { 
        doTreeToList(n->left, listHead);
        // append before going to the right to get ascending order
        ListAppend(listHead, n->key);
        doTreeToList(n->right, listHead);
    }

}

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

/**
 * Returns the k-th smallest key in the tree.
 * Assumes that k is between 1 and the number of nodes in the tree.
 * k = 1 will return the smallest value in the tree.
 * The time complexity of this function must be O(log n + k).
 */
int TreeKthSmallest(Tree t, int k) {
    int value = 0;
    int count = 0;
    doTreeKthSmallest(t->root, k, &value, &count);
    return value;
}

// wrapper for TreeKthSmallest
static void doTreeKthSmallest(Node n, int k, int *value, int *count) { 
    if (n == NULL) {  
        return ;
    }
    doTreeKthSmallest(n->left, k, value, count);
    if (*count < k) { 
        *count = *count+1;
        if (*count == k ){ 
            *value = n->key;
            return;
        }
        doTreeKthSmallest(n->right, k, value, count); 
    }
}

////////////////////////////////////////////////////////////////////////

/**
 * Returns the k-th largest key in the tree.
 * Assumes that k is between 1 and the number of nodes in the tree.
 * k = 1 will return the largest value in the tree.
 * The time complexity of this function must be O(log n + k).
 */
int TreeKthLargest(Tree t, int k) {
    int value = 0;
    int count = 0;
    doTreeKthLargest(t->root, k, &value, &count);
    return value;
}

// wrapper for TreeKthLarget
static void doTreeKthLargest(Node n, int k, int *value, int *count) { 
    if (n == NULL) {  
        return ;
    }
    // look right to start from the largest value
    doTreeKthLargest(n->right, k, value, count);
    // add to count and return if count = key
    if (*count < k) { 
        *count = *count+1;
        if (*count == k ){ 
            *value = n->key;
            return;
        }
        // if count != k, then traverse the left node to see if the value is 
        doTreeKthLargest(n->left, k, value, count); 
    }
}
////////////////////////////////////////////////////////////////////////

/**
 * Returns the lowest common ancestor of two keys, a and b.
 * Returns UNDEFINED if either a or b are not present in the tree.
 * a may be larger than b, or equal to each other.
 * Either a or b may be the LCA in some cases.
 * The time complexity of this function must be O(log n).
 */
int TreeLCA(Tree t, int a, int b) {
    bool doesAExist = TreeSearch(t, a);
    bool doesBexist = TreeSearch(t, b);
    int value = 0;
    if (doesAExist == true && doesBexist == true) { 
        doTreeLCA(t->root, a, b, &value);
        return value;
    } else { 
        return UNDEFINED;
    }
}
// wrapper for TreeLCA
static void doTreeLCA(Node n, int a, int b, int *savedValue) {
    if (n == NULL) {
        return;
    } 
    if (n->key == a) { 
        *savedValue = n->key;
        return;
    } else if (n->key == b) { 
        *savedValue = n->key;
        return;
    }
    // traverse left
    if (a < n->key && b < n->key) { 
        doTreeLCA(n->left, a, b, savedValue);
    }
    // traverse right
    else if (a > n->key && b > n->key) { 
        doTreeLCA(n->right, a, b, savedValue);
    } 
    // found the node it's supposed to be in
    else { 
        *savedValue = n->key;
        return;
    }
}
////////////////////////////////////////////////////////////////////////

/**
 * Returns the largest key less than or equal to the given value.
 * Returns UNDEFINED if there is no such key.
 * The time complexity of this function must be O(log n).
 */
int TreeFloor(Tree t, int key) {
    int savedValue = UNDEFINED;
    doTreeFloor(t->root, key, &savedValue);
    return savedValue;
}

//wrapper for TreeFloor
static void doTreeFloor(Node n, int key, int *savedValue) { 
    if (n == NULL) {
        return;
    } 
    // return if the key exists in the tree
    if (n->key == key) { 
        *savedValue = n->key;
        return;
    } 

    if (key < n->key) { 
        doTreeFloor(n->left, key, savedValue);
    }
    else { 
        *savedValue = n->key;
        doTreeFloor(n->right, key, savedValue);   
    } 
}

////////////////////////////////////////////////////////////////////////

/**
 * Returns the smallest key greater than or equal to the given value.
 * Returns UNDEFINED if there is no such key.
 * The time complexity of this function must be O(log n).
 */
int TreeCeiling(Tree t, int key) {
    int s = UNDEFINED;
    doTreeCeiling(t->root, key, &s);
    return s;
}

//wrapper for TreeCeiling
static void doTreeCeiling(Node n, int key, int *savedValue) { 
    if (n == NULL) {
        return;
    } 

    if (n->key == key) { 
        *savedValue = key;
        return;
    }

    if (key < n->key) { 
        *savedValue = n->key;
        doTreeCeiling(n->left, key, savedValue);
    } else  {
        doTreeCeiling(n->right, key, savedValue);
    } 
    
}

////////////////////////////////////////////////////////////////////////

/**
 * Searches for all keys between the two given keys (inclusive) and
 * returns the keys in a list in ascending order.
 * Assumes that lower is less than or equal to upper.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 */
List TreeSearchBetween(Tree t, int lower, int upper) {
    List newList = ListNew();
    doTreeSearchBetween(t->root, newList, lower, upper);
    return newList;
}

// wrapper for TreeSearchBetween
static void doTreeSearchBetween(Node n, List listHead, int lower, int upper) { 
    if (n == NULL) { 
        return;
    }

    if (n->key >= lower && n->key <= upper) { 
        // do left first before ListAppend to append in ascending order
        doTreeSearchBetween(n->left, listHead, lower, upper);
        ListAppend(listHead, n->key);
        doTreeSearchBetween(n->right, listHead, lower, upper);
    } 
    // go right if the values are lower than the lower limit
    else if (n->key < lower) { 
        doTreeSearchBetween(n->right, listHead, lower, upper);
    
    } 
    // go left if the values are higher than the upper limit
    else if (n->key > upper) { 
        doTreeSearchBetween(n->left, listHead, lower, upper);
    }
}

////////////////////////////////////////////////////////////////////////