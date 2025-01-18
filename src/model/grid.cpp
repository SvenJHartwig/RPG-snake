#include "grid.h"

using std::vector, std::string;

void Grid::reset()
{
    grid_size_x = 20;
    grid_size_y = 20;
    winCon = WinCondition(NONE, 0);
    level = new vector<vector<GridElement *> *>();
    mobs = new std::vector<Mob *>();
    occupiedSpacesWall = new std::set<std::pair<int, int>>();
    occupiedSpacesSnake = new std::set<std::pair<int, int>>();
    for (int i = 0; i < grid_size_y; i++)
    {
        vector<GridElement *> *temp = new vector<GridElement *>(grid_size_x);
        level->push_back(temp);
        for (int j = 0; j < grid_size_x; j++)
        {
            if (i == 0 || i == grid_size_y - 1 || j == 0 || j == grid_size_x - 1)
            {
                // Wall
                level->at(i)->at(j) = new Wall(j, i);
                occupiedSpacesWall->insert({j, i});
            }
            else
            {
                level->at(i)->at(j) = new Ground(j, i);
            }
        }
    }
}
Grid::Grid()
{
    // Initialize standard level
    reset();
}

Grid::~Grid()
{
}
int Grid::getGridSizeX()
{
    return this->grid_size_x;
}
int Grid::getGridSizeY()
{
    return this->grid_size_y;
}

void Grid::saveToFile(const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        throw std::ios_base::failure("Failed to open file for writing.");
    }

    // Save the integers
    outFile.write(reinterpret_cast<const char *>(&grid_size_x), sizeof(grid_size_x));
    outFile.write(reinterpret_cast<const char *>(&grid_size_y), sizeof(grid_size_y));

    // Save the vector of strings
    size_t vectorSize = level->size();
    outFile.write(reinterpret_cast<const char *>(&vectorSize), sizeof(vectorSize));

    for (auto &levelVec : *(level))
    {
        for (GridElement *element : *(levelVec))
        {
            element->serialize(&outFile);
        }
    }
    winCon.serialize(&outFile);

    outFile.close();
}

// Load the object from a binary file
// If the file doesn't match the format the grid is reset.
void Grid::loadFromFile(const std::string &filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile)
    {
        reset();
        return;
    }

    try
    {
        // Load the integers
        inFile.read(reinterpret_cast<char *>(&grid_size_x), sizeof(grid_size_x));
        inFile.read(reinterpret_cast<char *>(&grid_size_y), sizeof(grid_size_y));

        // Load the vector of strings
        size_t vectorSize;
        inFile.read(reinterpret_cast<char *>(&vectorSize), sizeof(vectorSize));
        level->resize(vectorSize);
        for (int i = 0; i < grid_size_y; i++)
        {
            vector<GridElement *> *temp = new vector<GridElement *>(grid_size_x);
            level->at(i) = temp;
            for (int j = 0; j < grid_size_x; j++)
            {
                char gridElementType;
                inFile.read(reinterpret_cast<char *>(&gridElementType), sizeof(char));
                int x, y;
                inFile.read(reinterpret_cast<char *>(&x), sizeof(x));
                inFile.read(reinterpret_cast<char *>(&y), sizeof(y));

                if (gridElementType == 'x')
                {
                    level->at(i)->at(j) = new Ground(x, y);
                }
                if (gridElementType == 'W')
                {
                    level->at(i)->at(j) = new Wall(x, y);
                }
                if (gridElementType == 'E')
                {
                    mobs->push_back(new Enemy(x, y));
                }
            }
        }
        winCon.deserialize(&inFile);
    }
    catch (const std::exception &e)
    {
        reset();
        return;
    }

    inFile.close();
}

std::vector<Mob *> *Grid::getMobs()
{
    return mobs;
}