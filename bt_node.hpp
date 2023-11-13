/*
* bt_node.hpp
* Written by : Lana Cossettini (c3436542)
* Modified : 29/10/2023
*
* This class represents a templated binary tree node.
* This file is used in conjunction with Assignment 3 for SENG1120.
*/

#include "bt_node.h"

template <typename T>
BTNode<T>::BTNode() {
    left = nullptr;
    right= nullptr;
}

template <typename T>
BTNode<T>::BTNode(const T& new_data) {
    data = new_data; 
    left = nullptr; 
    right = nullptr;
}

template <typename T>
BTNode<T>::~BTNode() {

}

//set data for node
template <typename T>
void BTNode<T>::set_data(const T& new_data)
{
    data = new_data;
}

//set left child for node
template <typename T>
void BTNode<T>::set_left(BTNode<T>* new_left)
{
    left = new_left;
}

//set right child for node
template <typename T>
void BTNode<T>::set_right(BTNode<T>* new_right)
{
    right = new_right;
}

//get reference to data in node
template <typename T>
T& BTNode<T>::get_data()
{
    return data;
}

//get pointer to left child
template <typename T>
BTNode<T>* BTNode<T>::get_left() const
{
    return left;
}

//get pointer to right child
template <typename T>
BTNode<T>* BTNode<T>::get_right() const
{
    return right;
}

//value of the data variable is appended to the stream
template <typename T>
std::ostream& operator<<(std::ostream& out, const BTNode<T>& node)
{
    out << node.get_data();
    return out;
}
