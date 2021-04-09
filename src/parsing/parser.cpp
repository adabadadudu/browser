#include "parser.hpp"

std::string Parser::parse_html(std::string code)
{
    char current_char = code[0], last_char;
    bool parsing = true;
    int number_of_chars = 1;
    std::string name;
    int state;
    while (parsing)
    {
        // Determining the current state of parsing, is in tag or not?

        last_char = current_char;
        current_char = code[number_of_chars];
        if (last_char == '<' && current_char != '>')
        {
            state = 0;
        }
        if (current_char == '>' && last_char != '<')
	  {
	    state = 1;
	    name += ' ';
	  }

        if (state == 0)
        {
            name += current_char;
        }

        number_of_chars++;

        if (number_of_chars == code.length())
            parsing = false;
    }
    return name;
}
