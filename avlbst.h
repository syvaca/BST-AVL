#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key& key);
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix( AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key, Value>* n, int8_t diff);
    void rotateLeft( AVLNode<Key, Value>* node);
    void rotateRight( AVLNode<Key, Value>* node);
    bool zigzig( AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    bool zigzag( AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{

    //this->printRoot(this->root_); //used for debugging

    Key key = new_item.first;
    Value value = new_item.second;
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* node = new AVLNode<Key, Value> (key, value, NULL); //create a new node
    node->setBalance(0);

    //tree is empty (adding to root)
    if(temp == nullptr) {
        this->root_ = node;
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

    if(key == temp->getKey()) { //update value in the case that temp has no children
            temp->setValue(value);
            delete node; 
            return;
        }

    //temp is the parent
    if(temp->getRight() == NULL && temp->getLeft() != NULL) { //fill in right child
        temp->setRight(node);
        node->setParent(temp);
    }
    else if(temp->getRight() != NULL && temp->getLeft() == NULL) { //fill in left child
        temp->setLeft(node);
        node->setParent(temp);
    }
    else if(temp->getRight() == NULL && temp->getLeft() == NULL) { //decide which one to fill
        
        if(key < temp->getKey()) { //left
            temp->setLeft(node);
            node->setParent(temp);
        }
        else if(key > temp->getKey()) { //right
            temp->setRight(node);
            node->setParent(temp);
        }
    }

    //fix the balance of the parent
    if((temp->getBalance() == -1) || (temp->getBalance() == 1)) {
        temp->setBalance(0);
    }
    else if(temp->getBalance() == 0) {
        if(temp->getLeft() == node) {
            temp->updateBalance(-1);
        }
        else {
            temp->updateBalance(1);
        }
        insertFix(temp, node);
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
    if(p == NULL || p->getParent() == NULL) {
        return;
    }
 
    AVLNode<Key, Value>* g(p->getParent());
    
    //left child
    if(g->getLeft() == p) {
        g->updateBalance(-1);
        
        if(g->getBalance() == 0) { //case 1
            return;
        }
        else if(g->getBalance() == -1) { //case 2
            insertFix(g,p);
        }
        else if(g->getBalance() == -2) { //case 3
            if(zigzig(g, p, n)) {
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else if(zigzag(g, p, n)) {
                rotateLeft(p);
                rotateRight(g);
            
                
                if(n->getBalance() == -1) { //case 3a
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0) { //case 3b
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 1) { //case 3c
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }


    //right child
    if(g->getRight() == p) {
        g->updateBalance(1);
        
        if(g->getBalance() == 0) { //case 1
            return;
        }
        else if(g->getBalance() == 1) { //case 2
            insertFix(g,p);
        }
        else if(g->getBalance() == 2) { //case 3
            if(zigzig(g, p, n)) {
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else if(zigzag(g, p, n)) {
                rotateRight(p);
                rotateLeft(g);
            
                
                if(n->getBalance() == 1) { //case 3a
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0) { //case 3b
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == -1) { //case 3c
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }   
            } 
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // this->printRoot(this->root_); //used fore debugging


    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    int8_t diff = 0;

    if(node == NULL) {
        return;
    }

    AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));

    //node has 2 children
    if(node->getLeft() != NULL && node->getRight() != NULL) {
        nodeSwap(node, pred);
    }

    //get pred old child if there is one (would also be nodes child is there is no pred)
    AVLNode<Key, Value>* child = NULL;
    if(node->getLeft() != NULL) {
        child = node->getLeft();
    }
    else if(node->getRight() != NULL) {
        child = node->getRight();
    }

    //get pred old parent if there is one (would also be nodes parent is there is no pred)
    AVLNode<Key, Value>* parent = NULL;
    bool isLeft = false;
    if(node->getParent() != NULL) {
        parent = node->getParent();
        if(parent->getLeft() == node) {
            isLeft = true;
        }
    }

    //remove node
    if(parent != NULL) { //pred has a parent
        if(parent->getLeft() == node) {
            diff += 1;
        }
        else if(parent->getRight() == node) {
            diff += -1;
        }

        if(child != NULL) { //pred has a child
            if(isLeft) {
                parent->setLeft(child);
            }
            else if(!isLeft) {
                parent->setRight(child);
            }
            child->setParent(parent);
        }
        else { //pred doesnt have a child
            if(isLeft) {
                parent->setLeft(NULL);
            }
            else {
                parent->setRight(NULL);
            }      
        }
    }
    else { //pred didnt have a parent
        this->root_ = child;
        if(child != NULL) {
            child->setParent(NULL);
        }
    }

    delete node;

    removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff) {
    if(n == NULL) {
        return;
    }

    AVLNode<Key, Value>* p = n->getParent();
    int8_t ndiff;

    if(p != NULL) {
        if(p->getLeft() == n) { //n is a left child
            ndiff = 1;
        }
        else if(p->getRight() == n) { //n is a right child
            ndiff = -1;
        }
    }

    if(diff == -1) {
        if(n->getBalance() + diff == -2) { //case 1
            AVLNode<Key, Value>* c = n->getLeft();

            if(c->getBalance() == -1) { //case 1a
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if(c->getBalance() == 0) { //case 1b
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                return;
            }
            else if(c->getBalance() == 1) { //case 1c
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);

                if(g->getBalance() == 1) {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if(g->getBalance() == -1) {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == -1) { //case 2
            n->setBalance(-1);
            return;
        }
        else if(n->getBalance() + diff == 0) { //case 3
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }

    else if(diff == 1) {
        if(n->getBalance() + diff == 2) { //case 1
            AVLNode<Key, Value>* c = n->getRight();

            if(c->getBalance() == 1) { //case 1a
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if(c->getBalance() == 0) { //case 1b
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            }
            else if(c->getBalance() == -1) { //case 1c
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);

                if(g->getBalance() == -1) {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 1) {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == 1) { //case 2
            n->setBalance(1);
            return;
        }
        else if(n->getBalance() + diff == 0) { //case 3
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* parent = NULL;
    AVLNode<Key, Value>* child = node ->getRight();

     //node has a parent
    if(node->getParent() != NULL) {
        parent = node->getParent();
    
        bool isLeft = false;

        if(parent->getLeft() == node) { 
            isLeft = true;
        }

        if(isLeft) { //node is left child
            parent->setLeft(child);
        }
        else if(!isLeft) { //node is right child
            parent->setRight(child);
        }    
    }
    else if(node->getParent() == NULL) { //child becomes root
        this->root_ = child;
    }

    child->setParent(parent);

    AVLNode<Key, Value>* left = NULL;
    if(child->getLeft() != NULL) {
        left = child->getLeft();
        left->setParent(node);
    }

    child->setLeft(node);
    node->setParent(child);

    node->setRight(left);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* parent = NULL;
    AVLNode<Key, Value>* child = node ->getLeft();

     //node has a parent
    if(node->getParent() != NULL) {
        parent = node->getParent();
    
        bool isLeft = false;

        if(parent->getLeft() == node) { 
            isLeft = true;
        }

        if(isLeft) { //node is left child
            parent->setLeft(child);
        }
        else if(!isLeft) { //node is right child
            parent->setRight(child);
        }    
    }
    else if(node->getParent() == NULL) { //child becomes root
        this->root_ = child;
    }

    child->setParent(parent);


    AVLNode<Key, Value>* right = NULL;
    if(child->getRight() != NULL) {
        right = child->getRight();
        right->setParent(node);
    }

    child->setRight(node);
    node->setParent(child);

    node->setLeft(right);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::zigzig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
    bool result = false;
    
    //left
    if(g->getLeft() == p) {
        if(p->getLeft() == n) {
            result = true;
        }
    }

    //right
    else if(g->getRight() == p) {
        if(p->getRight() == n) {
            result = true;
        }
    }
    return result;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::zigzag(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {

    bool result = false;
    
     //left then right
    if(g->getLeft() == p) {
        if(p->getRight() == n) {
            result = true;
        }
    }
    
    //right then left
    else if(g->getRight() == p) {
        if(p->getLeft() == n) {
            result = true;
        }
    }
    return result;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
