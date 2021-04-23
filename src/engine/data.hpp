#ifndef LAYOUT_DATA_HPP
#define LAYOUT_DATA_HPP
#include <string>

namespace orca
{
struct LayoutData
{
    int width = 0, height = 0;
    std::string text;
    int text_size;
    uint32_t color, bg_color;
};
} // namespace orca
#endif
