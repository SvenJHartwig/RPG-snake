#include "testClasses.h"
#include "../src/editor/loadTextFile.h"

TEST_CASE("Import text file")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithWincon2");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    REQUIRE(grid->getLevel()->size() == 15);
}