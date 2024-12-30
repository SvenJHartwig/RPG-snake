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
        string l = level.at(i);
        if (l.rfind("Wincon:", 0) == 0)
        {
            l.replace(0, 7, 0, 'f');
            if (l.rfind("s", 0) == 0)
            {
                l.replace(0, 1, 0, 'f');
                if (has_only_digits(l))
                {
                    grid->setWinCondition(WinCondition(SCORE, std::stoi(l)));
                }
            }
            else if (l.rfind("t", 0) == 0)
            {
                l.replace(0, 1, 0, 'f');
                if (has_only_digits(l))
                {
                    grid->setWinCondition(WinCondition(TIME, std::stoi(l)));
                }
            }
        }
        else
        {
            grid->getLevel()->push_back(l);
            for (int j = 0; j < l.size(); j++)
            {
                if (l.at(j) == 'W')
                    grid->occupiedSpacesWall->insert({j, i});
            }
            grid->setGridSizeX(l.size());
            grid->setGridSizeY(grid->getGridSizeY() + 1);
        }
    }
}