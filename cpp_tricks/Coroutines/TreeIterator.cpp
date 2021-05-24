#include <iostream>
#include <stack>
#include "Generator.h"

struct Tree {
    int value;
    Tree *left {nullptr};
    Tree *right {nullptr};
    Tree(int value) : value {value} { }
    Tree(int value, Tree * left, Tree *right) : value {value}, left {left}, right {right} { }
};


// in-order traversal
Generator<Tree*> inOrderTraversal(Tree* root) {
    std::stack<Tree*> st;
    while (root) {
        st.push(root);
        root = root->left;
    }

    while (!st.empty()) {
        Tree* node {st.top()};
        st.pop();
        co_yield node;
        node = node->right;
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
}


int main() {
    Tree* root = new Tree(1);
    Tree *l1 = new Tree(2);
    Tree *l2 = new Tree(3);
    root->left = l1;
    root->right = l2;
    l2 = new Tree(4);
    l1->left = l2;
    for (auto nodePtr : inOrderTraversal(root)) {
        std::cout << nodePtr->value << " ";
    }
    std::cout << std::endl;
}
