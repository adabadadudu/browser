#include "tel-parser.hpp"
#include <algorithm>
#include <utils/log.hpp>

bool startswith(std::string str, std::string word)
{
    if (str.rfind(word, 0) == 0)
    {
        return true;
    }

    return false;
}

std::string cut_string(std::string str, std::string with)
{
    return str.substr(str.find(with) + with.length());
}

std::vector<TelescopeObject> TelescopeParser::parse_star(std::string code)
{
    std::vector<TelescopeObject> objects;

    int num_of_chars = 0;
    char current_char;

    bool parsing = true;

    std::string holder;

    while (parsing)
    {

        TelescopeObject object;

        current_char = code[num_of_chars];

        holder += current_char;

        if (current_char == '\n' || current_char == EOF)
        {
            if (startswith(holder, "* "))
            {
                holder = cut_string(holder, "* ");
                object.size = 32;
                object.color = 0x98c379ff;
		object.style = sf::Text::Bold;
            }

            else if (startswith(holder, "** "))
            {
                holder = cut_string(holder, "** ");
                object.size = 24;
                object.color = 0x98c379ff;
		object.style = sf::Text::Bold;
            }

            else if (startswith(holder, "*** "))
            {

                holder = cut_string(holder, "*** ");
                object.size = 18;
		object.color = 0x98c379ff;		
		object.style = sf::Text::Bold;
            }

            object.text = holder;

            objects.push_back(object);
            holder = "";
        }

        num_of_chars++;
        if (num_of_chars == (int)code.length())
            parsing = false;
    }

    return objects;
}
