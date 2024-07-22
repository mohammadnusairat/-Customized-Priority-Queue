#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;  // Link to duplicates -- Part 2 only
    };

    NODE* root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE* curr;
    NODE* temp;  // Optional

    // TODO_STUDENT: add private helper function definitions here
    // helper function to recursively delete nodes
    void clearRecursive(NODE* node) const {
        if (node != nullptr) {
            // recursively delete left and right subtrees
            clearRecursive(node->left);
            clearRecursive(node->right);
            
            // delete the linked-list
            NODE* current = node->link;
            while (current != nullptr) {
                NODE* temp = current;
                current = current->link;
                delete temp;
            }

            // delete the current node
            delete node;
        }
    }
    // helper function to recursively copy nodes
    void copyNodesRecursive(const NODE* source, NODE*& destination) const {
        if (source == nullptr) {
            destination = nullptr;
            return;
        }

        // create a new node and copy the value and priority
        destination = new NODE; 
        destination->value = source->value;
        destination->priority = source->priority;
        // valgrind error uninitialized values
        destination->parent = nullptr; destination->left = nullptr; destination->right = nullptr; destination->link = nullptr;

        // recursively copy left and right subtrees
        if (source->left != nullptr) {
            copyNodesRecursive(source->left, destination->left);
            destination->left->parent = destination; // set parent pointer for left child
        }
        if (source->right != nullptr) {
            copyNodesRecursive(source->right, destination->right);
            destination->right->parent = destination; // set parent pointer for right child
        }
        // copy linked list if it exists
        if (source->link != nullptr) {
            // create a new linked list for the destination node
            destination->link = new NODE;
            NODE* destCurrent = destination->link;
            NODE* sourceCurrent = source->link;

            // copy each node from the source linked list to the destination linked list
            while (sourceCurrent != nullptr) {
                destCurrent->value = sourceCurrent->value;
                destCurrent->priority = sourceCurrent->priority;
                destCurrent->link = nullptr;

                // move to the next node in both lists
                sourceCurrent = sourceCurrent->link;
                if (sourceCurrent != nullptr) {
                    destCurrent->link = new NODE;
                    destCurrent = destCurrent->link;
                }
            }
        }
    }
    // helper function to recursively build a multi-line string
    void _recursiveHelper(NODE* node, ostream& output) const {
        // base case: reach the end of a path
        if (node == nullptr) { 
            return;
        }

        // recursively call the left side of the root
        _recursiveHelper(node->left, output);

        // output node priority and value
        NODE* current = node;
        while (current != nullptr) {
            output << current->priority << " value: " << current->value << endl;
            current = current->link;
        }

        // recursively call the right side of the root
        _recursiveHelper(node->right, output);

    }
    // helper function to recursively check equivalency of BST
    bool areEquivalent(NODE* a, NODE* b) const {
        // base cases: compare whether nodes exist or not
        if (a == nullptr && b == nullptr) {
            return true; // nodes are symmetric
        }
        
        if (a == nullptr || b == nullptr) { 
            return false; // nodes are asymmetric
        }

        // make sure values and priorities are the same
        if (a->value == b->value && a->priority == b->priority) {
            // recursive check the whole BST
            return areEquivalent(a->left, b->left) && areEquivalent(a->right, b->right);
        } else {
            return false;
        }
    }
    // helper function to find next in-order traversal
    NODE* inOrderTraversal(NODE* current) const {
        // edge case: already reached the root's parent (no next in order node)
        if (current == nullptr) {
            return nullptr;
        }

        // edge case: reached end of linked list
        if (current->link == nullptr && current->parent == nullptr && current->left == nullptr && current->right == nullptr) {
            // set current back to head of linked list
            current = this->temp;
        }
        
        // if the right subtree exists, move to the smallest node in the right subtree.
        if (current->right != nullptr) {
            current = current->right;
            // traverse to smallest node in right subtree
            while (current->left != nullptr) {
                current = current->left;
            }
        } else {
            // move up the tree until we find a node that is a left child; its parent is the next node.
            NODE* parent = current->parent;
            while (parent != nullptr && current == parent->right) { // While the current node is a right child
                current = parent;
                parent = parent->parent;
            }
            
            current = parent;
        }

        return current; // next node found
    }
   
   public:
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue() {
        // default constructor. set the private member variables to default values.
        this->temp = nullptr;
        this->sz = 0;
        this->root = nullptr;
        this->curr = nullptr;
    }

    /// Copy constructor.
    ///
    /// Copies the value-priority pairs from the provided `prqueue`.
    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other) {
        // copying elements FROM 'other' INTO 'this->' class
    
        // re-initialize variables
        this->temp = nullptr;
        this->sz = 0;
        this->root = nullptr;
        this->curr = nullptr;

        // recursively copy nodes from 'other' into 'this->'
        copyNodesRecursive(other.root, this->root);

        // update private member variable size
        this->sz = other.sz; 
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other) {
        // Check for self-assignment
        if (this == &other) {
            return *this;
        }

        // Clear current tree
        clear();

        // Copy from 'other'
        copyNodesRecursive(other.root, this->root);
        this->sz = other.sz;

        return *this;
    }

    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    /// Runs in O(N), where N is the number of values.
    void clear() {
        // clear the tree recursively
        clearRecursive(this->root);

        // reset private member variables
        this->sz = 0;
        this->root = nullptr;
        this->curr = nullptr;
        this->temp = nullptr;
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ///
    /// Runs in O(N), where N is the number of values.
    ~prqueue() {
        // destructor. use the clear function-- de-allocates all alloc'ed memory
        this->clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority) {
        // initialize the Node to be inserted
        NODE* newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->parent = nullptr;
        newNode->link = nullptr;

        // edge case: no nodes in the list (list is empty)
        if (this->root == nullptr) {
            this->root = newNode;
            this->sz++;
            return;
        }

        // traverse the tree to find the correct position to insert the node
        this->curr = this->root;
        while (true) {
            // if priority of the new node is less than the priority of the current node, go left
            if (newNode->priority < this->curr->priority) {
                if (this->curr->left == nullptr) { // if left side is empty, then add the new Node
                    this->curr->left = newNode;
                    newNode->parent = this->curr;
                    break;
                } else { // left side is NOT empty, keep going until it is 
                    this->curr = this->curr->left;
                }
            } else if (newNode->priority > this->curr->priority) { // if priority of the new node is greater than the priority of the current node, go right
                if (this->curr->right == nullptr) { // if right side is empty, then add the new Node
                    this->curr->right = newNode;
                    newNode->parent = this->curr;
                    break;
                } else { // right side is NOT empty, keep going until it is
                    this->curr = this->curr->right;
                }
            } else { // if priority of the new node is equal to the priority of the current node, add to linked list
                // if this is the last node of the linked list, add newNode
                if (this->curr->link == nullptr) {
                    this->curr->link = newNode;
                    break;
                } else {
                    // traverse to end of linked-list
                    this->temp = this->curr->link;
                    while (this->temp->link != nullptr) {
                        this->temp = this->temp->link;
                    }
                    this->temp->link = newNode;
                    break;
                }
            }
        }

        // increment the private member variable size
        this->sz++;
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const {
        // edge case: prqueue is empty
        if (this->sz == 0) {
            return T{}; // return default value for T
        }

        // traverse to the leftmost node (node with the smallest priority)
        NODE* current = this->root;
        while (current->left != nullptr) {
            current = current->left;
        }

        // return the value of the left most Node
        return current->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue() {
        // edge case: prqueue is empty
        if (this->sz == 0) {
            return T{}; // return default value for T
        }

        // traverse to the leftmost node (node with the smallest priority)
        NODE* nodeToRemove = root;
        NODE* parent = nullptr;
        while (nodeToRemove->left != nullptr) {
            parent = nodeToRemove;
            nodeToRemove = nodeToRemove->left;
        }

        // save the value to be returned
        T valueToReturn = nodeToRemove->value;

        if (nodeToRemove->link != nullptr) { // duplicates exist, remove the head of the linked list
            NODE* nextDuplicate = nodeToRemove->link;
            nextDuplicate->left = nodeToRemove->left; // usually null for the leftmost node
            nextDuplicate->right = nodeToRemove->right;
            nextDuplicate->parent = nodeToRemove->parent;
            // connect children to parents
            if (nextDuplicate->left != nullptr) {
                nextDuplicate->left->parent = nextDuplicate;
            }
            if (nextDuplicate->right != nullptr) {
                nextDuplicate->right->parent = nextDuplicate;
            }
            if (parent != nullptr) {
                parent->left = nextDuplicate; // parent's left is always the node to remove for the leftmost node
            } else {
                root = nextDuplicate; // the node was the root and had duplicates
                root->parent = nullptr;
            }
        } else { // no duplicates exist
            // if the node to remove is not the root and has no right child, simply detach it
            if (parent != nullptr) {
                parent->left = nodeToRemove->right; // attach the right child to the parent
                if (nodeToRemove->right != nullptr) {
                    nodeToRemove->right->parent = parent;
                }
            } else {
                // the node is the root and has no duplicates
                root = nodeToRemove->right; // the new root is the node's right child
                if (root != nullptr) {
                    root->parent = nullptr;
                }
            }
        }


        // free alloc'ed memory
        delete nodeToRemove;

        // decrement the size
        this->sz--;

        return valueToReturn;
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversa-l.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.
    void begin() {
        // reset internal state of BST
        this->curr = this->root;
        // traverse to left-most node
        while (this->curr != nullptr && this->curr->left != nullptr) {
            this->curr = this->curr->left;
        }
        // set temp to nullptr to distinguish between first call of next() and other calls of next()
        this->temp = nullptr;
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    ///
    /// Example usage:
    ///
    /// ```c++
    /// pq.begin();
    /// T value;
    /// int priority;
    /// while (pq.next(value, priority)) {
    ///   cout << priority << " value: " << value << endl;
    /// }
    /// ```
    ///
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority) {
        /* 
        questions abt this function we need to answer:
            1) how to handle egde case of first call after begin()?
            2) how to handle edge case of duplicates? (ie. how do we get out of linked list once we reach the end of it?)        
        */

        // no next node to traverse to. end of tree reached.
        if (this->curr == nullptr) {
            return false;
        }

        // edge case: first call to function after begin()
        if (this->temp == nullptr) {
            // set value and priority for the found node
            value = this->curr->value;
            priority = this->curr->priority;

            // update temp
            this->temp = this->curr;

            return true;
        }

        // check for duplicates first. if there are duplicates, we move to the next node in the linked list.
        if (this->curr->link != nullptr) {
            // set temp to head of linked list
            if (this->curr->parent != nullptr) {
                this->temp = this->curr;
            }

            // edge case: root might be a linked list
            if (this->curr == this->root) {
                this->temp = this->curr;
            }

            // set curr to next node of linked list
            this->curr = this->curr->link;

            // return value and priority
            value = this->curr->value;
            priority = this->curr->priority;
            
            return true;
        }

        // traverse to next node. (in the case of duplicates this function will return its parent until we get out of the linked list)
        this->curr = inOrderTraversal(this->curr);

        // if curr becomes nullptr, we've traversed the entire tree. no in-order value next
        if (this->curr == nullptr) {
            return false;
        }

        // set value and priority for the found node
        value = this->curr->value;
        priority = this->curr->priority;
        
        return true;
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Example:
    ///
    /// ```c++
    /// prqueue<string> names;
    /// names.enqueue("Gwen", 3);
    /// names.enqueue("Jen", 2);
    /// names.enqueue("Ben", 1);
    /// names.enqueue("Sven", 2);
    /// ```
    ///
    /// Calling `names.as_string()` would return the following multi-line
    /// string:
    ///
    /// ```text
    /// 1 value: Ben
    /// 2 value: Jen
    /// 2 value: Sven
    /// 3 value: Gwen
    /// ```
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const {
        // edge case: BST is empty
        if (this->sz == 0) {
            return "";
        }

        // recursively return the string form of the BST
        ostringstream ss;
        _recursiveHelper(this->root, ss);

        // turn stream output into string output
        return ss.str();
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    /// Two `prqueues` are equivalent if they have the same priorities and
    /// values, as well as the same internal tree structure.
    ///
    /// These two `prqueue`s would be considered equivalent, because
    /// they have the same internal tree structure:
    ///
    /// ```c++
    /// prqueue<string> a;
    /// a.enqueue("2", 2);
    /// a.enqueue("1", 1);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// and
    ///
    /// ```c++
    /// prqueue<string> b;
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// a.enqueue("1", 1);
    /// ```
    ///
    /// While this `prqueue`, despite containing the same priority-value pairs,
    /// would not be considered equivalent, because the internal tree structure
    /// is different.
    ///
    /// ```c++
    /// prqueue<string> c;
    /// a.enqueue("1", 1);
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// Runs in O(N) time, where N is the maximum number of nodes in
    /// either `prqueue`.
    ///
    bool operator==(const prqueue& other) const {
        return areEquivalent(this->root, other.root);
    }

    /// Returns a pointer to the root node of the BST.
    ///
    /// Used for testing the internal structure of the BST. Do not edit or
    /// change.
    ///
    /// Runs in O(1).
    void* getRoot() {
        return root;
    }
};
