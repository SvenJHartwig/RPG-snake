#include "spriteController.h"
#include "../model/teleporter.h"
#include "../model/mob.h"

std::vector<std::vector<SEngine::Sprite> *> *SpriteController::getSpriteVector(Grid *grid, Snake *snake, std::vector<Food *> *food)
{
    using SEngine::Sprite, std::vector;
    vector<vector<Sprite> *> *result = new vector<vector<Sprite> *>();
    // Level grid
    for (int yCoord = 0; yCoord < grid->getLevel()->size(); yCoord++)
    {
        vector<Sprite> *inner = new vector<Sprite>(grid->getLevel()->at(yCoord)->size());
        result->push_back(inner);
        for (int xCoord = 0; xCoord < grid->getLevel()->at(yCoord)->size(); xCoord++)
        {
            Sprite tempSprite = Sprite();
            if (dynamic_cast<Wall *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.0f;
                tempSprite.texBaseY = 0.0f;
            }
            else if (dynamic_cast<Teleporter *>(grid->getLevel()->at(yCoord)->at(xCoord)))
            {
                tempSprite.texBaseX = 0.375f;
                tempSprite.texBaseY = 0.375f;
            }
            else
            {
                tempSprite.texBaseX = 0.125f;
                tempSprite.texBaseY = 0.0f;
            }
            result->at(yCoord)->at(xCoord) = tempSprite;
        }
    }
    if (food)
    {
        // Dynamic elements
        for (int foodIndex = 0; foodIndex < food->size(); foodIndex++)
        {
            Food *f = food->at(foodIndex);
            Sprite temp = result->at(f->getPosY())->at(f->getPosX());
            if (foodIndex == 0)
            {
                temp.texBaseX = 0.0f;
                temp.texBaseY = 0.125f;
            }
            else
            {
                temp.texBaseX = 0.125f;
                temp.texBaseY = 0.125f;
            }
            result->at(f->getPosY())->at(f->getPosX()) = temp;
        }
    }
    for (Mob *mob : *grid->getMobs())
    {
        Sprite temp = result->at(mob->getPosY())->at(mob->getPosX());
        if (dynamic_cast<Enemy *>(mob))
        {
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.375f;
        }
        else
        {
            temp.texBaseX = 0.5f;
            temp.texBaseY = 0.0f;
        }
        result->at(mob->getPosY())->at(mob->getPosX()) = temp;
    }
    if (snake)
    {
        for (int snakeBodyIndex = 0; snakeBodyIndex < snake->getBody()->size(); snakeBodyIndex++)
        {
            SnakeBodyPart bodyPart = snake->getBody()->at(snakeBodyIndex);
            Sprite temp = result->at(bodyPart.getPosY())->at(bodyPart.getPosX());
            switch (bodyPart.facing)
            {
            case HORIZONTAL:
                temp.texBaseX = 0.25f;
                temp.texBaseY = 0.0f;
                break;
            case VERTICAL:
                temp.texBaseX = 0.375f;
                temp.texBaseY = 0.0f;
                break;
            case LEFT_TO_DOWN:
                temp.texBaseX = 0.0f;
                temp.texBaseY = 0.25f;
                break;
            case RIGHT_TO_DOWN:
                temp.texBaseX = 0.125f;
                temp.texBaseY = 0.375f;
                break;
            case LEFT_TO_UP:
                temp.texBaseX = 0.0f;
                temp.texBaseY = 0.375f;
                break;
            case RIGHT_TO_UP:
                temp.texBaseX = 0.125f;
                temp.texBaseY = 0.25f;
                break;
            }
            result->at(bodyPart.getPosY())->at(bodyPart.getPosX()) = temp;
        }

        Sprite temp = result->at(snake->getPosY())->at(snake->getPosX());
        switch (snake->facing)
        {
        case RIGHT:
            temp.texBaseX = 0.375f;
            temp.texBaseY = 0.125f;
            break;
        case LEFT:
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.125f;
            break;
        case DOWN:
            temp.texBaseX = 0.25f;
            temp.texBaseY = 0.25f;
            break;
        case UP:
            temp.texBaseX = 0.375f;
            temp.texBaseY = 0.25f;
            break;
        }
        result->at(snake->getPosY())->at(snake->getPosX()) = temp;
    }

    return result;
}