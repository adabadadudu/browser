#ifndef PARSER_H
#define PARSER_H
#include "dom.hpp"

// This is where we use the DOMNode to make a tree with the HTML elements.
class Parser
{
public:
    DOMNode *root;
    std::map<std::string, std::map<std::string, std::string>> css;

    std::string parse_html(std::string code);

private:
    std::string remove_whitespace(std::string str);
};

#endif
