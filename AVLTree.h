/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>
#include <optional>
#include <iostream>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;


        AVLNode(const KeyType &k, ValueType v);

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:

AVLTree();
AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);
    ~AVLTree();

    bool insert(const KeyType& k, ValueType v);
    bool remove(const KeyType& k);
    bool contains(const KeyType& k) const;
    std::optional<ValueType> get(const KeyType& k) const;
    size_t& operator[](const std::string& k);

    vector<string> findRange(const KeyType& lowKey,
                                     const KeyType& highKey) const;
    vector<string> keys() const;

    size_t size() const;
    size_t getHeight() const;



    private:
    AVLNode* root;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

};

#endif //AVLTREE_H
