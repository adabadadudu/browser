#ifndef LAYOUT_ENGINE_HPP
#define LAYOUT_ENGINE_HPP
#include <map>
#include <parsing/dom.hpp>
#include <string>

namespace orca
{

class Engine
{
public:
    DOMNode *root;
    Engine(DOMNode *root, std::map<std::string, std::map<std::string, std::string>> css) : root(root), css(css) {}

    std::map<std::string, std::map<std::string, std::string>> css;

    std::vector<LayoutData> to_layout_data();

private:
    std::vector<DOMNode *> get_all_nodes();
    std::string get_value(std::string name, DOMNode *node, std::string default_s);
    std::string get_value(std::string name, DOMNode *node, std::string other_name, std::string default_s);
};
} // namespace orca

#endif
