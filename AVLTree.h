/** Student Name: Ethan Barnes
*   Project 5: AVL Tree
 *
 *
 *This file contains the declarations of the AVLTree and AVLNode classes, the functions/methods appear in AVLTree.cpp
 *
 *
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

        /*Node Helper methods
         *
         *
         */
    //AVLNode methods
        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        // returns the balance of the node, in between -2, 2
        int getBalance() const;


    };

public:
//constructor/desctructors
AVLTree();
AVLTree(const AVLTree& other);
~AVLTree();

//operator overloads
void operator=(const AVLTree& other);
size_t& operator[](const std::string& k);
friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree);




//Tree builders
bool insert(const KeyType& k, ValueType v);
bool remove(const KeyType& k);
//tree accessors
bool contains(const KeyType& k) const;
std::optional<ValueType> get(const KeyType& k) const;




// vector builders
vector<size_t> findRange(const KeyType& lowKey,
                                     const KeyType& highKey) const;

vector<string> keys() const;



//tree info
size_t size() const;

size_t getHeight() const;



private:

    AVLNode* root;
    size_t nodePairs = 0;

    /*Inner tree recursive helper functions
     *needed for any function that makes recursive calls
     *
     */
    bool insert(AVLNode*& current, const KeyType& k, ValueType v);

    void printInorder(std::ostream& os, const AVLNode* current, int depth) const;

    bool contains(const AVLNode* current, const KeyType& k) const;

    std::optional<ValueType> get(const AVLNode* current, const KeyType& k) const;

    AVLNode* findOperator(AVLNode* current, const KeyType& k) const;

    AVLNode*clone (const AVLNode *other);

    void keys(AVLNode *current, vector<KeyType> &result) const;

    void clear(AVLNode*& root);

    void findRange (AVLNode* node,
        const KeyType& lowKey,
        const KeyType& highKey,
        std::vector<ValueType>& result) const;
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    //functions below pass node by reference, to allow root reassignment
    bool remove(AVLNode*& current, KeyType k);
    // removeNode contains the logic for actually removing a node based on the number of children
    bool removeNode(AVLNode*& current);
    //Tree Balancers
    void balanceNode(AVLNode*& node);
    AVLNode* rotateRight(AVLNode*& current);
    AVLNode* rotateLeft(AVLNode*& current);
    //recalculate current nodes height
    void updateHeight(AVLNode *&current);


};

#endif //AVLTREE_H
