#include "gameController.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include "../view/cliView.h"

GameController::GameController()
{
    gridController = new GridController(this);
}

GameController::~GameController()
{
}

void GameController::setView(IGameView *view)
{
    this->view = view;
}

void GameController::reactOnInput(char input)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (input == 'p')
        {
            gameState = IN_GAME;
            Grid *grid = gridController->getGrid();
            grid->occupiedSpacesWall->clear();
            for (int i = 0; i < grid->getGrid()->size(); i++)
            {
                for (int j = 0; j < grid->getGrid()->at(i).size(); j++)
                {
                    grid->occupiedSpacesWall->insert({j, i});
                }
            }
            view->gameStateChanged(gameState);
        }
        else if (input == 'o')
        {
            infinite = false;
            string path = RESOURCE_DIR;
            path.append("/level/level1");
            gridController->loadLevel(path);
            gridController->updateGrid();
            gameState = IN_GAME;
            view->gameStateChanged(gameState);
        }
        else if (input == 'l')
        {
            gameState = EXIT;
            view->gameStateChanged(gameState);
        }
    case IN_GAME:
        if (eatCount > 0 &&
                (lastDirection == 'a' && input == 'd' ||
                 lastDirection == 'w' && input == 's' ||
                 lastDirection == 'd' && input == 'a' ||
                 lastDirection == 's' && input == 'w') ||
            input != 'a' && input != 'w' && input != 'd' && input != 's')
        {
            return;
        }
        lastInput = input;
        break;
    case GAME_OVER:
        if (input == 'p')
        {
            resetGame();
            gameState = MAIN_MENU;
            view->gameStateChanged(gameState);
        }
        break;
    case WIN:
        if (input == 'p')
        {
            resetGame();
            string path = RESOURCE_DIR;
            path.append("/level/level" + std::to_string(level));
            gridController->loadLevel(path);
            gridController->updateGrid();
            gameState = IN_GAME;
            view->gameStateChanged(gameState);
        }
        break;
    default:
        break;
    }
}

void GameController::mainLoop()
{
    view->setGameController(this);
    gridController->updateGrid();
    view->init();

    while (gameState != EXIT && !windowClosed)
    {
        if (gameState == IN_GAME)
        {
            mainLoopIteration();
        }
        usleep(speed);
    }
}

void GameController::mainLoopIteration()
{

    switch (lastInput)
    {
    case 'd':
        lastDirection = 'd';
        gridController->moveSnakeRight();
        break;
    case 'w':
        lastDirection = 'w';
        gridController->moveSnakeUp();
        break;
    case 'a':
        lastDirection = 'a';
        gridController->moveSnakeLeft();
        break;
    case 's':
        lastDirection = 's';
        gridController->moveSnakeDown();
        break;
    default:
        break;
    }
    // Updates the grid in memory to be read by the graphics engine
    vector<string> *chars = gridController->updateGrid();
    view->setGrid(chars);
    if (gridController->isGameOver())
    {
        gameState = GAME_OVER;
        view->gameStateChanged(gameState);
    }
}

Grid GameController::getGrid()
{
    return *gridController->getGrid();
}

void GameController::setWindowClosed(bool closed)
{
    windowClosed = closed;
}

GridController *GameController::getGridController()
{
    return gridController;
}

SpeedSetting GameController::getSpeed()
{
    return speed;
}

void GameController::eat(bool isSpecial)
{
    if (isSpecial)
        score += 2;
    else
        score++;
    eatCount++;
    if (eatCount == 2)
    {
        speed = l2;
    }
    else if (eatCount == 4)
    {
        speed = l3;
    }
    else if (eatCount == 6)
    {
        speed = l4;
    }
    else if (eatCount == 8)
    {
        speed = l5;
    }
    else if (eatCount == 10)
    {
        speed = l6;
    }
    view->setScore(score);
    if (!infinite && score >= 40)
    {
        level++;
        gameState = WIN;
        view->gameStateChanged(gameState);
    }
}

char GameController::getLastDirection()
{
    return lastDirection;
}

int GameController::getScore()
{
    return score;
}

GameState GameController::getGameState()
{
    return gameState;
}

void GameController::resetGame()
{
    lastInput = ' ';
    speed = l1;
    eatCount = 0;
    view->setScore(0);
    level = 1;
    infinite = true;
    score = 0;
    lastDirection = ' ';
    gridController->reset();
}