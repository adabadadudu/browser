#include "dom.hpp"

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
