#ifndef BST_H
#define BST_H
#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
    Node* root;

    Node* insert_helper(Node* root, int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            if (value < root->data) {
                root->left = insert_helper(root->left, value);
            } else {
                root->right = insert_helper(root->right, value);
            }
        }

        return root;
    }

    Node* copy_tree(const Node* otherRoot) {
        if (otherRoot == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(otherRoot->data);
        newNode->left = copy_tree(otherRoot->left);
        newNode->right = copy_tree(otherRoot->right);

        return newNode;
    }

    Node* search_helper(Node* root, int value) {
        if (root == nullptr) {
            return nullptr;
        } else {
            if (root->data == value) {
                return root;
            } else if (value < root->data) {
                return search_helper(root->left, value);
            } else {
                return search_helper(root->right, value);
            }
        }
    }

    Node* max_helper(Node* r) {
        if (r == nullptr) {
            return nullptr;
        } else if (r->right == nullptr) {
            return r;
        } else {
            return max_helper(r->right);
        }
    }

    Node* min_helper(Node* r) {
        if (r == nullptr) {
            return nullptr;
        } else if (r->left == nullptr) {
            return r;
        } else {
            return min_helper(r->left);
        }
    }

    void traverse_helper(Node* root) {
        if (root != NULL) {
            std::cout << root->data;
            traverse_helper(root->right);
            traverse_helper(root->left);
        }
    }

   public:
    BinarySearchTree() { root = nullptr; }

    BinarySearchTree(const BinarySearchTree& other) {
        root = copy_tree(other.root);
    }

    void insert(int x) { root = insert_helper(root, x); }

    void traverse() {
        std::cout << "travesing...";
        traverse_helper(root);
        std::cout << std::endl;
    }

    Node* search(int x) { return search_helper(root, x); }

    Node* min() { return min_helper(root); }

    Node* max() { return max_helper(root); }

    Node* successor(Node* start) {
        if (start == nullptr) {
            return nullptr;
        }
        if (start->right != nullptr) {
            return min_helper(start->right);
        } else {
            Node* parent = findParent(start);
            if (parent == nullptr) {
                return nullptr;
            } else {
                if (start == parent->left) {
                    return parent;
                } else {
                    return nullptr;
                }
            }
        }
    }

    Node* findParent(Node* start) {
        if (start == root) {
            return nullptr;
        }
        Node* temp = root;
        Node* parent = root;

        while (temp != start) {
            parent = temp;
            if (start->data < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        return parent;
    }

    void remove(Node* node) {
        if (node->left != nullptr && node->right != nullptr) {
            // P is pointing to a node that has
            // both a left and a right child

            Node* succ = successor(node);
            node->data = succ->data;
            remove(succ);
        }

        else if (node->left == nullptr && node->right == nullptr) {
            Node* parent = findParent(node);
            if (parent->left == node) {
                parent->left = nullptr;
            } else if (parent->right == node) {
                parent->right = nullptr;
            }
            delete node;
        }

        else if (node->left == nullptr && node->right != nullptr) {
            if (node == root) {
                Node* old = root;
                root = root->right;
                delete old;
            } else {
                Node* parent = findParent(node);
                if (parent->left == node) {
                    parent->left = node->right;
                    delete node;
                } else {
                    parent->right = node->right;
                    delete node;
                }
            }
        }

        else if (node->left != nullptr && node->right == nullptr) {
            if (node == root) {
                Node* old = root;
                root = root->left;
                delete old;
            } else {
                Node* parent = findParent(node);
                if (parent->left == node) {
                    parent->left = node->left;
                    delete node;
                } else {
                    parent->right = node->left;
                    delete node;
                }
            }
        }
    }

    // A function to display the tree graphically
    void displayTree(Node* r, int level, int direction) {
        // Don't worry about this function, just use it
        if (r != NULL) {
            displayTree(r->right, level + 1, 1);

            for (int i = 0; i < level - 1; i++) {
                std::cout << "   ";
            }
            if (level > 0) {
                if (direction == 1) {
                    std::cout << " /--";
                } else {
                    std::cout << " \\--";
                }
            }
            std::cout << r->data;
            std::cout << std::endl;
            level++;

            displayTree(r->left, level, -1);
        }
    }

    // Call the function to display the tree and leave some space afterwards
    void draw() {
        displayTree(root, 0, 0);
        std::cout << std::endl << std::endl;
    }
};

#endif