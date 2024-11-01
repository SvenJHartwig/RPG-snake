#include "snake.h"

Food::Food()
{
    pos_x = 7;
    pos_y = 5;
}

Food::~Food()
{
}

int Food::getPosX()
{
    return pos_x;
}

int Food::getPosY()
{
    return pos_y;
}
void Food::setPosX(int pos)
{
    this->pos_x = pos;
}
void Food::setPosY(int pos)
{
    this->pos_y = pos;
}

SnakeBodyPart::SnakeBodyPart(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
SnakeBodyPart::~SnakeBodyPart()
{
}
int SnakeBodyPart::getPosX()
{
    return pos_x;
}

int SnakeBodyPart::getPosY()
{
    return pos_y;
}
void SnakeBodyPart::setPosX(int pos)
{
    this->pos_x = pos;
}
void SnakeBodyPart::setPosY(int pos)
{
    this->pos_y = pos;
}
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
}

Snake::~Snake()
{
}

int Snake::getHeadX()
{
    return this->head_pos_x;
}

int Snake::getHeadY()
{
    return this->head_pos_y;
}
void Snake::eat()
{
    SnakeBodyPart *newPart = new SnakeBodyPart(this->head_pos_x, this->head_pos_y);
    body.push_back(*newPart);
}
std::vector<SnakeBodyPart> *Snake::getBody()
{
    return &body;
}
void Snake::setPosX(int pos)
{
    this->head_pos_x = pos;
}
void Snake::setPosY(int pos)
{
    this->head_pos_y = pos;
}
