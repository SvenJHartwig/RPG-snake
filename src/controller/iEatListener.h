#pragma once

#include "../model/quest.h"

class IEatListener
{
public:
    virtual void eat(bool isSpecial) = 0;
    virtual void setText(std::string text) = 0;
    virtual void addQuest(Quest *quest) = 0;
};