#include "snake.h"

void Food::snakeOnElement(IGridController *controller) {}
void Food::serialize(std::ofstream *outFile) {}
Food::Food()
{
    pos_x = 7;
    pos_y = 5;
}

Food::~Food() {}

void SpecialFood::snakeOnElement(IGridController *controller) {}
void SpecialFood::serialize(std::ofstream *outFile) {}

void SnakeBodyPart::snakeOnElement(IGridController *controller) {}
void SnakeBodyPart::serialize(std::ofstream *outFile) {}
SnakeBodyPart::SnakeBodyPart(int pos_x, int pos_y)
{
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

void Snake::snakeOnElement(IGridController *controller) {}
void Snake::serialize(std::ofstream *outFile) {}
Snake::Snake()
{
    pos_x = 5;
    pos_y = 5;
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
void Snake::loseHealth(int health)
{
    this->health -= health;
}
int Snake::getHealth()
{
    return this->health;
}
int Snake::getPosX()
{
    return pos_x;
}
int Snake::getPosY()
{
    return pos_y;
}
void Snake::setPosX(int pos)
{
    this->pos_x = pos;
}
void Snake::setPosY(int pos)
{
    this->pos_y = pos;
}