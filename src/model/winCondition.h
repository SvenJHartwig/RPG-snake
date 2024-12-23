#pragma once

enum WinConType
{
    SCORE,
    TIME
};

class WinCondition
{
private:
    WinConType type;
    int amount;

public:
    WinCondition(WinConType type, int amount);
    ~WinCondition();
    bool operator==(WinCondition const &other) const;
};