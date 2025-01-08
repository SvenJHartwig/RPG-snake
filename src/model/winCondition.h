#pragma once

#include <string>
#include <iostream>
#include <fstream>

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
    bool operator!=(WinCondition const &other) const;
    std::string toString();
    void serialize(std::ofstream *outFile);
    void deserialize(std::ifstream *inFile);
};