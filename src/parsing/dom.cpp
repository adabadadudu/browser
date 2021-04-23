#include "dom.hpp"
#include <iostream>
DOMNode::DOMNode()
{
    parent = 0;
}

DOMNode::DOMNode(DOMNode *p)
{
    parent = p;
}

void DOMNode::add_child(DOMNode *node)
{
    children.push_back(node);
}

void DOMNode::set_parent(DOMNode *p)
{
    parent = p;
}

void DOMNode::add_attribute(std::string key, std::string data)
{
    attributes[key] = data;
}

void DOMNode::add_attributes_to_children()
{

    for (uint i = 0; i < children.size(); i++)
    {
        children[i]->add_attribute("class", attributes["class"]);
    }
}
