#include "parser.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <wctype.h>

// Spoiler alert: most of the code is inspired by https://github.com/jackfischer/andreessen

enum state
{
    TAGNAME,
    BETWEENTAGS,
    ENDTAG
};

enum css_state
{
    CLASSNAME,
    PROPERTY,
    CODE,
    OFF
};

DOMNode *
Parser::parse_html(std::string code)
{
    char current_char = code[0], last_char;
    bool parsing = true, equal_sign = false, tag_name = false, between_tag = false;

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

        if (last_char == '<')
            tag_name = false;

        if (last_char == '<' && current_char != '/')
        {
            state = TAGNAME;
        }

        if (last_char == '>' && current_char != '<')
        {
            state = BETWEENTAGS;
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

            if ((current_char == ' ' || current_char == '>') && !tag_name) // if at the end of the tag
            {

                holder = remove_whitespace(holder); // Remove every space
                current_node->name = holder;

                if (root == current_node)
                    std::cout << "Created new root node: " << current_node->name << "\n";
                else
                    std::cout << "Created new node: " << current_node->name << " with " << current_node->parent->name << " as parent"
                              << "\n";

                holder = "";
                tag_name = true;
            }

            break;
        }

        case BETWEENTAGS:
        {

            if (current_char == '<')
            {

                state = ENDTAG;
                between_tag = true;
                break;
            }
            holder += current_char;
            break;
        }

        case ENDTAG:
        {

            if (between_tag)
            {

                int position_b, position_e;

                for (size_t i = 0; i < holder.size(); i++)
                {
                    if (!std::iswspace(holder[i]))
                    {
                        position_b = i;
                        break;
                    }
                    else
                        position_b = i;
                }

                for (size_t i = holder.size() - 1; i >= 0; i--)
                {
                    if (!std::iswspace(holder[i]))
                    {
                        position_e = i + 1;
                        break;
                    }
                    else
                    {
                        position_e = i;
                    }
                }

                bool junk = (position_e <= position_b) ? true : false;

                if (!junk)
                {
                    holder = holder.substr(position_b, position_e);
                    current_node->text = holder;
                    between_tag = false;
                }
                else
                {
                    between_tag = false;
                }
                holder = "";
            }

            if (current_char == '>')
            {
                if (current_node == root)
                    break;

                current_node = current_node->parent;
            }
            break;
        }
        default:
            break;
        }
        number_of_chars++;

        if (number_of_chars == (int)code.length())
            parsing = false;
    }

    root_node = root;
    return root;
}

DOMNode *Parser::find_node(DOMNode *base, std::string name)
{

    if (base->name == name)
    {
        return base;
    }

    for (int i = 0; i < base->children.size(); i++)
    {

        if (base->children[i]->name == name)
        {
            return base->children[i];
        }
    }

    return NULL;
}

std::map<std::string, std::map<std::string, std::string>> Parser::parse_css(std::string code)
{
    code.erase(std::remove(code.begin(), code.end(), '\n'), code.end());
    code.erase(std::remove(code.begin(), code.end(), ' '), code.end());

    std::map<std::string, std::map<std::string, std::string>> map;

    int state = OFF;

    std::string s_class, field, value, tag;

    bool b_class = false, b_tag = false;

    for (char c : code)
    {
        if (state == OFF && c == '.')
        {
            state = CLASSNAME;
            b_class = true;
	    b_tag = false;
        }

        else if (state == CLASSNAME && c != '{')
        {
            s_class.push_back(c);
        }

        else if (state == OFF && c != '{')
        {
            tag.push_back(c);
	    
            b_tag = true;
            b_class = false;
        }
	
        else if (state == OFF && c == '{')
        {
	  state = CODE;
        }
	
        else if (state == CLASSNAME && c == '{')
        {
            state = CODE;
        }

        else if (state == CODE && c != ':' && c != '}')
        {
            field.push_back(c);
        }

        else if (state == CODE && c == ':')
        {
            state = PROPERTY;
        }

        else if (state == CODE && c == '}')
        {
            s_class = " ";
	    tag = " ";
	    
            state = OFF;
        }

        else if (state == PROPERTY && c != ';')
        {
            value.push_back(c);
        }

        else if (state == PROPERTY && c == ';')
        {
            if (b_class)
            {
                map[s_class][field] = value;
            }

            if (b_tag)
            {
                map[tag][field] = value;
            }

            field = "";
            value = "";
            state = CODE;
        }
    }

    return map;
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
