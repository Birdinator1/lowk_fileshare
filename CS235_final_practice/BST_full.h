#pragma once
#include <cstdlib>
#include <functional>


template <typename T>
class BST
{
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
    }

    ~BST() {
        clear();
    }

    bool insert(T const &item) {
        return insertHelper(root, item);
    }

    bool contains(T const &item) {
        return containsHelper(root, item);
    }

    bool remove(T const &item) {
        return removeHelper(root, item);
    }

    void inorder_traversal(std::function<void(T)> visit) const {
        inorderHelper(root, visit);
    }

    void preorder_traversal(std::function<void(T)> visit) const {
        preorderHelper(root, visit);
    }

    void postorder_traversal(std::function<void(T)> visit) const {
        postorderHelper(root, visit);
    }

    size_t size() const {
        return _size;
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
        _size = 0;
    }
private:
    Node* root;
    int _size;

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
        if (node == nullptr) return;
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

    void clearHelper(Node* node) {
        if (node == nullptr) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
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
            } else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } else {
                Node* prev = node->left;
                while (prev->right != nullptr) prev = prev->right;
                node->value = prev->value;
                removeHelper(node->left, prev->value);
                return true;
            }
            _size--;
            return true;
        }
    }
};
