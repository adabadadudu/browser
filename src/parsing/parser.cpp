#include "parser.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <wctype.h>
enum state
{
    TAGNAME,
    INTAG,
    ENDTAG
};

DOMNode *Parser::parse_html(std::string code)
{
    char current_char = code[0], last_char;
    bool parsing = true, equal_sign = false;

    // The number of characters and the current parsing state.
    int number_of_chars = 1, state;

    DOMNode *current_node, *root = 0;

    // This is just a temporary string.
    std::string holder;

    while (parsing)
    {
        // Determining the current state of parsing, is in tag or not?

        last_char = current_char;
        current_char = code[number_of_chars];

        if (last_char == '<' && current_char != '/')
        {
            state = TAGNAME;
        }

        if (last_char == '>' && current_char != '<')
        {
            state = INTAG;
        }

        if (current_char == '/' && last_char == '<')
        {
            state = ENDTAG;
        }

        switch (state)
        {
        case TAGNAME:
        {

            // Here we only want to get the letters out of the tag name and not spaces.
            if (std::isalpha(current_char) && current_char != ' ')
            {
                holder += current_char;
            }

            if (!root && last_char == '<') // If the root of the tree is undefined, let the tag be it.
            {
                DOMNode *node = new DOMNode();

                root = node;

                current_node = node;
            }

            else if (last_char == '<') // else, set the tag as child of the current node.
            {
                DOMNode *node = new DOMNode(current_node);

                current_node->add_child(node);

                current_node = node;
            }

            if (current_char == ' ' || current_char == '>') // if at the end of the tag
            {

	       holder = remove_whitespace(holder); // Remove every space
                current_node->name = holder;

                if (root == current_node)
                    std::cout << "Created new root node: " << holder << "\n";
                else
                    std::cout << "Created new node: " << holder << " with " << current_node->parent->name << " as parent"
                              << "\n";

                holder = "";
            }
            break;
        }
        default:
            break;
        }

        number_of_chars++;

        if (number_of_chars == code.length())
            parsing = false;
    }
    return current_node;
}

std::string Parser::remove_whitespace(std::string string)
{
    int position_b;
    int position_e;

    for (int i = 0; i < string.size(); i++)
    {
        if (!std::iswspace(string[i]))
        {
            position_b = i;
            break;
        }
        else
        {
            position_b = i;
        }
    }
    for (int i = string.size() - 1; i >= 0; i--)
    {
        if (!std::iswspace(string[i]))
        {
            position_e = i + 1;
            break;
        }
        else
        {
            position_e = i;
        }
    }
    return string.substr(position_b, position_e);
}
