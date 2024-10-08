#pragma once

#include <vector>

class Food
{
private:
    int pos_x;
    int pos_y;

public:
    Food();
    ~Food();
    int getPosX();
    int getPosY();
    void setPosX(int pos);
    void setPosY(int pos);
};

class SpecialFood : public Food
{
};
class SnakeBodyPart
{
private:
    int pos_x;
    int pos_y;
    bool has_moved = false;

public:
    SnakeBodyPart(int pos_x, int pos_y);
    ~SnakeBodyPart();
    int getPosX();
    int getPosY();
    void setPosX(int pos);
    void setPosY(int pos);
    bool getHasMoved();
    void setHasMoved(bool val);
};

class Snake
{
private:
    int head_pos_x = 5;
    int head_pos_y = 5;
    std::vector<SnakeBodyPart> body;

public:
    Snake();
    ~Snake();
    int getHeadX();
    int getHeadY();
    void setPosX(int pos);
    void setPosY(int pos);
    void eat();
    std::vector<SnakeBodyPart> *getBody();
};
