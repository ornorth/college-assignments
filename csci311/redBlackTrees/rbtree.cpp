// rbtree.cpp 

#include <iostream>
#include <iomanip>
#include <string>
#include "rbtree.h"

using std::string;
using std::vector;

///////////////////////////////////////////////////////////////////////////////
///////CONSTRUCTORS\DESTRUCTORS////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  RBTree constructor
 *
 *  Initializes nil and points root at nil
 */
RBTree::RBTree()
{
    nil = new Node();
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
}

/**
 *  RBTree destructor
 *
 *  Calls a helper function to perform a post-order traversal
 *  Which will delete the entire tree
 */
RBTree::~RBTree()
{
    postOrderDelete(root);
    delete nil;
}

/**
 *  RBTree::postOrderDelete
 *
 *  @brief  deletes all the nodes in a red-black tree rooted at the given node
 *          by traveling through the tree recursively and deleting post-order
 *
 *  @param  toDelete the root of the tree to be deleted
 *  @return none
 */
void RBTree::postOrderDelete(Node* toDelete)
{
    //Base case - node is T.nil
    if (toDelete != nil)
    {
        postOrderDelete(toDelete->left);
        postOrderDelete(toDelete->right);
        delete toDelete;
    }
}

///////////////////////////////////////////////////////////////////////////////
///////PUBLIC FUNCTIONS////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  RBTree::rbInsert
 *
 *  @brief  inserts a new element into the tree at a position determined by key
 *          this function creates a Node, then calls a private function
 *
 *  @param  key     determines the element's placement in the tree
 *          value   satellite data attached to key
 *
 *  @return none
 */
void RBTree::rbInsert(const string& key, const string& value)
{
    Node* z = new Node(key, value);
    rbInsert(z);
}

/**
 *  RBTree::rbDelete
 *
 *  @brief  removes an element with given key and value from the r-b tree
 *          this function finds the Node to be deleted, 
 *          then calls a private function
 *
 *  @param  key     the key of the Node to be deleted
 *          value   the value of the Node to be deleted
 *  @return none
 */
void RBTree::rbDelete(const string& key, const string& value)
{
    //Find Node with matching key
    Node* z = root;
    while (z != nil)
    {
        if (*z->key == key)
            break;
        else if (*z->key < key)
            z = z->right;
        else
            z = z->left;
    }
    //Matching Node found
    if (z != nil)
    {
        //Find and delete all other instances with matching data
        Node* x = rbTreeSearch(z, value);
        while (x != nil && x != z)
        {
            rbDelete(x);
            x = rbTreeSearch(z, value);
        }
        //Delete original Node, if data matches
        if (*z->value == value)
        {
            rbDelete(z);
        }
    }
}

/**
 *  RBTree::rbFind
 *
 *  @brief  searches the tree for all nodes with matching key
 *          and returns a vector containing their satellite data
 *
 *  @param  key the key of the Nodes to be found
 *  @return vector of strings containing the satellite data of all valid Nodes
 *              (returns an empty vector if there are no matching Nodes)
 */
vector<const string*> RBTree::rbFind(const string& key)
{
    vector<const string*> data;
    Node* home = root;

    //Find matching Node
    while (home != nil)
    {
        if (*home->key == key)
            break;
        else if (*home->key < key)
            home = home->right;
        else
            home = home->left;
    }

    //Matching Node found
    if (home != nil)
    {
        //Add Node to vector
        data.push_back(home->value);

        //Add all matching predecessor Nodes to vector
        Node* x = rbTreePredecessor(home);
        while (x != nil)
        {
            if (*x->key == key)
            {
                data.push_back(x->value);
                x = rbTreePredecessor(x);
            }
            else break;
        }
        //Add all matching successor Nodes to vector
        x = rbTreeSuccessor(home);
        while (x != nil)
        {
            if (*x->key == key)
            {
                data.push_back(x->value);
                x = rbTreeSuccessor(x);
            }
            else break;
        }
    }

    return data;
}

/**
 *  RBTree::rbPrintTree
 *
 *  @brief  displays the red-black tree rooted at 'root' with simulated depth
 *          this function calls private function reverseInOrderPrint
 *
 *  @param  none
 *  @return none
 */
void RBTree::rbPrintTree()
{
    reverseInOrderPrint(root, 0);
}

///////////////////////////////////////////////////////////////////////////////
///////PRIVATE ACCESSORS///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  RBTree::rbTreeMinimum
 *
 *  @brief  returns the element with the smallest value in the tree rooted at z
 *
 *  @param  z   the root of the tree to find minimum
 *  @return a pointer to the Node whose key is the minimum in the tree
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* z)
{
    while (z->left != nil)  z = z->left;
    return z;
}

/**
 *  RBTree::rbTreeMaximum
 *
 *  @brief  returns the element with the largest value in the tree rooted at z
 *
 *  @param  z   the root of the tree to find maximum
 *  @return a pointer to the Node whose key is the maximum in the tree
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* z)
{
    while (z->right != nil)  z = z->right;
    return z;
}

/**
 *  RBTree::rbTreeSuccessor
 *
 *  @brief  returns a node's successor
 *
 *  @param  z   the node whose successor is to be found
 *  @return a pointer to the successor Node
 */
RBTree::Node* RBTree::rbTreeSuccessor(Node* z)
{
    //Node has a right subtree, return minimum of that subtree
    if (z->right != nil)
    {
        return rbTreeMinimum(z->right);
    }
    //Node has no right subtree, move up the tree until a right turn is taken
    Node* y = z->parent;
    Node* x = z;
    while (y != nil && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 *  RBTree::rbTreePredecessor
 *
 *  @brief  returns a node's predecessor
 *
 *  @param  z   the node whose predecessor is to be found
 *  @return a pointer to the predecessor Node
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* z)
{
    //Node has a left subtree, return maximum of that subtree
    if (z->left != nil)
    {
        return rbTreeMaximum(z->left);
    }
    //Node has no left subtree, move up the tree until a left turn is taken
    Node* y = z->parent;
    Node* x = z;
    while (y != nil && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 *  RBTree::rbTreeSearch
 *
 *  @brief  Searches for a Node with matching key and satellite data,
 *          Prioritizing Nodes other than the one passed to the function
 *
 *  @param  home Node, the Node whose predecessors and successors will be found
 *          value of the satellite data to be found
 *
 *  @return A pointer to the Node with matching key and satellite data,
 *          or T.nil if such a Node does not exist
 */
RBTree::Node* RBTree::rbTreeSearch(Node* home, const string& value)
{
    Node* predecessor = rbTreePredecessor(home);
    Node* successor = rbTreeSuccessor(home);

    //Search nearby nodes for matching data
    while (*predecessor->key == *home->key)
    {
        if (*predecessor->value == value) break;
        predecessor = rbTreePredecessor(predecessor);
    }
    while (*successor->key == *home->key)
    {
        if (*successor->value == value) break;
        successor = rbTreeSuccessor(successor);
    }
    //Return predecessor or successor, or home Node if neither is correct
    if (*predecessor->key == *home->key && *predecessor->value == value)
        return predecessor;
    if (*successor->key == *home->key && *successor->value == value)
        return successor;
    return home;
}

/**
 *  RBTree::reverseInOrderPrint
 *
 *  @brief  prints color, key, and value for each node in the tree
 *          in similar fashion to the standard visual representation of trees
 *          this is a recursive function that is called on each individual Node
 *
 *  @param  x       the node to be printed
 *          depth   used to simulate tree depth
 *  @return none
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
    if ( x != nil ) {
        reverseInOrderPrint(x->right, depth+1);
        std::cout << std::setw(depth*4+4) << x->color << " ";
        std::cout << *(x->key) << " " << *(x->value) << std::endl;
        reverseInOrderPrint(x->left, depth+1);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////PRIVATE MUTATORS////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  RBTree::leftRotate
 *
 *  @brief  rotates the tree left at the provided Node
 *
 *  @param  x   the Node about which the tree will be rotated
 *  @return none
 */
void RBTree::leftRotate(Node* x)
{
    Node* y = x->right;             //set y to right child
    x->right = y->left;             //x inherits y's left subtree
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;          //link x's parent to y
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;                    //put x on y's left
    x->parent = y;
}

/**
 *  RBTree::rightRotate
 *
 *  @brief  rotates the tree right at the provided Node
 *
 *  @param  x   the Node about which the tree will be rotated
 *  @return none
 */
void RBTree::rightRotate(Node* x)
{
    Node* y = x->left;              //set y to left child
    x->left = y->right;             //x inherits y's right subtree
    if (y->right != nil)            
        y->right->parent = x;
    y->parent = x->parent;          //link x's parent to y
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;                   //put x on y's right
    x->parent = y;
}

/**
 *  RBTree::rbInsertFixup
 *
 *  @brief  detects and corrects violations of r-b tree properties post-insert
 *
 *  @param  z   the inserted Node which may have violated r-b properties
 *  @return none
 */
void RBTree::rbInsertFixup(Node* z)
{
    while (z->parent->color == 'R')
    {
        if (z->parent == z->parent->parent->left)   //Cases 1-3
        {
            Node* y = z->parent->parent->right;     //Get uncle
            if (y->color == 'R')
            {
                z->parent->color = 'B';             //Case 1
                y->color = 'B';                     //Case 1
                z->parent->parent->color = 'R';     //Case 1
                z = z->parent->parent;              //Case 1
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;                  //Case 2
                    leftRotate(z);                  //Case 2
                }
                z->parent->color = 'B';             //Case 3
                z->parent->parent->color = 'R';     //Case 3
                rightRotate(z->parent->parent);     //Case 3
            }
        }
        else                                        //Cases 4-6 (mirrored)
        {
            Node* y = z->parent->parent->left;      //Get uncle
            if (y->color == 'R')
            {
                z->parent->color = 'B';             //Case 4
                y->color = 'B';                     //Case 4
                z->parent->parent->color = 'R';     //Case 4
                z = z->parent->parent;              //Case 4
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;                  //Case 5
                    rightRotate(z);                 //Case 5
                }
                z->parent->color = 'B';             //Case 6
                z->parent->parent->color = 'R';     //Case 6
                leftRotate(z->parent->parent);      //Case 6
            }
        }
    }
    root->color = 'B';
}

/**
 *  RBTree::rbDeleteFixup
 *
 *  @brief  detects and fixes violations of r-b tree properties post-delete
 *
 *  @param  x   the Node at which violations may have occurred
 *  @return none
 */
void RBTree::rbDeleteFixup(Node* x)
{
    while (x != root && x->color == 'B')
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'B';
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
            }
            else 
            {
                if (w->right->color == 'B')
                {
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node* w = x->parent->left;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'B';
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
            }
            else 
            {
                if (w->left->color == 'B')
                {
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 'B';
}

/**
 *  RBTree::rbTransplant
 *
 *  @brief  copies Node v into the place of Node u
 *
 *  @param  u   the Node to be replaced
 *          v   the Node to be copied
 *  @return none
 */
void RBTree::rbTransplant(Node* u, Node* v)
{
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

///////////////////////////////////////////////////////////////////////////////
///////PRIVATE OVERLOADED MUTATORS/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  RBTree::rbInsert
 *
 *  @brief  inserts a Node into the tree, then calls rbInsertFixup
 *          to preserve r-b tree properties
 *
 *  @param  z   the Node to be inserted
 *  @return none
 */
void RBTree::rbInsert(Node* z)
{
    Node* y = nil;
    Node* x = root;

    //Search for where to place z
    while (x != nil)
    {
        y = x;
        if (*z->key < *x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nil)              root = z;     //z is the only element - z = root
    else if (*z->key < *y->key) y->left = z;   //z is y's left child
    else                       y->right = z; //z is y's right child
    z->left = nil;
    z->right = nil;
    //z->color = 'R' implicit in construction of Node
    rbInsertFixup(z);
}

/**
 *  RBTree::rbDelete
 *
 *  @brief  removes a Node from the tree, then calls rbDeleteFixup
 *          to preserve r-b tree properties
 *  
 *  @param  z   the Node to be deleted
 *  @return none
 */
void RBTree::rbDelete(Node* z)
{
    Node* y = z;
    Node* x = nil;
    char ogColor = y->color;
    if (z->left == nil)
    {
        x = z->right;
        rbTransplant(z, z->right);
        delete z;
    }
    else if (z->right == nil)
    {
        x = z->left;
        rbTransplant(z, z->left);
        delete z;
    }
    else
    {
        y = rbTreeMaximum(z->left);
        ogColor = y->color;
        x = y->left;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }
        rbTransplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
        delete z;
    }
    if (ogColor == 'B')
    {
        rbDeleteFixup(x);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////NESTED NODE CLASS///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 *  Node default constructor
 *
 *  Used for instantiation of nil
 */
RBTree::Node::Node()
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    key = new string("");
    value = new string("");
    color = 'B';
}
/**
 *  Node overloaded constructor
 *
 *  Takes key and value as arguments
 *
 *  Defaults color to red
 */
RBTree::Node::Node(const string& key, const string& value)
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    this->key = new string(key);
    this->value = new string(value);
    color = 'R';
}

/** Node Destructor
 *
 */
RBTree::Node::~Node()
{
    delete key;
    delete value;
}
