#include "AVLTree.h"

#include <string>

size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
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

 bool AVLTree::remove(const std::string& key){
	remove(root, key);
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    if(current == nullptr) {
        return false;
    }
    else if(current->key == key) {
        sizeOfSequence--;
        delete current;
        return true;
    }
    else if(current->key < key) {
        return remove(current->left, key);
    }
    else if(current->key > key) {
        return remove(current->right, key);
    }
}

void AVLTree::balanceNode(AVLNode *&node) {
}





//new methods
bool AVLTree::insert(const std::string& key, size_t value) {
    if (sizeOfSequence == 0) {
            root = new AVLNode(key, value);
            sizeOfSequence++;
            return true;
    }
    else{
        return insert(root, key, value);
    }
}

bool AVLTree::remove(KeyType key) {
    if(sizeOfSequence == 0) {
        return false;
    }
    else{
        return remove(root, key);
    }
}

bool AVLTree::contains(const std::string& key) {
    if(sizeOfSequence == 0) {
        return false;
    }
    else{
        return contains(root, key);
    }
}

std::optional<size_t> AVLTree::get(const std::string& key) {
    if(sizeOfSequence == 0) {
        return "-1";
    }
    return get(root, key);
}







size_t AVLTree::getHeight(AVLNode *&current) const { //different getHeight method
    int l = 0
    int r = 0;
    int h = 1;
    if(left && current->left){
        l = getHeight(current->left);
    }
    if(right && current->right){
        r = getHeight(current->right);
    }
    if(l > r){
        return h + l;
    }
    return h + r;
}


AVLTree::AVLTree(const AVLTree& other) {
	root = other.root;
	copyInsert(root);
	sizeOfSequence = other.sizeOfSequence;
}
ALTree AVLNode*::copyInsert(AVLNode *&other){ // self me funtion for the cop constructor
	if(other == nullptr) {
		return nullptr;
	}

	AVLNode* newNode = new AVLNode(other->key, other->value);



	newNode->left = copyInsert(other->left);
	newNode->right = copyInsert(other->right);
	return newNode;
}


AVLTree& AVLTree::operator=(const AVLTree& other) {

}

AVLTree::~AVLTree() {
	clear();
}

friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {

}






bool AVLNode* AVLTree::insert(AVLNode* &current, KeyType key, ValueType value) {
	if(current.value == value) {
		return false;
	}
	if(current == nullptr) {
		current = new AVLNode(key, value);
		sizeOfSequence++;
		return true;
	}
    if(current < value) {
        sizeOfSequence++;
         return insert(current->left, key, value);
    }
    else if(current > value) {
        sizeOfSequence++;
        return insert(current->right, key, value);
    }
}



bool AVLNode* AVLTree::contains(AVLNode* &current, KeyType key) {
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

std::optional<size_t> AVLNode* AVLTree::get(AVLNode* &current, KeyType key) {
    if(current.key == key) {
        return current.value;
    }
	if(current == nullptr) {
		return "-1";
	}
    else if(current->key < key) {
        return get(current->left, key);
    }
    else if(current->key > key) {
        return get(current->right, key);
    }
}

std::string& AVLTree::operator[](const std::string& key) {
    if(sizeOfSequence == 0) {
        return "-1";
    }
    return get(root, key);
}

vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {
    vector<string>Range;
    for(int x = int(lowKey); x <= int(highKey); x++) {
        Range.push_back(char(x));
    }
}

std::vector<std::string> AVLTree::keys() const {
	vector<string>nds;

	nds.resize(sizeOfSequence);


	return keys(root, nds);

}



size_t AVLTree::size() const {
    return sizeOfSequence;
}

size_t AVLTree::getheight() const {
    int l = 0
    int r = 0;
    int h = 1;
    if(root == nullptr) {
		return -1;
	}
	return getheight(root, 0);

}

size_t AVLTree::getheight(AVLNode *&current, Height) const { // self made function
	if(current.left == nullptr && current.right == nullptr) {
		return -1
	}
	return getheight(current->left, Height + 1) - getheight(current->right, Height + 1);
}

 std::vector<std::string> AVLTree::keys(AVLNode *&current, vector<string> ST){ // self made function
	if(current == nullptr) {
		return ST;
	}
	return keys(current->left, ST);
	ST.push_back(current->key);
	return keys(current->left, ST);
}

void Sequence::clear() { //self made function
    SequenceNode* current = root;

    while (current != nullptr) {
		deleteNodes(current);
        /*SequenceNode* nextToDie = current->next;
        delete current;
        current = nextToDie;*/
    }


    sizeOfSequence = 0;
}

void deleteNodes(AVLNode *&current) { //self made function for the previous
	if(current.left != nullptr && current.right != nullptr) {
		delete current;
		return;
	}
	deleteNodes(current->left);
	deleteNodes(current->right);


}
