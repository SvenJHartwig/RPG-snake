#include "gameController.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include "../view/cliView.h"

using std::string, std::vector;

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

bool GameController::checkWinCondition()
{
    if (gridController->getWinCondition()->getType() == SCORE)
    {
        if (score >= gridController->getWinCondition()->getAmount())
        {
            return true;
        }
    }
    if (gridController->getWinCondition()->getType() == TIME)
    {
        if (steps >= gridController->getWinCondition()->getAmount())
        {
            return true;
        }
    }
    return false;
}

void GameController::reactOnInput(char input)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (input == 'p')
        {
            gameState = IN_GAME;
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
            softReset();
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
        steps++;
        break;
    case 'w':
        lastDirection = 'w';
        gridController->moveSnakeUp();
        steps++;
        break;
    case 'a':
        lastDirection = 'a';
        gridController->moveSnakeLeft();
        steps++;
        break;
    case 's':
        lastDirection = 's';
        gridController->moveSnakeDown();
        steps++;
        break;
    default:
        break;
    }
    gridController->updateGrid();
    view->setGrid(gridController->getSpriteVector());
    if (!infinite && checkWinCondition())
    {
        level++;
        gameState = WIN;
        view->gameStateChanged(gameState);
    }
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

void GameController::softReset()
{
    lastInput = ' ';
    lastDirection = ' ';
    speed = l1;
    eatCount = 0;
    score = 0;
    steps = 0;
    gridController->reset();
    gridController->updateGrid();
    view->setGrid(gridController->getSpriteVector());
}

void GameController::resetGame()
{
    view->setScore(0);
    level = 1;
    infinite = true;
    softReset();
}