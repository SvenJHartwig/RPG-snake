#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "model/grid.h"
#include "model/winCondition.h"

using std::vector, std::string;

bool has_only_digits(const string s)
{
    return s.find_first_not_of("0123456789") == string::npos;
}

vector<string> readFileAsStringArray(const string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        return {};
    }

    vector<string> lines;
    string line;

    // Read the file line by line and store each line in the vector
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

void loadLevel(const string path, Grid *grid)
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
                    //    wincon = new WinCondition(SCORE, std::stoi(l));
                }
            }
            else if (l.rfind("t", 0) == 0)
            {
                l.replace(0, 1, 0, 'f');
                if (has_only_digits(l))
                {
                    //    wincon = new WinCondition(TIME, std::stoi(l));
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

int main()
{
    string path = RESOURCE_DIR;
    path.append("/level/level1");
    Grid *grid = new Grid();
    loadLevel(path.c_str(), grid);

    return 0;
}
