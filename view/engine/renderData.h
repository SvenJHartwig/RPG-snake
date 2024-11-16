#pragma once

#include <vector>

using std::vector;

class RenderData
{
private:
    vector<float> *vertices;
    vector<unsigned int> *indices;

public:
    RenderData(vector<float> *vertices, vector<unsigned int> *indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
    vector<float> *getVertices() { return vertices; }
    vector<unsigned int> *getIndices() { return indices; }
};