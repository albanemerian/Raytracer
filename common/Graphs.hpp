/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Graphs
*/

#ifndef GRAPHS_HPP_
#define GRAPHS_HPP_

#include "IPrimitives.hpp"
#include "ILight.hpp"
#include <memory>
#include <vector>

template<typename T>
class GraphsNode {
public:
    std::shared_ptr<T> _primitives;
    std::vector<std::shared_ptr<GraphsNode<T>>> _children;

    GraphsNode() = default;
    GraphsNode(const GraphsNode& other) {
        *this = other;
    }
    GraphsNode& operator=(const GraphsNode& other) {
        if (this == &other)
            return *this;
        _primitives = other._primitives;
        _children.clear();
        for (const auto& child : other._children) {
            if (child)
                _children.push_back(std::make_shared<GraphsNode<T>>(*child));
            else
                _children.push_back(nullptr);
        }
        return *this;
    }
    template<typename Func>
    void traverseGraph(const std::shared_ptr<GraphsNode<T>>& node, Func &&func) {
        if (!node)
            return;
        if (node->_primitives)
            func(node->_primitives);
        for (const auto& child : node->_children)
            traverseGraph(child, func);
    }
};

using GraphsNodePrimitive = GraphsNode<IPrimitives>;
using GraphsNodeLight = GraphsNode<ILight>;

#endif /* !GRAPHS_HPP_ */
