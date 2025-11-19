/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

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
        size_t height = 0;

        AVLNode* left = nullptr;
        AVLNode* right = nullptr;


        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        size_t getHeight();
    };
public:

    AVLTree();
    ~AVLTree();
    bool insert(AVLNode*& current, KeyType key, ValueType value);
    bool insert(const std::string& key, size_t value);
    size_t size() const;
    size_t getHeight() const;
    void setHeight(AVLNode *current) const;
    //size_t getHeight(AVLNode *&current, size_t Height) const;
    friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
    bool contains(const std::string& key);
    optional<size_t> get(const std::string& key);
    optional<size_t> get(AVLNode* &current, const string& key);
    void OutputNodes(ostream& os, AVLNode *current, string Dir, size_t loops) const;
    vector<std::string> findRange(const std::string& lowKey, const std::string& highKey) const;
    size_t& operator[](const std::string& key);
    bool remove(const std::string& key);

    AVLNode* rightRotation(AVLNode* current);
    AVLNode* leftRotate(AVLNode* current);
    AVLNode* rightRotationDeletion(AVLNode* current);
    AVLNode* leftRotationDeletion(AVLNode* current);
    int getBalance(AVLNode* &current);
    void UpdateHeight(AVLNode* &current);
    bool ReplaceChild(AVLNode* &parent, AVLNode* currentChild, AVLNode* &newChild);
    bool SetChild(AVLNode* &parent, string whichChild, AVLNode* &child);



    private:
    int sizeOfSequence;
    AVLNode* root;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode *&node);

    AVLTree(const AVLTree& other);

    AVLTree& operator=(const AVLTree& other);
    AVLTree::AVLNode* copyInsert(AVLNode *&other);
    bool contains(AVLNode* &current, KeyType key);

    void clear();
    vector<std::string> keys();

    size_t getheight(AVLNode *&current, size_t Height) const;
    vector<std::string> keys(AVLNode *&current, vector<string> ST);
    void deleteNodes(AVLTree::AVLNode *&current);
    vector<std::string> findRange(const std::string& lowKey, const std::string& highKey, vector<string> V, AVLNode *current) const;

};

#endif //AVLTREE_H
