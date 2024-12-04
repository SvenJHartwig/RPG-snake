#pragma once

class IEatListener
{
public:
    virtual void eat(bool isSpecial) = 0;
};