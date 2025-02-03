#include "gridElement.h"

using std::vector, std::string;
int GridElement::getPosX()
{
    return pos_x;
}

int GridElement::getPosY()
{
    return pos_y;
}
void GridElement::setPosX(int pos)
{
    this->pos_x = pos;
}
void GridElement::setPosY(int pos)
{
    this->pos_y = pos;
}

Ground::Ground(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
void Ground::snakeOnElement(IGridController *controller) {}
void Ground::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"x"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
}

Wall::Wall(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
void Wall::snakeOnElement(IGridController *controller) {}
void Wall::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"W"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
}

Teleporter::Teleporter(int pos_x, int pos_y, std::string path)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->path = path;
}
void Teleporter::snakeOnElement(IGridController *controller)
{
    controller->loadLevel(path);
}
void Teleporter::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"T"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
    size_t strLength = path.size();
    outFile->write(reinterpret_cast<const char *>(&strLength), sizeof(strLength));
    outFile->write(path.data(), strLength);
}