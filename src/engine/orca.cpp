#include <cstdio>
#include <engine/orca.hpp>
#include <iostream>
#include <stack>
#include <unistd.h>
#include <utils/log.hpp>
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

std::string Engine::get_value(std::string name, DOMNode *node, std::string default_s)
{

    std::string value;

    while (value.empty())
    {
        value = css[node->name][name];

        if (!css[node->name][name].empty())
            value = css[node->name][name];
	
        if (!css[node->attributes["class"]][name].empty())
            value = css[node->attributes["class"]][name];
	
        if (value.empty())
            value = default_s;
    }

    return value;
}

std::string Engine::get_value(std::string name, DOMNode *node, std::string other_name, std::string default_s)
{

    std::string value;

    while (value.empty())
    {
        value = css[node->name][name];

        if (!css[node->attributes["class"]][name].empty())
            value = css[node->attributes["class"]][name];

        if (!css[node->attributes["class"]][other_name].empty())
            value = css[node->attributes["class"]][other_name];

        if (!css[node->name][name].empty())
            value = css[node->name][name];

        if (!css[node->name][other_name].empty())
            value = css[node->name][other_name];

        if (value.empty())
            value = default_s;
    }
    return value;
}

std::vector<LayoutData> Engine::to_layout_data()
{

    std::map<std::string, uint32_t> colors = {
        {"black", 0x00000000},
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
        std::string color, bg_color, text_size;
        bg_color = get_value("background-color", n, "background", "white");

        color = get_value("color", n, "black");

        bool hex = false;

        if (color.find("#") != std::string::npos)
        {
            color.erase(0, 1);

            if (color.size() > 4)
                color += "ff";

            hex = true;
        }

        text_size = get_value("font-size", n, "12");

        n->layout_data.text_size = std::atoi(text_size.c_str());
        n->layout_data.text = n->text;
        n->layout_data.bg_color = colors[bg_color];

        n->layout_data.width = std::atoi(get_value("width", n, text_size).c_str());
        n->layout_data.height = std::atoi(get_value("height", n, text_size).c_str());

        if (!hex)
            n->layout_data.color = colors[color];
        else
            n->layout_data.color = static_cast<uint32_t>(std::stoul(color, 0, 16));

        result.push_back(n->layout_data);
    }

    return result;
}
