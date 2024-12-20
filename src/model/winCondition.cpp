#include "winCondition.h"

WinCondition::WinCondition(WinConType type)
{
    this->type = type;
}

WinCondition::~WinCondition() {}

bool WinCondition::operator==(WinCondition const &other) const
{
    return other.type == this->type;
}