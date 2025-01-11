#include "mob.h"

IntendedAction Mob::getIntendedAction()
{
    return intendedAction;
}

void Enemy::tick()
{
    intendedAction = IntendedAction::MOVE_RIGHT;
}

Enemy::Enemy(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Enemy::~Enemy() {}