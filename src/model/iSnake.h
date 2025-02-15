#pragma once

class ISnake
{
public:
    virtual int getHealth() = 0;
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual void setPosX(int pos) = 0;
    virtual void setPosY(int pos) = 0;
    virtual void eat() = 0;
};