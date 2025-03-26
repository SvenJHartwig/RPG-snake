#pragma once

class IEatListener
{
public:
    virtual void eat(bool isSpecial) = 0;
    virtual void setText(std::string text) = 0;
};