#pragma once

enum WinConType
{
    SCORE
};

class WinCondition
{
public:
    WinCondition(WinConType type);
    ~WinCondition();
    bool operator==(WinCondition const &other) const;
};