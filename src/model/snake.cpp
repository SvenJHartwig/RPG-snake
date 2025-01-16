#include "snake.h"

void Food::serialize(std::ofstream *outFile) {}
Food::Food()
{
    pos_x = 7;
    pos_y = 5;
}

Food::~Food() {}

void SpecialFood::serialize(std::ofstream *outFile) {}

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