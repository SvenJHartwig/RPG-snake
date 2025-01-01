#include "commonFunctions.h"
#include "editor/loadTextFile.h"

int main()
{
    std::string path = RESOURCE_DIR;
    path.append("/tests/level/level1");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);

    return 0;
}
