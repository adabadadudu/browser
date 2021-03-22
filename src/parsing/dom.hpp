#ifndef DOM_NODE_H
#define DOM_NODE_H
#include <map>
#include <string>
#include <vector>

/* DOM or document object model is a programming API for HTML, it's represented as a tree,
so
<html>
  <body>
    <p>
      Hello World
    </p>
    <div> <img src="example.png"/></div>
  </body>
</html>

would be:
html -|
      |_ Body -|
               |_ Paragraph -|
                             |_Text
               |_ Div -|
                       |_ Image 
*/

class DOMNode
{

public:
    DOMNode *parent;                 // Parent of the Node
    std::vector<DOMNode *> children; // Children of the node

    std::string name;
    std::map<std::string, std::string> attributes;
    std::string text;

    DOMNode();                // Class constructor for the root node
    DOMNode(DOMNode *parent); // Class constructor for the children nodes

    void add_child(DOMNode *node);
    void set_parent(DOMNode *parent);
    void add_attribute(std::string key, std::string data); // Attributes can be "class", "background-color",...
};

#endif
