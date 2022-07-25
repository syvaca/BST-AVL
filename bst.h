#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void postOrder(Node<Key, Value>* node);
    static int height(Node<Key, Value>* node, bool& balanced);
    static int maxHeight(int left, int right);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
   
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_= ptr;
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_(NULL);

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO

    if(this->current_ == rhs.current_) {
        return true;
    }

    return false;

}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO

    if(this->current_ != rhs.current_) {
        return true;
    }

    return false;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO

    current_ = successor(current_);
    return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    Key key = keyValuePair.first;
    Value value = keyValuePair.second;
    Node<Key, Value>* temp(root_);
    Node<Key, Value>* node = new Node<Key, Value> (key, value, NULL); //create a new node

    //tree is empty (adding to root)
    if(root_ == nullptr) {
        root_ = node;  
        return;
    }

    
    while(temp->getLeft() != NULL || temp->getRight() != NULL) {
        Key this_key = temp->getKey();
        if(key == this_key) { //update value
            temp->setValue(value);
            delete node; 
            return;
        }
        else if(key < this_key) {
            if(temp->getLeft() == NULL) { //checker to see if you need to stop
                break;
            }
            temp = temp->getLeft(); 
        }
        else if(key > this_key) {
            if(temp->getRight() == NULL) { //checker to see if you need to stop
                break;
            }
            temp = temp->getRight(); 
        }
    }

    if(temp->getRight() == NULL && temp->getLeft() != NULL) { //fill in right child
        temp->setRight(node);
        node->setParent(temp);
        return;
    }
    else if(temp->getRight() != NULL && temp->getLeft() == NULL) { //fill in left child
        temp->setLeft(node);
        node->setParent(temp);
        return;
    }
    else if(temp->getRight() == NULL && temp->getLeft() == NULL) { //decide which one to fill
        if(key < temp->getKey()) { //left
            temp->setLeft(node);
            node->setParent(temp);
            return;
        }
        else if(key > temp->getKey()) { //right
            temp->setRight(node);
            node->setParent(temp);
            return;
            
        }
    }
    
    delete node;
    
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    //this->printRoot(this->root_); //used for debugging

    //find predecessor 
    Node<Key, Value>* node = internalFind(key);
    Node<Key, Value>* pred = predecessor(node);

    if(node == NULL) { //node isnt in tree
        return;
    }

    //no children
    if(node->getLeft() == NULL && node->getRight() == NULL) {
        Node<Key, Value>* parent = NULL;
        if(node->getParent() != NULL) { //not the root
            parent = node->getParent();
 
            if(parent->getRight() == node) {
                parent->setRight(NULL);
            }
            else { //parent->getLeft() == node
                parent->setLeft(NULL);
            } 
        }
        else{
            root_ = NULL;
        }
        delete node;
        return;
    }

    //one child
    //right
    else if(node->getLeft() == NULL && node->getRight() != NULL) {
        Node<Key, Value>* right = node->getRight();
        Node<Key, Value>* parent = NULL;

        if(node->getParent() == NULL) { //node is the root
            right->setParent(NULL);
            root_ = right;
            delete node;
            return;
        }
        else if(node->getParent() != NULL) { //get the parent
            parent = node->getParent();
        }
        if(parent->getRight() == node) {
            parent->setRight(right);
            right->setParent(parent);

        }
        else if(parent->getLeft() == node) {
            parent->setLeft(right);
            right->setParent(parent);
        }
        delete node;
        return;
    }

    //left
    else if(node->getLeft() != NULL && node->getRight() == NULL) {
        Node<Key, Value>* left = node->getLeft();
        Node<Key, Value>* parent = NULL;

        if(node->getParent() == NULL) { //node is the root
            left->setParent(NULL);
            root_ = left;
            delete node;
            return;
        }
        else if(node->getParent() != NULL) { //get the parent
            parent = node->getParent();
        }
        if(parent->getRight() == node) {
            parent->setRight(left);
            left->setParent(parent);

        }
        else if(parent->getLeft() == node) {
            parent->setLeft(left);
            left->setParent(parent);
        }
        delete node;
        return;
    }


    //2 children
    else if(node->getLeft() != NULL && node->getRight() != NULL) { //else
         Node<Key, Value>* pred_left = NULL;
         Node<Key, Value>* pred_parent = NULL;

        if(pred->getLeft() != NULL) {
            pred_left = pred->getLeft();
        }
        if(pred->getParent() != NULL) {
            pred_parent = pred->getParent();
        }
        nodeSwap(node, pred); //swap
        

        
        if(pred_left != NULL && pred_parent != NULL) { //pred has left child
            if(pred_parent == node) {
                pred_left->setParent(pred);
                pred->setLeft(pred_left);
                delete node;
                return;
            }
            else {
                pred_left->setParent(pred_parent);
            }

            if(pred_parent->getRight() == node) { 
                pred_parent->setRight(pred_left);
            }
            else if(pred_parent->getLeft() == node) {
                pred_parent->setLeft(pred_left);
            }

            delete node;
            return;
        }
        else if(pred_left == NULL) { //pred has no child
            if(pred_parent == node) {
                pred->setLeft(NULL);
                delete node;
                return;
            }
            pred_parent->setRight(NULL);
            delete node;
            return;
        }
        else if(pred_parent == NULL) {
            pred_left->setParent(NULL);
        }

        delete node;
    }


    
    //in the case that the predeccesor has a child
    //move child from where it just was (promote child to old predecessor)/space of what just deleted


}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO    
    if(current == NULL || current->getLeft() == NULL) {
        return NULL;
    }

    if(current->getLeft() != NULL) {
        current = current->getLeft();
        while(current->getRight() != NULL) {
            current = current->getRight();
        }
        return current;
    }
    else { 
        if(current->getParent() == NULL) { //only right side of tree
            return NULL;
        } 
        Node<Key, Value>* temp = current->getParent();

        while(temp != NULL) {
            temp = current->getParent();
            if(temp->getRight() != current) {
                current = temp;
            }
            else if(temp->getRight() == current) {
                return current;
            }
        }
    }
    return NULL;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if(current == NULL || current->getRight() == NULL) { 
        return NULL;
    }

    if(current->getRight() != NULL) {
        current = current->getRight();
        while(current->getLeft() != NULL) {
            current = current->getLeft();
        }
        return current;
    }

    else {  
        if(current->getParent() == NULL) { //only left side of tree
            return NULL;
        } 
        Node<Key, Value>* temp = current->getParent();

        while(temp != NULL) {
            temp = current->getParent();
            if(temp->getLeft() != current) {
                current = temp;
            }
            else if(temp->getLeft() == current) {
                return current;
            }
        }
    }
    return NULL;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO

    Node<Key, Value>* node(root_);

    postOrder(node);
    
    root_ = NULL;

}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::postOrder(Node<Key, Value>* node) {

    //TODO
    if(node == NULL) {
        return;
    }

    postOrder(node->getLeft());
    postOrder(node->getRight());

    delete node;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

    Node<Key, Value>* temp(root_);

    if(temp == NULL) {
        return NULL;
    }

    while(temp->getLeft() != NULL) {
        temp = temp->getLeft();
    }

    return temp;    

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

    Node<Key, Value>* temp(root_);

    while(temp != NULL) {
        Key this_key = temp->getKey();
        if(key == this_key) {
            return temp;
        }
        else if(key < this_key) {
            temp = temp->getLeft();
        }
        else if(key > this_key) {
            temp = temp->getRight();
        }
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    bool result = true;
    Node<Key, Value>* temp = root_;
    height(temp, result);
    return result;

}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* node, bool& balanced) {
    //tree is empty
    if(node == NULL) {
        return 0;
    }

    //not balanced anymore
    if(!balanced) {
        return 0;
    }

    int lh = height(node->getLeft(), balanced);
    int rh = height(node->getRight(), balanced);

    if((lh - rh > 1) || (rh - lh > 1)) {
        balanced = false;
    }

    //height is one greater than max of left and right subtree
    return 1 + maxHeight(lh, rh);
    
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::maxHeight(int left, int right) {

    if(left >= right) {
        return left;
    }
    return right;
}





template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/


#endif
