#include "commonFunctions.h"
#include "editor/loadTextFile.h"

int main()
{
    std::string path = RESOURCE_DIR;
    std::cout << "Choose resource to open:\n";
    std::string input;
    std::cin >> input;
    path.append(input);
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);

    return 0;
}
