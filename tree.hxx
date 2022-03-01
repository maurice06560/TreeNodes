#pragma once 

#include <vector>
#include <iostream>
#include <exception>

// ===================================================
// Structure to contain the output information
//
// Provide a print method to display the outputs 
// in a formatted way
// ===================================================
template <typename T>
struct DeepestNodes {
    std::vector<T> m_deepestNode;
    int m_depth = -1;

    void print() const;
};

template <typename T>
void DeepestNodes<T>::print() const
{
    std::cout << "deepest";

    for (int idx = 0; idx < m_deepestNode.size(); idx++)
        std::cout << ", " << m_deepestNode[idx];

    std::cout << "; depth, " << m_depth << '\n';
}

// ===================================================
// Tree class
// ===================================================
template <typename T>
class Tree {

public:
    Tree(const std::vector<T>& inputNodes);
    ~Tree();

    DeepestNodes<T> getDeepestNodes() const;

private:
    T m_value;
    Tree* m_left = nullptr;
    Tree* m_right = nullptr;

    Tree(const T& value);
    void emptyTree(Tree<T>* node);
    Tree<T>* insert(Tree<T>* node, const T& value);

    void dfsDeepNodes(const Tree<T>* node, const int depth, DeepestNodes<T>& deepestNodes) const;
};

// =============================
// Constructor taking a vector
// in input
// =============================
template <class T>
Tree<T>::Tree(const std::vector<T>& inputNodes)
{
    if (inputNodes.size() == 0)
        throw std::runtime_error("Input vector cannot be empty");

    // Process the root node
    m_value = inputNodes[0];

    // insert the rest of nodes in a DFS manner
    for (int idx = 1; idx < inputNodes.size(); idx++)
       insert(this, inputNodes[idx]);
}

// =============================
// Constructor taking a single
// input element
// =============================
template <class T>
Tree<T>::Tree(const T& value) : m_value(value)
{
}

// =============================
// Delete all tree nodes
// =============================
template <class T>
void Tree<T>::emptyTree(Tree<T>* node) 
{
    if (node->m_left) 
    {
        emptyTree(node->m_left);
        delete node->m_left;
        node->m_left = nullptr;
    }

    if (node->m_right)
    {
        emptyTree(node->m_right);
        delete node->m_right;
        node->m_right = nullptr;
    }

    return;
}

// =============================
// Destructor
// =============================
template <class T>
Tree<T>::~Tree()
{
    emptyTree(this); 
}

// =============================
// Insert node in the tree
// =============================
template <class T>
Tree<T>* Tree<T>::insert(Tree<T>* node, const T& value) {

    if (!node)
        return new Tree<T>(value);

    if (value < node->m_value)
        node->m_left = insert(node->m_left, value);
    else 
        node->m_right = insert(node->m_right, value);

    return node;
}

// =============================
// Build the DeepestNodes output
// object
// =============================
template <class T>
DeepestNodes<T> Tree<T>::getDeepestNodes() const
{
    DeepestNodes<T> deepestNodes;

    dfsDeepNodes(this, 0, deepestNodes);

    return deepestNodes;
}

// =============================
template <class T>
void Tree<T>::dfsDeepNodes(const Tree<T>* node, const int depth, DeepestNodes<T>& deepestNodes) const
{
    if (!node->m_left && !node->m_right)
    {
        if (depth == deepestNodes.m_depth)
        {
            deepestNodes.m_deepestNode.push_back(node->m_value);
        }
        else if (depth >  deepestNodes.m_depth)
        {
            deepestNodes.m_deepestNode.clear();
            deepestNodes.m_deepestNode.push_back(node->m_value);
            deepestNodes.m_depth = depth;
        }

        return;
    }

    if (node->m_left)
        dfsDeepNodes(node->m_left, depth + 1, deepestNodes);

    if (node->m_right)
        dfsDeepNodes(node->m_right, depth + 1, deepestNodes);

    return;
}
