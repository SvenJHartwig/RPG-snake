#include "snake.h"

Ground::Ground()
{
    gridElementType = GROUND;
}
Ground::~Ground() {}

Wall::Wall()
{
    gridElementType = WALL;
}
Wall::~Wall() {}

Food::Food()
{
    gridElementType = FOOD;
    pos_x = 7;
    pos_y = 5;
}

Food::~Food() {}

SnakeBodyPart::SnakeBodyPart(int pos_x, int pos_y)
{
    gridElementType = SNAKE;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
SnakeBodyPart::~SnakeBodyPart() {}
bool SnakeBodyPart::getHasMoved()
{
    return has_moved;
}
void SnakeBodyPart::setHasMoved(bool val)
{
    this->has_moved = val;
}

Snake::Snake()
{
    pos_x = 5;
    pos_y = 5;
    gridElementType = SNAKE;
}

Snake::~Snake() {}

void Snake::eat()
{
    SnakeBodyPart *newPart = new SnakeBodyPart(this->pos_x, this->pos_y);
    body.push_back(*newPart);
}
std::vector<SnakeBodyPart> *Snake::getBody()
{
    return &body;
}