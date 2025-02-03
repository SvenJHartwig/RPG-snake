#include "mob.h"

IntendedAction Mob::getIntendedAction()
{
    return intendedAction;
}

void Enemy::snakeOnElement(IGridController *controller) {}
void Enemy::setTicksSinceLastMovement(int ticksSinceLastMovement)
{
    this->ticksSinceLastMovement = ticksSinceLastMovement;
}
void Enemy::serialize(std::ofstream *outFile)
{
    outFile->write(reinterpret_cast<const char *>(&"E"), sizeof(char));
    outFile->write(reinterpret_cast<const char *>(&pos_x), sizeof(pos_x));
    outFile->write(reinterpret_cast<const char *>(&pos_y), sizeof(pos_y));
}
void Enemy::tick()
{
    intendedAction = IntendedAction::NONE;
    ticksSinceLastMovement++;
    if (ticksSinceLastMovement > 100)
    {
        intendedAction = IntendedAction::MOVE_RIGHT;
        ticksSinceLastMovement = 0;
    }
}

Enemy::Enemy(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Enemy::~Enemy() {}