#include "AVLTree.h"

#include <string>
#include <iostream>
#include <vector>
#include <optional>
AVLTree::AVLNode::AVLNode(const KeyType& k, ValueType v) :
                                    key(k), value(v), height(0), left(nullptr), right(nullptr) {}


size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}
bool AVLTree::insert(const KeyType& k, ValueType v) {
    return false;
}
bool AVLTree::contains(const KeyType& k) const {
    return false;
}
std::optional<AVLTree::ValueType> AVLTree::get(const KeyType& k) const {
    return std::nullopt;
}
AVLTree::ValueType& AVLTree::operator[](const KeyType& k) {

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

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
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
