/* Student Name: Ethan Barnes
 * Project 5: AVL Tree
 *
 *This file containts the AVLTree class and AVLNode methods/functions
 *
 * Functions (respective recursive helper in parenthesis):
 * Constructor, Desctructor(clear), Deep Copy Constructor(clone), insert(insert), contains(contains),  get(get) ,
 * operator=(findOperator),findRange(findRange, keys(keys), Size, getHeight, operator <<(printInorder), remove(remove),
 * removeNode, balanceNode, rotateLeft, rotateRight, updateHeight, isleaf, numChildren, getHeight, getBalance
 *A tree just contains the pointer to its root, whilst a node holds a key value pair, left and right pointers, and its height.
 *
 */
#include "AVLTree.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <optional>


AVLTree::AVLNode::AVLNode(const KeyType& k, ValueType v) :
                                    key(k), value(v), height(0), left(nullptr), right(nullptr) {}
AVLTree::AVLTree() : root(nullptr) {}

/*~AVLTree , destructor
 *uses clear as a recursive helper to traverse the tree and remove each node
 *
 */
AVLTree::~AVLTree() {
clear(root);
}

void AVLTree::clear(AVLNode*& current) {
    if (!current) return;
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;
}

/* numChildren
 *
 *returns a size_t, either 0,1,2 are the possiblities for the amount of children
 */
size_t AVLTree::AVLNode::numChildren() const {
    size_t childCount = 0;
    if (left) childCount++;
    if (right) childCount++;
    return childCount;
}
/* isLeaf
 *
 * returns true if the left and right pointers of a current node are null
 *
 */
bool AVLTree::AVLNode::isLeaf() const {
    return !left && !right;
}
/* getHeight
 *
 * returns a size_t, the height of the node
 *
 */
size_t AVLTree::AVLNode::getHeight() const {
    return static_cast<size_t>(height);
}
/* getBalance
 *
 * returns the balance of the current node, depending on its subchildrens height
 *
 */
int AVLTree::AVLNode::getBalance() const {
    int leftHeight = left ? left->height : -1;
    int rightHeight = right ? right->height : -1;
    return (leftHeight - rightHeight);
}


/* insert
 *
 * utilizes a recursive helper to do an insert based on the keys value and update its ancestors heights
 * returns a boolean depending on the status of insert completion
 * parameters: key reference, and value
 */
bool AVLTree::insert(const KeyType& k, ValueType v) {
    return insert(root, k, v);
}
bool AVLTree::insert(AVLNode*& current, const KeyType& k, ValueType v) {

    if (!current) {
        current = new AVLNode(k, v);
        nodePairs++;
        return true;

    }

    if (k == current->key) {
        return false;
    }

    bool wasInserted = false;
    if (k < current->key) {
        wasInserted = insert(current->left, k, v);

    } else {
        wasInserted = insert(current->right, k, v);
    }

    if (wasInserted) {
        int leftHeight = current->left ? current->left->height : -1;
        int rightHeight = current->right ? current->right->height : -1;
        //recursivly update ancestors
        current->height = 1+std::max(leftHeight, rightHeight);


        }
    balanceNode(current);
    return wasInserted;
    }


/* contains
 *
 * utilizes a recursive function to search the tree for the provided key
 * parameters: key reference
 */
bool AVLTree::contains(const KeyType& k) const {
    return contains (root, k);
}
bool AVLTree::contains(const AVLNode *current, const KeyType &k) const {
    if (!current) {
        return false;
    } else if (k == current->key) {
        return true;
    } else if (k < current->key) {
        return contains(current->left, k);
    }
    return contains(current->right, k);
    }


/* get
 *
 * similar to contains but returns the value found with the associated key, also using recursion
 *parameters: key reference
 */
std::optional<AVLTree::ValueType> AVLTree::get(const KeyType& k) const {
    return get(root, k);
}

std::optional<AVLTree::ValueType> AVLTree::get(const AVLNode *current, const KeyType &k) const {
    if (!current) {
        return std::nullopt;
    }
    if (k == current->key) {
        return current->value;
    }
    if (k < current->key) {
        return get(current->left, k);
    } else {
        return get(current->right, k);
    }
}

/* operator[] overload
 *
 * similar to get, but returns a reference allowing for value reassignment using recursion
 *
 * parameters: key reference
 */
AVLTree::ValueType& AVLTree::operator[](const KeyType& k) {
AVLNode* current = findOperator(root, k);
    if (!current) {
        //dummy return value, index out of bounds so do nothing
        static ValueType dummy = ValueType();
        return dummy;
    }
    return current->value;
}
AVLTree::AVLNode *AVLTree::findOperator(AVLNode *current, const KeyType &k) const {
    if (!current) {
        return nullptr;
    }
    if (k == current->key) {
        return current;
    }
    if (k < current->key) {
        return findOperator(current->left, k);
    }
    return findOperator(current->right, k);
}

/* findRange
 * creates a vector of values that lie within the given key range
 *
 * parameters - lowkey, highkey
 */
vector<size_t> AVLTree::findRange(const KeyType &lowKey, const KeyType &highKey) const {
    std::vector<ValueType> result;
    findRange(root, lowKey, highKey, result);
    return result;
}
void AVLTree::findRange(AVLNode* current,
                            const KeyType& lowKey,
                            const KeyType& highKey,
                            std::vector<ValueType> &result) const {
    if (!current) {
        return;
    }
    if (current->key > lowKey) {
        findRange(current->left, lowKey, highKey, result);
    }
    if (current->key >= lowKey && current->key <= highKey) {
        result.push_back(current->value);
    }
    if (current->key < highKey) {
        findRange(current->right, lowKey, highKey, result);
    }
}


/* keys
 *
 * uses recursion to create a vector of all keys in the current tree
 *
 */
std::vector<AVLTree::KeyType> AVLTree::keys() const {
std::vector<KeyType> result;
    keys(root, result);
    return result;
}
void AVLTree::keys(AVLNode *current, vector<KeyType> &result) const {
    if (!current) {
        return;
    }
    keys(current->left, result);
    result.push_back(current->key);
    keys(current->right, result);
}

/* size
 *
 * returns, the amount of key value pairs
 *
 */
size_t AVLTree::size() const {
    return nodePairs;
}
/* getHeight
 *
 * returns the height of the root node
 *
 */
size_t AVLTree::getHeight() const {
    return root ? root->height : 0;
}
/*
 * operator <<
 *
 *  does a right child first in order traversal to print the tree sideways
 *
 */
std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
    avlTree.printInorder(os, avlTree.root, 0);
    return os;
}
void AVLTree::printInorder(std::ostream& os, const AVLNode* current, int depth) const {
    if (!current) return;
    {
        printInorder(os, current->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            os <<"    ";
        }
        os << "{"  << current->key << ": " <<  current->value << "}" << std::endl;
        printInorder(os, current->left, depth + 1);
    }
}



/* deep copy contructor and operator =
 *clone the root of tree passed in to the new tree, and also assign nodePairs. result is a new independent tree using a
 *preorder traversal
 *
 * paramters: reference to other tree
 */
void AVLTree::operator=(const AVLTree& other) {
    if (this == &other) {
        return;
    }
    clear(root);
    root = clone(other.root);

}
AVLTree::AVLTree(const AVLTree& other)
    :root(nullptr), nodePairs(0) {
root = clone(other.root);
    nodePairs = other.nodePairs;
}
//clone each node
AVLTree::AVLNode* AVLTree::clone(const AVLNode* other) {
    if (!other) {
        return nullptr;
    }
    AVLNode* newNode = new AVLNode (other->key, other->value );
    newNode->height = other->height;


    newNode->left = clone(other->left);
    newNode->right = clone(other->right);
    return newNode;
}
/* removes the current node
 *
 * removes the given node and relinks the children/ ancestors
 * parameters - node pointer reference
 */
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
       balanceNode(current);


        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    nodePairs--;
    return true;

}

/* remove
 * returns true or false depending on if the removal failed or succeeded, and also rebalances the tree upon removal
 *
 * paramters- key reference
 */
bool AVLTree::remove(const KeyType& k) {
    return remove(root, k);
}
bool AVLTree::remove(AVLNode*& current,KeyType k) {
    if (!current) return false;
    bool removed = false;
    if (k< current-> key) {
        removed = remove(current->left, k);
    }
    else if (k > current->key) {
        removed = remove(current->right, k);
    } else {
        removed = removeNode(current);
    }
    if (!removed) return false;
    updateHeight(current);
    balanceNode(current);

        return removed;

    }

/* balanceNode
 *
 * calculates the balance of the current node and calls single or double rotations depending on the balance of the
 * hook/problem nodes
 *
 *pointers - node pointer reference
 */
void AVLTree::balanceNode(AVLNode*& node) {
    if (!node) {
        return;
    }

updateHeight(node);
    int bal = node->getBalance();
    if (bal >1 ) {
    int leftBal = node ->left ? node ->left->getBalance() : 0;
        if (leftBal >= 0 ) {
            node = rotateRight(node);
        } else {
            node -> left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    }
   else if (bal < -1) {
       int rightBal = node -> right ? node -> right ->getBalance() : 0;
       if (rightBal <= 0 ) {
           node = rotateLeft(node);
       } else {
           node -> right = rotateRight(node -> right);
           node = rotateLeft(node);
       }
   }
        }





/* update height
 * calculate the current nodes height
 *
 *parameters: node pointer reference
 */
void AVLTree::updateHeight(AVLNode*& current) {
    if (!current ) {
        return;
    }

        int leftHeight = current->left ? current->left->height : -1;
        int rightHeight = current->right ? current->right->height : -1;
        current->height = 1+std::max(leftHeight, rightHeight);
    }

/* rotateRight
 *
 * if the tree/subtree is found to be left heavy during balancing, then rotate right is called
 *
 *parameters - node pointer reference
 */
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode*& current) {

    AVLNode* newRoot = current->left;
    AVLNode* hookNode = newRoot -> right;

    newRoot -> right = current;
    current->left = hookNode;

    updateHeight(current);
    updateHeight(hookNode);
    return newRoot;
}
/* rotateLeft
 *
 *if the tree/subtree is found to be right heavy during balancing, then rotate left is called
 *
 *parameters - node pointer reference
 */
AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode*& current) {
    AVLNode* newRoot = current->right;
    AVLNode* hookNode = newRoot -> left;

    newRoot -> left = current;
    current->right = hookNode;
    updateHeight(current);
    updateHeight(hookNode);
    return newRoot;
}