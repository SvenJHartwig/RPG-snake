#include "commonFunctions.h"
#include "editor/loadTextFile.h"
#include "model/mob.h"
#include "model/teleporter.h"

int main()
{
    bool exit = false;
    std::string input;
    /*
     * States:
     * 0 - Initial
     * 1 - Map loaded
     * 2 - Choosing what element to add
     */
    int state = 0;
    std::string path = RESOURCE_DIR;
    Grid *grid;
    int x;
    int y;
    while (!exit)
    {
        if (state == 0)
        {
            std::cout << "Choose option:\n";
            std::cout << "1 - Load map\n";
            std::cout << "2 - Exit\n";
            std::cin >> input;
            if (input.compare("1") == 0)
            {
                std::cout << "Choose resource to open:\n";
                std::cin >> input;
                path.append(input);
                grid = new Grid();
                loadLevelFromBinaryFile(path.c_str(), grid);
                state = 1;
            }
            else if (input.compare("2") == 0)
            {
                exit = true;
            }
        }
        else if (state == 1)
        {
            std::cout << "Loaded: " << path << "\n";
            std::cout << "Choose option:\n";
            std::cout << "1 - Save map\n";
            std::cout << "2 - Save map as\n";
            std::cout << "3 - Add element\n";
            std::cout << "4 - Back\n";
            std::cin >> input;
            if (input.compare("1") == 0)
            {
                saveGridAsBinaryFile(path, grid);
            }
            if (input.compare("2") == 0)
            {
                std::cout << "File name:\n";
                std::cin >> input;
                path = RESOURCE_DIR;
                path.append(input);
                saveGridAsBinaryFile(path, grid);
            }
            if (input.compare("3") == 0)
            {
                std::cout << "Position X:\n";
                std::cin >> input;
                x = std::stoi(input);
                std::cout << "Position Y:\n";
                std::cin >> input;
                y = std::stoi(input);
                state = 2;
            }
            else if (input.compare("4") == 0)
            {
                path = RESOURCE_DIR;
                state = 0;
            }
        }
        else if (state == 2)
        {
            std::cout << "Choose option:\n";
            std::cout << "1 - Wall\n";
            std::cout << "2 - Ground\n";
            std::cout << "3 - Enemy\n";
            std::cout << "4 - Teleporter\n";
            std::cout << "5 - Back:\n";
            std::cin >> input;
            if (input.compare("1") == 0)
            {
                grid->getLevel()->at(y)->at(x) = new Wall(x, y);
            }
            if (input.compare("2") == 0)
            {
                grid->getLevel()->at(y)->at(x) = new Ground(x, y);
            }
            if (input.compare("3") == 0)
            {
                grid->getLevel()->at(y)->at(x) = new Enemy(x, y);
            }
            if (input.compare("4") == 0)
            {
                std::cout << "File name:\n";
                std::cin >> input;
                std::string mapPath = input;
                std::cout << "Target Position X:\n";
                std::cin >> input;
                int targetX = std::stoi(input);
                std::cout << "Target Position Y:\n";
                std::cin >> input;
                int targetY = std::stoi(input);
                grid->getLevel()->at(y)->at(x) = new Teleporter(x, y, mapPath, targetX, targetY);
            }
            else if (input.compare("5") == 0)
            {
                state = 1;
            }
        }
    }

    return 0;
}
