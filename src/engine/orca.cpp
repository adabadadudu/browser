#include <engine/orca.hpp>
#include <stack>
using namespace orca;

std::vector<DOMNode *> Engine::get_all_nodes()
{
    std::stack<DOMNode *> stack;
    std::vector<DOMNode *> result;

    stack.push(root);

    while (!stack.empty())
    {
        DOMNode *n = stack.top();

        stack.pop();

        result.push_back(n);

        for (int i = n->children.size() - 1; i >= 0; i--)
        {
            stack.push(n->children[i]);
        }
    }

    return result;
}

std::vector<LayoutData> Engine::to_layout_data()
{
    std::map<std::string, uint32_t> colors = {
        {"black", 0x000000ff},
        {"white", 0xffffffff},
        {"red", 0xff0000ff},
        {"yellow", 0xffff00ff},
        {"blue", 0x0000ffff},
        {"lime", 0x00ff00ff},
        {"green", 0x008000ff}};

    std::vector<DOMNode *> nodes = get_all_nodes();
    std::vector<LayoutData> result;

    for (auto n : nodes)
    {
        std::string bg_color = "", color = "";
        while (bg_color.empty())
        {
            bg_color = css[n->name]["background"];
            bg_color = css[n->name]["background-color"];
            bg_color = css[n->attributes["class"]]["background"];
            bg_color = css[n->attributes["class"]]["background-color"];

            if (bg_color.empty())
                bg_color = colors["white"];
        }

        while (color.empty())
        {
            color = css[n->name]["color"];
            color = css[n->attributes["class"]]["color"];

            if (color.empty())
                color = colors["black"];
        }

        n->layout_data.bg_color = colors[bg_color];
        n->layout_data.color = colors[color];
	
        result.push_back(n->layout_data);
    }

    return result;
}
