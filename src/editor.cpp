#include "commonFunctions.h"
#include "editor/loadTextFile.h"

int main()
{
    std::string path = RESOURCE_DIR;
    path.append("/level/level1");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);

    return 0;
}
