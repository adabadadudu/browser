#ifndef PARSER_H
#define PARSER_H
#include "dom.hpp"

// This is where we use the DOMNode to make a tree with the HTML elements.
class Parser
{
public:
    DOMNode *root_node;
    std::map<std::string, std::map<std::string, std::string>> css;

    DOMNode *parse_html(std::string code);
    DOMNode *find_node(DOMNode *base, std::string name); 
    std::map<std::string, std::map<std::string, std::string>> parse_css(std::string code);

private:
    std::string remove_whitespace(std::string str);
};

#endif
