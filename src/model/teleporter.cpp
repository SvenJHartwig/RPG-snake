#include "teleporter.h"
#include "snake.h"

Teleporter::Teleporter(int pos_x, int pos_y, std::string path, int targetPosX, int targetPosY)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->path = path;
    this->targetPosX = targetPosX;
    this->targetPosY = targetPosY;
}
void Teleporter::snakeOnElement(IGridController *controller)
{
    controller->loadLevel(static_cast<std::string>(RESOURCE_DIR).append(path));
    Snake *snake = static_cast<Snake *>(controller->getSnake());
    snake->setPosX(targetPosX);
    snake->setPosY(targetPosY);
    for (int i = 0; i < snake->getBody()->size(); i++)
    {
        SnakeBodyPart *bodyPart = &(snake->getBody()->at(i));
        bodyPart->setPosX(targetPosX);
        bodyPart->setPosY(targetPosY);
        bodyPart->setHasMoved(false);
    }
}
void Teleporter::snakeMovedAway(IGridController *controller) {}
void Teleporter::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"T"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
    outFile->write(reinterpret_cast<const char *>(&targetPosX), sizeof(targetPosX));
    outFile->write(reinterpret_cast<const char *>(&targetPosY), sizeof(targetPosY));
    size_t strLength = path.size();
    outFile->write(reinterpret_cast<const char *>(&strLength), sizeof(strLength));
    outFile->write(path.data(), strLength);
}