#include "element.h"

namespace SEngine
{
    void Element::setIsHovered(bool isHovered) { this->isHovered = isHovered; }
    int Element::getPosXTopLeft() { return pos_x_top_left; }
    int Element::getPosYTopLeft() { return pos_y_top_left; }
    int Element::getPosXBottomRight() { return pos_x_bottom_right; }
    int Element::getPosYBottomRight() { return pos_y_bottom_right; }
}