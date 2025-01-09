#include "mob.h"

void Enemy::tick()
{
    pos_x++;
}

Enemy::Enemy(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Enemy::~Enemy() {}