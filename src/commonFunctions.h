#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "model/grid.h"
#include "model/winCondition.h"

bool has_only_digits(const std::string s);
std::vector<std::string> readFileAsStringArray(const std::string &filepath);
void serializeString(std::ofstream *outFile, std::string text);