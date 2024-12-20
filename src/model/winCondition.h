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

public:
    WinCondition(WinConType type);
    ~WinCondition();
    bool operator==(WinCondition const &other) const;
};