#include "winCondition.h"

WinCondition::WinCondition(WinConType type, int amount)
{
    this->type = type;
    this->amount = amount;
}

WinCondition::~WinCondition() {}

bool WinCondition::operator==(WinCondition const &other) const
{
    return other.type == this->type && other.amount == this->amount;
}

int WinCondition::getAmount()
{
    return amount;
}

WinConType WinCondition::getType()
{
    return type;
}