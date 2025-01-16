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
    for (int i = 0; i < level.size(); i++)
    {
        string levelAt = level.at(i);
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
        else
        {
            //     grid->getLevel()->push_back(levelAt);
            for (int j = 0; j < levelAt.size(); j++)
            {
                if (levelAt.at(j) == 'W')
                    grid->occupiedSpacesWall->insert({j, i});
            }
            grid->setGridSizeX(levelAt.size());
            grid->setGridSizeY(grid->getGridSizeY() + 1);
        }
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