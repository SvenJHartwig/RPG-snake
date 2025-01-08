#include "testClasses.h"
#include "../src/editor/loadTextFile.h"
#include <cstdio>

TEST_CASE("Import text file time")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithWincon2");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    REQUIRE(grid->getLevel()->size() == 15);
    REQUIRE(grid->getWinCondition() == WinCondition(TIME, 20));
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);
    grid = new Grid();
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(grid->getLevel()->size() == 15);
    REQUIRE(grid->getWinCondition() == WinCondition(TIME, 20));
}
TEST_CASE("Import text file score")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithWincon");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    REQUIRE(grid->getLevel()->size() == 20);
    REQUIRE(grid->getWinCondition() == WinCondition(SCORE, 40));
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);
    grid = new Grid();
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(grid->getLevel()->size() == 20);
    REQUIRE(grid->getWinCondition() == WinCondition(SCORE, 40));
}