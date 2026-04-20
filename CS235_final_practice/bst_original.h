#pragma once

#include <functional>

template<class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() {
        root = nullptr;
        _size = 0;
        // implement the constructor here
    }

    ~BST() {
        clear();
        // implement the destructor here
    }

    const Node* getRootNode() const {
        // implement getRootNode here
        // return a pointer to the tree's root node
        return root;
    }

    bool insert(T item) {
        // implement insert here
        // return true if item was inserted, false if item was already in the tree
        return insertHelper(root, item);
    }

    bool remove(T item) {
        // implement remove here
        // return true if item was removed, false if item wasn't in the tree
        return removeHelper(root, item);
    }

    bool contains(T item) const {
        // implement contains here
        // return true if item is in the tree, false otherwise
        return containsHelper(root, item);
    }

    void clear() {
        // implement clear here
        // remove all nodes from the tree
        clearHelper(root);
        root = nullptr;
        _size = 0;
    }

    int size() const {
        // implement size here
        // return the number of nodes in the tree
        return _size;
    }

    void inorder_traversal(std::function<void(T)> visit) const
    {
        inorderHelper(root, visit);
    }

    void preorder_traversal(std::function<void(T)> visit) const
    {
        preorderHelper(root, visit);
    }

    void postorder_traversal(std::function<void(T)> visit) const
    {
        postorderHelper(root, visit);
    }
private:
    Node* root;
    int _size;
    
    void clearHelper(Node* node) {
        if (node == nullptr) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

    bool insertHelper(Node*& node, T item) {
        if (node == nullptr) {
            node = new Node(item);
            _size++;
            return true;
        }
        if (item < node->value) return insertHelper(node->left, item);
        if (item > node->value) return insertHelper(node->right, item);
        return false;
    }

    bool removeHelper(Node*& node, T item) {
        if (node == nullptr) return false;
        if (item < node->value) return removeHelper(node->left, item);
        else if (item > node->value) return removeHelper(node->right, item);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            } else if  (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } else {
                Node* pred = node->left;
                while (pred->right != nullptr) pred = pred->right;
                node->value = pred->value;
                removeHelper(node->left, pred->value);
                _size++;
            }
            _size--;
            return true;
        }
    }

    bool containsHelper(Node* node, T item) const {
        if (node == nullptr) return false;
        if (item == node->value) return true;
        if (item < node->value) return containsHelper(node->left, item);
        return containsHelper(node->right, item);
    }

    void inorderHelper(Node* node, std::function<void(T)> visit) const {
        if (node == nullptr) return;
        inorderHelper(node->left, visit);
        visit(node->value);
        inorderHelper(node->right, visit);
    }

    void preorderHelper(Node* node, std::function<void(T)> visit) const {
        if (node ==nullptr) return;
        visit(node->value);
        preorderHelper(node->left, visit);
        preorderHelper(node->right, visit);
    }

    void postorderHelper(Node* node, std::function<void(T)> visit) const {
        if (node == nullptr) return;
        postorderHelper(node->left, visit);
        postorderHelper(node->right, visit);
        visit(node->value);
    }
};
