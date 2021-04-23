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
};
} // namespace orca

#endif
