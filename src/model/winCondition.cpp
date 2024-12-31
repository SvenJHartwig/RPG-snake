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

std::string WinCondition::toString()
{
    std::string result;
    switch (type)
    {
    case SCORE:
        result = std::to_string(amount) + " points";
        break;
    case TIME:
        result = std::to_string(amount) + " steps";
        break;
    case NONE:
        result = "None";
        break;
    }
    return result;
}
void WinCondition::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&amount), sizeof(amount));

    std::string typeString;
    switch (type)
    {
    case SCORE:
        typeString = "SCORE";
        break;
    case TIME:
        typeString = "TIME";
        break;
    case NONE:
        typeString = "NONE";
        break;
    }
    size_t strLength = typeString.size();
    outFile->write(reinterpret_cast<const char *>(&strLength), sizeof(strLength));
    outFile->write(typeString.data(), strLength);
}
void WinCondition::deserialize(std::ifstream *inFile)
{
    inFile->read(reinterpret_cast<char *>(&amount), sizeof(amount));

    size_t strLength;
    std::string typeString;
    inFile->read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    typeString.resize(strLength);
    inFile->read(&typeString[0], strLength); // Load string content
    if (typeString == "SCORE")
    {
        type = SCORE;
    }
    else if (typeString == "TIME")
    {
        type = TIME;
    }
    else
    {
        type = NONE;
    }
}