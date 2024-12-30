#include "commonFunctions.h"

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