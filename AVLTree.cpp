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
bool AVLTree::insert(const KeyType& k, ValueType v) {
    return insert(root, k, v);
}
bool AVLTree::insert(AVLNode*& current, const KeyType& k, ValueType v) {
    if (!current) {
        current = new AVLNode(k, v);
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

std::vector<AVLTree::KeyType> AVLTree::findRange(const KeyType& lowKey, const KeyType& highKey) const {
    return{};
}

std::vector<AVLTree::KeyType> AVLTree::keys() const {
    return{};
}
size_t AVLTree::size() const {
    return 0;
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

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
