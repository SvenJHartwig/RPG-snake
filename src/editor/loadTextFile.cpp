#include "loadTextFile.h"
#include "../commonFunctions.h"
#include <vector>

using std::vector, std::string;

void loadLevelFromTextFile(const string path, Grid *grid)
{
    vector<string> level = readFileAsStringArray(path);
    grid->occupiedSpacesWall->clear();
    grid->getLevel()->clear();
    grid->setGridSizeY(0);

    string levelAt = level.at(0);
    if (levelAt.rfind("Wincon:", 0) == 0)
    {
        levelAt.replace(0, 7, 0, 'f');
        if (levelAt.rfind("s", 0) == 0)
        {
            levelAt.replace(0, 1, 0, 'f');
            if (has_only_digits(levelAt))
            {
                grid->setWinCondition(WinCondition(SCORE, std::stoi(levelAt)));
            }
        }
        else if (levelAt.rfind("t", 0) == 0)
        {
            levelAt.replace(0, 1, 0, 'f');
            if (has_only_digits(levelAt))
            {
                grid->setWinCondition(WinCondition(TIME, std::stoi(levelAt)));
            }
        }
    }
    for (int i = 1; i < level.size(); i++)
    {
        string levelAt = level.at(i);
        vector<GridElement *> *temp = new vector<GridElement *>(levelAt.size());
        grid->getLevel()->push_back(temp);
        for (int j = 0; j < levelAt.size(); j++)
        {
            std::string gridElementType;

            if (levelAt.at(j) == 'W')
            {
                grid->getLevel()->at(i - 1)->at(j) = new Wall(j, i - 1);
                grid->occupiedSpacesWall->insert({j, i - 1});
            }
            if (levelAt.at(j) == 'x')
            {
                grid->getLevel()->at(i - 1)->at(j) = new Ground(j, i - 1);
            }
        }
        grid->setGridSizeX(levelAt.size());
        grid->setGridSizeY(grid->getGridSizeY() + 1);
    }
}
void loadLevelFromBinaryFile(const std::string path, Grid *grid)
{
    grid->loadFromFile(path);
}

void saveGridAsBinaryFile(const std::string path, Grid *grid)
{
    grid->saveToFile(path);
}