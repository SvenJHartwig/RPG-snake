#pragma once

#include <string>
#include "../model/grid.h"

void loadLevelFromTextFile(const std::string path, Grid *grid);
void loadLevelFromBinaryFile(const std::string path, Grid *grid);
void saveGridAsBinaryFile(const std::string filename, Grid *grid);