#include "mob.h"
#include "grid.h"

IntendedAction Mob::getIntendedAction()
{
    return intendedAction;
}

int Enemy::currentId = 0;

void Enemy::snakeOnElement(IGridController *controller)
{
    std::vector<Mob *> *mobs = static_cast<Grid *>(controller->getGrid())->getMobs();
    for (int i = 0; i < mobs->size(); i++)
    {
        Enemy *enemy = dynamic_cast<Enemy *>(mobs->at(i));
        if (enemy)
        {
            if (enemy->id == this->id)
            {
                mobs->erase(mobs->cbegin() + i);
            }
        }
    }
}
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
    this->id = currentId++;
}

Enemy::~Enemy() {}