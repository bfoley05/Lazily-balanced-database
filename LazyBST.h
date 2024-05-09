#include <iostream>
#include "Student.h"
#include "Faculty.h"

using namespace std;

template <class T>
class TreeNode {
public:
    int key;
    T* data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode();
    TreeNode(T* d, int k);
    virtual ~TreeNode();
    int leftDepth;
    int rightDepth;
};

template <class T>
TreeNode<T>::TreeNode() {
    key = -1;
    data = T();
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T* d, int k) {
    key = k;
    data = d;
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode() {
    delete data;
    delete left;
    delete right;
}

template <class T>
class BST {
private:
    TreeNode<T>* root;
    int size;

public:
    BST();
    virtual ~BST();

    bool contains(int k);
    T* find(int k);
    void insert(TreeNode<T>* node); //Insert
    // void specialinsert(TreeNode<T>* node);

    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    bool remove(int k); //Delete
    // bool specialremove(int k);

    T* getMin();
    T* getMax();

    void printRecursive(TreeNode<T>* node);
    void printRecursivePost(TreeNode<T>* node);
    void printTree();

    TreeNode<T>* getRoot();
    int getSize();
    bool isEmpty();

    bool needsRotating();
    void rotate();
    int calculateDepth(TreeNode<T>* tempNode);
    TreeNode<T>** arr;
    void rotateHelper(TreeNode<T>* value);
    int index;
    TreeNode<T>* buildTreeFromArray(int start, int end);
    // void deleteTree();
    int leftHeight;
    int rightHeight;
};

template <class T>
BST<T>::BST() {
    root = NULL;
    size = 0;
    index = 0;
    leftHeight = 0;
    rightHeight = 0;
}

template <class T>
BST<T>::~BST() {
}

template<class T>
void BST<T>::rotate(){
    leftHeight = 0;
    rightHeight = 0;
    if(needsRotating()){
        arr = new TreeNode<T>*[size];
        index = -1;
        rotateHelper(root);
        // deleteTree();
        root = buildTreeFromArray(0, size - 1);

        delete[] arr;
        // printRecursivePost(root);
    }
}


// template<class T>
// void BST<T>::deleteTree() {
//     cout << "IN DELETE" << endl;
//     int start = 0;
//     int end = size - 1;
//     while (start <= end) {
//         if (arr[start] != nullptr) {
//             specialremove(arr[start]->key);
//             cout << arr[start]->key << " Removed" << endl;
//         }
//         if (start != end && arr[end] != nullptr) {
//             specialremove(arr[end]->key);
//             cout << arr[end]->key << " Removed" << endl;
//         }
//         ++start;
//         --end;
//     }
//     printTree();
// }




template<class T>
TreeNode<T>* BST<T>::buildTreeFromArray(int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    TreeNode<T>* newNode = arr[mid];
    // cout << "Inserted key: " << newNode->key << endl;
    newNode->left = buildTreeFromArray(start, mid - 1);
    newNode->right = buildTreeFromArray(mid + 1, end);
    return newNode;
}



template<class T>
void BST<T>::rotateHelper(TreeNode<T>* value){
    if(value == NULL){
        return;
    }
    rotateHelper(value->left);
    arr[++index] = value;
    // cout << "Added: " << arr[index]->key << " key to array" << endl;
    rotateHelper(value->right);
}

template<class T>
bool BST<T>::needsRotating(){
    if(root == nullptr){
        return false;
    }

    // Calculate the maximum depth of the left and right subtrees
    int leftDepth = calculateDepth(root->left);
    int rightDepth = calculateDepth(root->right);

    // Check if the difference between the maximum depths is more than 1.5
    if(abs(leftDepth - rightDepth) > 1.5){
        return true;
    }
    return false;
}

template<class T>
int BST<T>::calculateDepth(TreeNode<T>* tempNode){
    if(tempNode == nullptr){
        return 0;
    }
    int leftSubtreeDepth = calculateDepth(tempNode->left);
    int rightSubtreeDepth = calculateDepth(tempNode->right);
    
    // Update the depth of the current node
    tempNode->leftDepth = leftSubtreeDepth;
    tempNode->rightDepth = rightSubtreeDepth;

    // Return the depth of the subtree rooted at this node
    return 1 + max(leftSubtreeDepth, rightSubtreeDepth);
}

template <class T>
bool BST<T>::contains(int k) {
    if (root == NULL) {
        return false;
    }

    TreeNode<T>* curr = root;

    while (curr->key != k) {
        if (k < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr == NULL) {
            return false;
        }
    }
    return true;
}

template <class T>
T* BST<T>::find(int k) {
    if (root == NULL) {
        return NULL;
    }

    if (contains(k)) {
        TreeNode<T>* curr = root;

        while (curr->key != k) {
            if (k < curr->key) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }

            if (curr == NULL) {
                return NULL;
            }
        }
        return curr->data;
    } else {
        return NULL;
    }
}

// template <class T>
// void BST<T>::specialinsert(TreeNode<T>* node) {
//     // cout << "inserting: " << node->key << endl;
//     if (root == NULL) {
//         // cout << "\t ROOT HAS BEEN INSERTED" << endl;
//         root = node;
//     } else {
//         TreeNode<T>* curr = root;
//         TreeNode<T>* parent = NULL;

//         while (true) {
//             // cout << "root = " << (root ? to_string(root->key) : "NULL") << endl;
//             // cout << "node = " << (node ? to_string(node->key) : "NULL") << endl;
//             parent = curr;
//             if(node->key == curr->key){
//                 // cout << "how many " << endl;
//                 break;
//             }
//             if (node->key < curr->key) {
//                 // cout << "curr = " << (curr ? to_string(curr->key) : "NULL") << endl;
//                 node->leftDepth++;
//                 curr = curr->left;
//                 if (curr == NULL) {
//                     parent->left = node;
//                     break;
//                 }
//             } else if(node->key > curr->key){
//                 // cout << "curr = " << (curr ? to_string(curr->key) : "NULL") << endl;
//                 node->rightDepth++;
//                 // cout << "right: curr = " << (curr->right ? to_string(curr->right->key) : "NULL") << endl;
//                 curr = curr->right;
//                 if (curr == NULL) {
//                     parent->right = node;
//                     break;
//                 }
//             }else{
//                 break;
//             }
//         }
//     }
// }

template <class T>
void BST<T>::insert(TreeNode<T>* node) {
    if (root == NULL) {
        root = node;
    } else {
        TreeNode<T>* curr = root;
        TreeNode<T>* parent;

        while (true) {
            parent = curr;
            if (node->key < curr->key) {
                node->leftDepth++;
                curr = curr->left;
                if (curr == NULL) {
                    parent->left = node;
                    break;
                }
            } else {
                if (node->key > curr->key) {
                    node->rightDepth++;
                    curr = curr->right;
                    if (curr == NULL) {
                        parent->right = node;
                        break;
                    }
                }
            }
        }
    }
    ++size;
    rotate();
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d) {
    TreeNode<T>* sp = d;
    TreeNode<T>* successor = d;
    TreeNode<T>* curr = d->right;

    while (curr != NULL) {
        sp = successor;
        successor = curr;
        curr = curr->left;
    }

    if (successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }

    return successor;
}

// template <class T>
// bool BST<T>::specialremove(int k) {
//     if (root == NULL) {
//         return false;
//     }

//     TreeNode<T>* curr = root;
//     TreeNode<T>* parent = root;
//     bool isLeft = true;

//     while (curr->key != k) {
//         parent = curr;

//         if (k < curr->key) {
//             isLeft = true;
//             curr = curr->left;
//         } else {
//             isLeft = false;
//             curr = curr->right;
//         }

//         if (curr == NULL) {
//             return false;
//         }
//     }
//     //We have found the node we want to delete

//     //Delete a Node with No Children
//     if (curr->left == NULL && curr->right == NULL) {
//         if (curr == root) {
//             root = NULL;
//         } else if (isLeft) {
//             parent->left = NULL;
//         } else {
//             parent->right = NULL;
//         }
//     }
//     //One Child (to the Left)
//     else if (curr->right == NULL) {
//         if (curr == root) {
//             root = curr->left;
//         } else if (isLeft) {
//             parent->left = curr->left;
//         } else {
//             parent->right = curr->right;
//         }
//     }
//     //One Child (to the Right)
//     else if (curr->left == NULL) {
//         if (curr == root) {
//             root = curr->right;
//         } else if (isLeft) {
//             parent->left = curr->right;
//         } else {
//             parent->right = curr->right;
//         }
//     }
//     //Two Children
//     else {
//         TreeNode<T>* successor = getSuccessor(curr);

//         if (curr == root) {
//             root = successor;
//         } else if (isLeft) {
//             parent->left = successor;
//         } else {
//             parent->right = successor;
//         }
//         successor->left = curr->left;
//     }
//     return true;
// }

template <class T>
bool BST<T>::remove(int k) {
    if (root == NULL) {
        return false;
    }

    TreeNode<T>* curr = root;
    TreeNode<T>* parent = root;
    bool isLeft = true;

    while (curr->key != k) {
        parent = curr;

        if (k < curr->key) {
            isLeft = true;
            curr = curr->left;
        } else {
            isLeft = false;
            curr = curr->right;
        }

        if (curr == NULL) {
            return false;
        }
    }
    //We have found the node we want to delete

    //Delete a Node with No Children
    if (curr->left == NULL && curr->right == NULL) {
        if (curr == root) {
            root = NULL;
        } else if (isLeft) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }
    //One Child (to the Left)
    else if (curr->right == NULL) {
        if (curr == root) {
            root = curr->left;
        } else if (isLeft) {
            parent->left = curr->left;
        } else {
            parent->right = curr->right;
        }
    }
    //One Child (to the Right)
    else if (curr->left == NULL) {
        if (curr == root) {
            root = curr->right;
        } else if (isLeft) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
    }
    //Two Children
    else {
        TreeNode<T>* successor = getSuccessor(curr);

        if (curr == root) {
            root = successor;
        } else if (isLeft) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = curr->left;
    }
    --size;
    rotate();
    return true;
}

template <class T>
T* BST<T>::getMin() {
    TreeNode<T>* curr = root; //Start at root

    if (root == NULL) {
        return NULL;
    }

    while (curr->left != NULL) {
        curr = curr->left;
    }

    return curr;
}

template <class T>
T* BST<T>::getMax() {
    TreeNode<T>* curr = root;

    if (root == NULL) {
        return NULL;
    }

    while (curr->right != NULL) {
        curr = curr->right;
    }

    return curr;
}

template <class T>
void BST<T>::printRecursive(TreeNode<T>* node) {
    if (node == NULL) {
        // cout << "Tree is empty" << endl;
        return;
    }

    printRecursive(node->left);
    cout << node->key << endl;
    printRecursive(node->right);
}

template <class T>
void BST<T>::printRecursivePost(TreeNode<T>* node) {
    if (node == NULL) {
        // cout << "Tree is empty" << endl;
        return;
    }
    cout << node->key << endl;
    printRecursive(node->left);
    printRecursive(node->right);
}

template <class T>
void BST<T>::printTree() {
    printRecursive(root);
}

template <class T>
TreeNode<T>* BST<T>::getRoot() {
    return root;
}

template <class T>
int BST<T>::getSize() {
    return size;
}

template <class T>
bool BST<T>::isEmpty() {
    return (size == 0);
}
