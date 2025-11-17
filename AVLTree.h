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
        int height;

        AVLNode* left;
        AVLNode* right;


        AVLNode(const KeyType &k, ValueType v);

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        int getBalance() const;


    };

public:

AVLTree();
AVLTree(const AVLTree& other);

    AVLNode *clone(const AVLNode *other);



    void operator=(const AVLTree& other);
    ~AVLTree();

    bool insert(const KeyType& k, ValueType v);
    bool remove(const KeyType& k);
    bool contains(const KeyType& k) const;
    std::optional<ValueType> get(const KeyType& k) const;
    size_t& operator[](const std::string& k);
friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree);
    vector<size_t> findRange(const KeyType& lowKey,
                                     const KeyType& highKey) const;
    vector<string> keys() const;

    void keys(AVLNode *current, vector<KeyType> &result) const;

    size_t size() const;

    size_t getHeight() const;



private:
    AVLNode* root;
    size_t nodePairs = 0;
    bool insert(AVLNode*& current, const KeyType& k, ValueType v);
    void printInorder(std::ostream& os, const AVLNode* current, int depth) const;
    bool contains(const AVLNode* current, const KeyType& k) const;
    std::optional<ValueType> get(const AVLNode* current, const KeyType& k) const;
    AVLNode* findOperator(AVLNode* current, const KeyType& k) const;
    void clear(AVLNode*& root);
    void findRange (AVLNode* node,
        const KeyType& lowKey,
        const KeyType& highKey,
        std::vector<ValueType>& result) const;
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType k);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

    void updateHeight(AVLNode *&current);

    AVLNode* rotateRight(AVLNode*& current);
    AVLNode* rotateLeft(AVLNode*& current);
};

#endif //AVLTREE_H
