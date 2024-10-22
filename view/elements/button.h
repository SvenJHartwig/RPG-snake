#pragma once
#include <string>

class Button
{
private:
    int pos_x_top_left;
    int pos_y_top_left;
    int pos_x_bottom_right;
    int pos_y_bottom_right;
    std::string text;

public:
    Button(int pos_x_top_left,
           int pos_y_top_left,
           int pos_x_bottom_right,
           int pos_y_bottom_right);
    ~Button();
};