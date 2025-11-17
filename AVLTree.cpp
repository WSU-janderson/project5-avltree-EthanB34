#include "AVLTree.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <optional>
AVLTree::AVLNode::AVLNode(const KeyType& k, ValueType v) :
                                    key(k), value(v), height(0), left(nullptr), right(nullptr) {}
AVLTree::AVLTree() : root(nullptr) {}

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
size_t AVLTree::AVLNode::numChildren() const {
    size_t childCount = 0;
    if (left) childCount++;
    if (right) childCount++;
    return childCount;
}

bool AVLTree::AVLNode::isLeaf() const {
    return !left && !right;
}

size_t AVLTree::AVLNode::getHeight() const {
    return static_cast<size_t>(height);
}
int AVLTree::AVLNode::getBalance() const {
    int leftHeight = left ? left->height : -1;
    int rightHeight = right ? right->height : -1;
    return (leftHeight - rightHeight);
}
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
        current->height = 1+std::max(leftHeight, rightHeight);


        }
    balanceNode(current);
    return wasInserted;
    }



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


std::optional<AVLTree::ValueType> AVLTree::get(const KeyType& k) const {
    return get(root, k);
}
std::optional<AVLTree::ValueType>
AVLTree::get(const AVLNode *current, const KeyType &k) const {
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
AVLTree::ValueType& AVLTree::operator[](const KeyType& k) {
AVLNode* current = findOperator(root, k);
    if (!current) {
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

size_t AVLTree::size() const {
    return nodePairs;
}

size_t AVLTree::getHeight() const {
    return root ? root->height : 0;
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

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
   avlTree.printInorder(os, avlTree.root, 0);
    return os;
}
AVLTree::AVLTree(const AVLTree& other)
    :root(nullptr), nodePairs(0) {
root = clone(other.root);
    nodePairs = other.nodePairs;
}
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
void AVLTree::operator=(const AVLTree &other) {
if (this == &other) {
    return;
}
    clear(root);
    root = clone(other.root);

}



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
       // balanceNode(current);


        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    nodePairs--;
    return true;

}

bool AVLTree::remove(const KeyType& k) {
    return remove(root, k);
}
bool AVLTree::remove(AVLNode*& current,KeyType k) {
    if (!current) return false;
    if (k < current->key ) {
        bool removed = remove(current->left,k);
        if (removed) {
            updateHeight(current);
            balanceNode(current);
        }
        return removed;
    }
    else if (k > current->key) {
        bool removed = remove(current->right,k);
        if (removed) {
           updateHeight(current);
            balanceNode(current);
        }
        return removed;

    }
    else {
        bool removed = removeNode(current);
        if (current) {
           updateHeight(current);
            balanceNode(current);
        }

        return removed;

    }
}
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






void AVLTree::updateHeight(AVLNode *&current) {
    if (!current ) {
        return;
    }

        int leftHeight = current->left ? current->left->height : -1;
        int rightHeight = current->right ? current->right->height : -1;
        current->height = 1+std::max(leftHeight, rightHeight);
    }

AVLTree::AVLNode* AVLTree::rotateRight(AVLNode*& current) {

    AVLNode* newRoot = current->left;
    AVLNode* hookNode = newRoot -> right;

    newRoot -> right = current;
    current->left = hookNode;

    updateHeight(current);
    updateHeight(hookNode);
    return newRoot;
}
AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode*& current) {
    AVLNode* newRoot = current->right;
    AVLNode* hookNode = newRoot -> left;

    newRoot -> left = current;
    current->right = hookNode;
    updateHeight(current);
    updateHeight(hookNode);
    return newRoot;
}