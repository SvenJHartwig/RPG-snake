#pragma once

#include <string>

enum WinConType
{
    SCORE,
    TIME,
    NONE
};

class WinCondition
{
private:
    WinConType type;
    int amount;

public:
    WinCondition(WinConType type, int amount);
    ~WinCondition();
    WinConType getType();
    int getAmount();
    bool operator==(WinCondition const &other) const;
    std::string toString();
};