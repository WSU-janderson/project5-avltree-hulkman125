/*
*Program
 *Written by
 *@Tyler
 *@Raymond
 *@Harvey
 */
/*
 * Project Name:
 *  Project 5: Map ADT: AvL Tree
 */
/*
 * Description:
 * Organizing nodes into
 * a tree-like structure
 * to quicken the
 * access time to
 * retrieve them.
 */



#include "AVLTree.h"

#include <iostream>
#include <optional>
#include <string>

int sizeOfSequence;

//----------------------------------------------------------------
//    numChildren: retriving the number of children
//    Returns:  size_t
//    Parameters: current (AVLNode*&)
//----------------------------------------------------------------
size_t AVLTree::AVLNode::numChildren() const {
    size_t NC = 0;
    if (left != nullptr) {
        NC++;
    }
    if (right != nullptr) {
        NC++;
    }
    return NC;
}

//----------------------------------------------------------------
//    isLeaf: checking if node has an children
//    Returns:  bool
//    Parameters: none
//----------------------------------------------------------------
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    return false;

}

//----------------------------------------------------------------
//    getHeight: retrieving the number of nodes in the tree
//    Returns:  size_t
//    Parameters: none
//----------------------------------------------------------------
size_t AVLTree::getHeight() const {
    if(root == nullptr) {
        return -1;
    }
    //return getHeight(root); // how to fix syntax error here
    return root->height;
}


//----------------------------------------------------------------
//    getHeight: retrieving the height of the node
//    Returns:  size_t
//    Parameters: none
//----------------------------------------------------------------
size_t AVLTree::AVLNode::getHeight() {
    return height;
}

//----------------------------------------------------------------
// removeNode: removing the node from the tree
//    Returns:  bool
//    Parameters: *current (AVLNode*&)
//----------------------------------------------------------------
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }
    sizeOfSequence--;

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

//----------------------------------------------------------------
// remove: accessing the remove method with 2 parameters
//    Returns:  bool
//    Parameters: key (string&)
//----------------------------------------------------------------
bool AVLTree::remove(const std::string& key){
    bool Q = remove(root, key);
    balanceNode(root);
    return Q;
}
AVLTree::AVLNode* AVLTree::rightRotationDeletion(AVLNode* current) {

    return current;
}

//----------------------------------------------------------------
//    remove: deleting a node from the tree
//    Returns:  bool
//    Parameters: *&current (AVLNode), key(KeyType)
//----------------------------------------------------------------
bool AVLTree::remove(AVLNode *&current, KeyType key) {

    bool Q;

    if(current == nullptr) {
        return false;
    }
    else if(current->key == key) {
        removeNode(current);
        return true;
    }
    else if(current->key > key) {
        Q = remove(current->left, key);
    }
    else if(current->key < key) {
        Q = remove(current->right, key);
    }

    if (Q == true) {
        balanceNode(current);
    }



    //setting the height of each node/////////////////////////////
    int leftHeight = -1;
    int rightHeight = -1;
    if (current != nullptr) {
        if (current->left != nullptr) {
            leftHeight = current->left->height;
        }
        if (current->right != nullptr) {
            rightHeight = current->right->height;
        }
        current->height = max(leftHeight, rightHeight) + 1;
        //time complexity is O(1)/////////////////////////////////////
    }
    return Q;
}


///////////////////ADDED ROTATION METHODS FOR FRIDAY///////////////////
/*
 */

//----------------------------------------------------------------
//    rightRotation: rotating the node to the right to maintain balance
//    Returns:  AVLNode*
//    Parameters: current (AVLNode)
//----------------------------------------------------------------
AVLTree::AVLNode* AVLTree::rightRotation(AVLNode* current) {


    if (current->left->left != nullptr && current->left->right == nullptr) {
        AVLNode* hook = current->left;
        AVLNode* temp = hook->right;
        //the actual rotation
        hook->right = current;
        //current->left = hook;
        current->left = temp;
        current->height = current->getHeight();
        current = hook;
        return current;
    }

    if (current->right != nullptr) {
        if (getBalance(current->right) == 1) {
            AVLNode* temp = current->right->left;
            current->left = temp;
            current->right->left = nullptr;
            return current;
        }
        if (getBalance(current->right) == -1) {
            AVLNode* temp = current->left->left;
            current->right = current->left->left;
            current->left->left = nullptr;
            return current;
        }
    }


        return current;
}

//----------------------------------------------------------------
//    LeftRotation: rotating the node to the left to maintain balance
//    Returns:  AVLNode*
//    Parameters: current (AVLNode*)
//----------------------------------------------------------------
AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* current) {
    if (current->right->right != nullptr && current->right->left == nullptr) {
        //delcaring the nodes
        AVLNode* hook = current->right;
        AVLNode* temp = hook->left;
        //doing the actual rotation
        hook->left = current;
        //current->right = hook;
        current->right = temp;
        current->height = current->getHeight();//testing
        current = hook;
        return current;
    }
    else if (current->left == nullptr && current->right->left != nullptr && current->right->right == nullptr) {
        AVLNode* temp = current->right->left;
        AVLNode* temp2 = current;
        current = current->right;
        current->right = temp;
        current->left = temp2;
        temp2->left = nullptr;
        temp2->right = nullptr;
    }
        return current;
}

//----------------------------------------------------------------
//    getBalance: getting the balace of the node
//    Returns:  int*
//    Parameters: &current (AVLNode*)
//----------------------------------------------------------------

int AVLTree::getBalance(AVLNode* &current) {
    int leftHieght = -1, rightHieght = -1;
    if (current->left != nullptr)
        {leftHieght = current->left->height;}
    if (current->right != nullptr)
        {rightHieght = current->right->height;
        return leftHieght - rightHieght;}
}

//----------------------------------------------------------------
//    UpdateHeight: giving the node its proper height
//    Returns:  void
//    Parameters: &current (AVLNode*)
//----------------------------------------------------------------

void AVLTree::UpdateHeight(AVLNode* &current) {
    int leftHieght = -1, rightHieght = -1;
    if (current->left != nullptr)
        {leftHieght = current->left->height;}
    if (current->right != nullptr)
        {rightHieght = current->right->height;}
    current->height = max(leftHieght, rightHieght) + 1;
}/*
bool AVLTree::ReplaceChild(AVLNode* &parent, AVLNode* currentChild, AVLNode* &newChild) {
    if (parent->left == currentChild)
        {return SetChild(parent, "left", newChild);}
    else if (parent->right == currentChild)
        {return SetChild(parent, "right", newChild);}
    return false;
}

bool AVLTree::SetChild(AVLNode* &parent, string whichChild, AVLNode* &child) {
    if (whichChild != "left" && whichChild != "right")
        {return false;}
    if (whichChild == "left")
        {parent->left = child;}
    else
        {parent->right = child;}
    if (child != nullptr)
        {child = parent;}
    UpdateHeight(parent);
    return true;
}
/*void RotateRight(AVLTree tree, AVLNode* &node) {
    AVLNode* leftRightChild = node->left->right;
    if (node->parent != nullptr) {
        ReplaceChild(node->parent, node, node->left);
    }
    else {
        tree->root = node->left;
        node->left->parent = nullptr;
    }
    SetChild(node->left, "right", node);
    SetChild(node, "left", leftRightChild);
}
*/

/////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------
//    balanceNode: checking to see if node is out of balance and if so, sets balance
//    Returns:  void
//    Parameters: *&node (AVLNode)
//----------------------------------------------------------------
void AVLTree::balanceNode(AVLNode *&node) {
    //this function should check the balance of *&node and then if out of balance, it should do the rotation

    int leftHieght;
    int rightHieght;
    if (node == nullptr) {
        return;
    }
    if (node != nullptr && node->left != nullptr) {
        leftHieght = node->left->height;
    }else{leftHieght = -1;}
    if (node != nullptr && node->right != nullptr) {
        rightHieght = node->right->height;
    }else{rightHieght = -1;}

    if ((leftHieght) == (rightHieght)) {
        return;
    }
    if ((leftHieght)  > (rightHieght)) {
    // checking to see if the height of the leftNode is greater than the height of the rightNode
        if (node->left != nullptr && node->right == nullptr) {

            node = rightRotation(node);
        }
    }
    if (static_cast<int>(leftHieght) < static_cast<int>(rightHieght)) {
    // checking to see if the height of the leftNode is less than the height of the rightNode
        if (node->right != nullptr && node->left == nullptr) {
            node = leftRotate(node);
        }
    }
    //testing if the height will work here
    balanceNode(node->left);
    balanceNode(node->right);
}

//new methods

//----------------------------------------------------------------
//    contains: checking if a node in the tree has the specified key
//    Returns:  bool
//    Parameters: key (string&)
//----------------------------------------------------------------

bool AVLTree::contains(const std::string& key) {
    if(sizeOfSequence == 0) {
        return false;
    }
    else{
        return contains(root, key);
    }
}

//----------------------------------------------------------------
//    get: accessing the get method with 2 parameters
//    Returns:  optional<size_t>
//    Parameters: key (string&)
//----------------------------------------------------------------
optional<size_t> AVLTree::get(const std::string& key) {
    if(sizeOfSequence == 0) {
        return -1;
    }
    return get(root, key);
}

//----------------------------------------------------------------
//    get: returning the value of a specific node
//    Returns:  optional<size_t>
//    Parameters: &current (AVLNode*), key (string&)
//----------------------------------------------------------------
std::optional<size_t>  AVLTree::get(AVLNode* &current, const string& key) {
    if(current == nullptr) {
        return 0;
    }
    if(current->key == key) {
        return current->value;
    }
    if(current->key > key) {
        return get(current->left, key);
    }
    if(current->key < key) {
        return get(current->right, key);
    }
    //return 0;
}

//----------------------------------------------------------------
//    AVLTree: default constructor
//    Returns:  none
//    Parameters: none
//----------------------------------------------------------------
AVLTree::AVLTree() {
    root = nullptr;
    sizeOfSequence = 0;
}

//----------------------------------------------------------------
//    AVLTree: copy constructor to call the copyInsert method
//    Returns:  none
//    Parameters: other (AVLTree&)
//----------------------------------------------------------------
AVLTree::AVLTree(const AVLTree& other) {
    root = new AVLNode(other.root->key, other.root->value);
	copyInsert(root);
	sizeOfSequence = other.sizeOfSequence;
}

//----------------------------------------------------------------
//    copyInsert: copy each node to the new tree by using recursion
//    Returns:  AVLNode*
//    Parameters: *&other (AVLTree)
//----------------------------------------------------------------
AVLTree::AVLNode* AVLTree::copyInsert(AVLNode *&other){ // self me funtion for the cop constructor
	if(other == nullptr) {
		return nullptr;
	}

	AVLNode* newNode = new AVLNode(other->key, other->value);
	newNode->left = copyInsert(other->left);
	newNode->right = copyInsert(other->right);
	return newNode;
}
//----------------------------------------------------------------
//    operator=: returns the value in a node and allows referencing to alter it
//    Returns:  AVLTree
//    Parameters: other (AVLTree&)
//----------------------------------------------------------------
AVLTree& AVLTree::operator=(const AVLTree& other) {
    clear();
    AVLNode* tempNode = new AVLNode(other.root->key, other.root->value);
    //AVLNode* tempNode = other.root;
    copyInsert(tempNode);
    return *this;
}

//----------------------------------------------------------------
//    ~AVLTree: destructor
//    Returns:  none
//    Parameters: none
//----------------------------------------------------------------
AVLTree::~AVLTree() {
	clear();
}

//----------------------------------------------------------------
//    insert: calls the insert method with 3 parameters
//    Returns:  bool
//    Parameters: key (string&), value (size_t)
//----------------------------------------------------------------
bool AVLTree::insert(const std::string& key, size_t value) {
    if (sizeOfSequence == 0) {
        root = new AVLNode(key, value);
        sizeOfSequence++;
        root->height = 0;
        return true;
    }
    return insert(root, key, value);
}

//----------------------------------------------------------------
//    OutputNodes: outputs the key and value of each node
//    Returns:  void
//    Parameters: os (ostream&), *current (AVLNode), Num (size_t), loops (size_t)
//----------------------------------------------------------------
void AVLTree::OutputNodes(ostream& os, AVLNode *current, string Dir, size_t loops) const {
    if (current == nullptr) {
        return;
    }
    if (loops == 0) {
        os << "--------{" << current->key << ": " << current->value << "}---------\n";
    }
    else if (Dir == "right") {
        os << "--------------{" << current->key << ": " << current->value << "}--------------\n";
    }
    else if (Dir == "left") {
        os << "--{" << current->key << ": " << current->value << "}--\n";
    }
    OutputNodes(os, current->left, "left", 1);
    OutputNodes(os, current->right, "right", 1);
}

//----------------------------------------------------------------
//    operator<<: calls the OutputNodes to output each node
//    Returns:  ostream&
//    Parameters: os (ostream&), tree (AVLTree&)
//----------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
    tree.OutputNodes(os, tree.root, "", 0); // how to fix this syntax error
    return os;
}



//----------------------------------------------------------------
//    insert: adds a new node to the tree using recursion
//    Returns:  bool
//    Parameters: &current (AVLNode*), key (KeyType), value (ValueType)
//----------------------------------------------------------------
bool AVLTree::insert(AVLNode* &current, KeyType key, ValueType value) {
    bool Q = true;
    if (current == nullptr) {
        current = new AVLNode(key, value);
        sizeOfSequence++;
        return true;
    }
    if(current->key == key) {
        return false;
    }

    if(current->key > key) {
        Q = insert(current->left, key, value);
        //return Q;
    }
    if(current->value < value) {

        Q = insert(current->right, key, value);
        //return Q;
    }
    if (Q == true) {
        //setting the height of each node/////////////////////////////
        int leftHeight = -1;
        int rightHeight = -1;
        if (current->left != nullptr) {
            leftHeight = current->left->height;
        }
        if (current->right != nullptr) {
            rightHeight = current->right->height;
        }
        current->height = max(leftHeight, rightHeight) + 1;
        //time complexity is O(1)/////////////////////////////////////
        balanceNode(current);

    }
    return Q;
}

//----------------------------------------------------------------
//    contains: checking to see if a node with a specific key is in the tree
//    Returns:  bool
//    Parameters: &current (AVLNode*),  key (KeyType)
//----------------------------------------------------------------
bool AVLTree::contains(AVLNode* &current, KeyType key) {
        if(current == nullptr) {
            return false;
        }
        if(current->key == key) {
            return true;
        }
        else if(current->key < key) {
            return contains(current->left, key);
        }
        else if(current->key > key) {
            return contains(current->right, key);
        }
}

//----------------------------------------------------------------
//    operator[]: returning the key of a specific node
//    Returns:  size_t&
//    Parameters: key (string&)
//----------------------------------------------------------------
size_t& AVLTree::operator[](const std::string& key) {
    if(sizeOfSequence == 0) {
        //return 0;
        throw exception();
    }
    //return get(key);
    if (root->key == key) {
        return root->value;
    }
    AVLNode* temp = root;
    while (temp != nullptr) {
        if (temp->key > key) {
            temp = temp->left;
            if (temp->key == key) {
                return temp->value;
            }
        }
        if (temp->key < key) {
            temp = temp->right;
            if (temp->key == key) {
                return temp->value;
            }
        }
    }
}

//----------------------------------------------------------------
//    findRange: accessing the findRange method with 4 methods
//    Returns:  vector<std::string>
//    Parameters: lowKey (string&), highKey (string&),
//----------------------------------------------------------------
vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {
    vector<string>Range;
    Range = findRange(lowKey, highKey, Range, root);
    return Range;
}

//----------------------------------------------------------------
//    findRange: creating a vector to store the values in a range by using recursionn
//    Returns:  vector<std::string>
//    Parameters: lowKey (string&), highKey (string&), V (vector<string>), *current (AVLNode)
//----------------------------------------------------------------
vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey, vector<string> V, AVLNode *current) const {
    if (current == nullptr) {
        return V;
    }
    if (current->key >= lowKey && current->key <= highKey) {
        V.push_back(std::to_string(current->value));
    }
    V = findRange(lowKey, highKey, V, current->left);
    V = findRange(lowKey, highKey, V, current->right);
    return V;
}

//----------------------------------------------------------------
//    keys: accessing the keys method with 2 parameters
//    Returns:  vector<std::string>
//    Parameters: none
//----------------------------------------------------------------
std::vector<std::string> AVLTree::keys()  {
	vector<string>nds;
	nds.resize(sizeOfSequence);
	return keys(root, nds);
}

//----------------------------------------------------------------
//    size: returning the number of nodes in the tree
//    Returns:  size_t
//    Parameters: none
//----------------------------------------------------------------
size_t AVLTree::size() const {
    return sizeOfSequence;
}

//----------------------------------------------------------------
//    keys: making a vector of all the keys in the treee
//    Returns:  vector<std::string>
//    Parameters: *&current (AVLNode), ST (vector<string>)
//----------------------------------------------------------------
 std::vector<std::string> AVLTree::keys(AVLNode *&current, vector<string> ST){ // self made function
	if(current == nullptr) {
		return ST;
	}
    ST.push_back(current->key);
	keys(current->left, ST);
	keys(current->left, ST);
    return ST;
}
//----------------------------------------------------------------
//    clear: accessing the deletNodes method
//    Returns:  void
//    Parameters: *&current (AVLNode)
//----------------------------------------------------------------
void AVLTree::clear() { //self made function
    if (sizeOfSequence == 0) {
        return;
    }
		deleteNodes(root);

    sizeOfSequence = 0;
}

//----------------------------------------------------------------
//    deleteNodes: eliminating all the nodes in the tree by using recursion
//    Returns:  void
//    Parameters: *&current (AVLNode)
//----------------------------------------------------------------
void AVLTree:: deleteNodes(AVLTree::AVLNode *&current) { //self-made function for the previous
    if (current == nullptr) {
        return;
    }
	if(current->left == nullptr && current->right == nullptr) {
		delete current;
		return;
	}
	deleteNodes(current->left);
	deleteNodes(current->right);
}

