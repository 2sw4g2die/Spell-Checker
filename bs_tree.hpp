/*
* bs_tree.hpp
* Written by : Lana Cossettini (c3436542)
* Modified : 29/10/2023
*
* This class represents a templated binary search tree.
* This file is used in conjunction with Assignment 3 for SENG1120.
*/


#include "bs_tree.h"

template <typename T>
BSTree<T>::BSTree()
{
    root = nullptr;
    count = 0;
}

template <typename T>
BSTree<T>::~BSTree() {
    clear(root);
}


template <typename T>
void BSTree<T>::insert(const T& data) {
    root = insert(data, root); // Call recursive insert function starting from root
    count++;
}

template <typename T>
void BSTree<T>::remove(const std::string& key) {
    root = remove(key, root); // Call recursive remove function starting from root
    count--;
}

template <typename T>
bool BSTree<T>::contains(const std::string& key) const {
    return contains(key, root); // call recursive contains function
}

template <typename T>
T* BSTree<T>::find(const std::string& key) const {
    BTNode<T>* node = find(key, root);
    if (node) {
        return node->get_data(); //call recursive function
    }
    return nullptr;
}

//find minimum element in the search tree
template <typename T>
T& BSTree<T>::find_min() const {
    if (empty()) {
        throw empty_collection_exception("Tree is empty");
    }
    return find_min(root)->get_data();
}

//find maximum element in search tree
template <typename T>
T& BSTree<T>::find_max() const {
    if (empty()) {
        throw empty_collection_exception("Tree is empty");
    }
    return find_max(root)->get_data();
}

//check if tree is empty
template <typename T>
bool BSTree<T>::empty() const {
    return (root == nullptr);
}

//returns number of elements in tree
template <typename T>
int BSTree<T>::size() const {
    return count;
}


template <typename T>
void BSTree<T>::print_inorder(std::ostream& out) const {
    print_inorder(out, root); // calls recursive function 
}

template <typename T>
void BSTree<T>::print_preorder(std::ostream& out) const {
    print_preorder(out, root); // calls recursive function
}

template <typename T>
void BSTree<T>::print_postorder(std::ostream& out) const {
    print_postorder(out, root); // calls recursive function
}

//clears tree recursively starting from the root
template <typename T>
void BSTree<T>::clear(BTNode<T>* root) {
    if (root) {
        clear(root->get_left());  
        clear(root->get_right()); 
        delete root; 
    }
}

//inserts a new element into the tree
template <typename T>
BTNode<T>* BSTree<T>::insert(const T& data, BTNode<T>* node) {
    if (node == nullptr) {
        return new BTNode<T>(data); // creates new node if current is null
    }

    if (data < node->get_data()) {
        node->set_left(insert(data, node->get_left()));
    } else if (data > node->get_data()) {
        node->set_right(insert(data, node->get_right()));
    }

    return node;
}

// removes element with given key 
template <typename T>
BTNode<T>* BSTree<T>::remove(const std::string& key, BTNode<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->get_data().get_key()) {
        node->set_left(remove(key, node->get_left()));
    } else if (key > node->get_data().get_key()) {
        node->set_right(remove(key, node->get_right()));
    } else {
        // Node with only one or less children
        if (node->get_left() == nullptr) {
            BTNode<T>* temp = node->get_right();
            delete node;
            return temp;
        } else if (node->get_right() == nullptr) {
            BTNode<T>* temp = node->get_left();
            delete node;
            return temp;
        }

        // Node with two children
        BTNode<T>* temp = find_min(node->get_right());
        node->set_data(temp->get_data());
        node->set_right(remove(temp->get_data().get_key(), node->get_right()));
    }

    return node;
}

// check if tree contains element with given key
template <typename T>
bool BSTree<T>::contains(const std::string& key, BTNode<T>* node) const {
    if (node == nullptr) {
        return false;
    }

    if (key == node->get_data().get_key()) {
        return true;
    } else if (key < node->get_data().get_key()) {
        return contains(key, node->get_left());
    } else {
        return contains(key, node->get_right());
    }
}

// finds and returns pointer to element with given key
template <typename T>
BTNode<T>* BSTree<T>::find(const std::string& key, BTNode<T>* node) const {
    if (node == nullptr || key == node->get_data().get_key()) {
        return node;
    }

    if (key < node->get_data().get_key()) {
        return find(key, node->get_left());
    } else {
        return find(key, node->get_right());
    }
}

//finds and returns pointer to minimum element in the tree
template <typename T>
BTNode<T>* BSTree<T>::find_min(BTNode<T>* node) const {
    while (node->get_left() != nullptr) {
        node = node->get_left();
    }
    return node;
}

//finds and returns pointer to max element in the tree
template <typename T>
BTNode<T>* BSTree<T>::find_max(BTNode<T>* node) const {
    while (node->get_right() != nullptr) {
        node = node->get_right();
    }
    return node;
}

// prints tree in inorder traversal
template <typename T>
void BSTree<T>::print_inorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) {
        print_inorder(out, node->get_left());
        out << node->get_data() << " ";
        print_inorder(out, node->get_right());
    }
}

//prints tree in preorder traversal
template <typename T>
void BSTree<T>::print_preorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) {
        out << node->get_data() << " ";
        print_preorder(out, node->get_left());
        print_preorder(out, node->get_right());
    }
}

// prints tree in postorder traversal
template <typename T>
void BSTree<T>::print_postorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) {
        print_postorder(out, node->get_left());
        print_postorder(out, node->get_right());
        out << node->get_data() << " ";
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
    tree.print_inorder(out);
    return out;
}
