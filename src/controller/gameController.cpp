#include "gameController.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include "../view/cliView.h"
#include "../model/mob.h"

using std::string, std::vector;

GameController::GameController()
{
    gridController = new GridController(this);
    gameMode = GameModeFactory::createGameMode(INFINITE, this);
}

GameController::~GameController() {}

void GameController::setView(IGameView *view)
{
    this->view = view;
}
void GameController::setSoundController(ISoundController *soundController)
{
    this->soundController = soundController;
}

void GameController::reactOnInput(int input)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (input == GLFW_KEY_ENTER)
        {
            gameState = IN_GAME;
            view->gameStateChanged(gameState);
            view->setQuests(gridController->getGrid()->getWinCondition().toString());
            soundController->playBackgroundMusic(static_cast<std::string>(RESOURCE_DIR).append("/music/background.mp3"));
        }
        else if (input == GLFW_KEY_O)
        {
            string path = RESOURCE_DIR;
            path.append("/level/level1");
            gridController->loadLevel(path);
            gridController->updateGrid();
            gameState = IN_GAME;
            gameMode = GameModeFactory::createGameMode(RPG, this);

            WinCondition winCon = gridController->getGrid()->getWinCondition();
            gameMode->addQuest("First quest", &winCon);
            view->gameStateChanged(gameState);
            view->setQuests(gameMode->getQuests()->at(0)->getName());
            soundController->playBackgroundMusic(static_cast<std::string>(RESOURCE_DIR).append("/music/background.mp3"));
        }
        else if (input == GLFW_KEY_ESCAPE)
        {
            gameState = EXIT;
            view->gameStateChanged(gameState);
        }
    case IN_GAME:
        if (eatCount > 0 &&
                (lastDirection == 'a' && input == GLFW_KEY_RIGHT ||
                 lastDirection == 'w' && input == GLFW_KEY_DOWN ||
                 lastDirection == 'd' && input == GLFW_KEY_LEFT ||
                 lastDirection == 's' && input == GLFW_KEY_UP) ||
            input != GLFW_KEY_RIGHT && input != GLFW_KEY_DOWN && input != GLFW_KEY_LEFT && input != GLFW_KEY_UP)
        {
            return;
        }
        if (input == GLFW_KEY_RIGHT)
        {
            lastInput = 'd';
        }
        else if (input == GLFW_KEY_DOWN)
        {
            lastInput = 's';
        }
        else if (input == GLFW_KEY_LEFT)
        {
            lastInput = 'a';
        }
        else if (input == GLFW_KEY_UP)
        {
            lastInput = 'w';
        }
        break;
    case GAME_OVER:
        if (input == GLFW_KEY_ENTER)
        {
            resetGame();
            gameState = MAIN_MENU;
            view->gameStateChanged(gameState);
            soundController->playBackgroundMusic(static_cast<std::string>(RESOURCE_DIR).append("/music/mainMenu.mp3"));
        }
        break;
    case WIN:
        if (input == GLFW_KEY_ENTER)
        {
            softReset();
            string path = RESOURCE_DIR;
            path.append("/level/level" + std::to_string(level));
            gridController->loadLevel(path);
            gridController->updateGrid();
            gameState = IN_GAME;
            view->gameStateChanged(gameState);
            view->setQuests(gridController->getGrid()->getWinCondition().toString());
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
    soundController->playBackgroundMusic(static_cast<std::string>(RESOURCE_DIR).append("/music/mainMenu.mp3"));

    while (gameState != EXIT && !windowClosed)
    {
        if (gameState == IN_GAME)
        {
            mainLoopIteration();
        }
        usleep(10000);
        ticksSinceMovement++;
    }
}

void GameController::mainLoopIteration()
{
    if (ticksSinceMovement >= speed)
    {
        ticksSinceMovement = 0;
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
    }
    gridController->updateGrid();
    view->setGrid(gridController->getSpriteVector());
    if (gameMode->hasHealth())
    {
        view->setHealth(gridController->getSnake()->getHealth());
    }
    /* if (gameMode->checkWinCondition())
     {
         level++;
         gameState = WIN;
         view->gameStateChanged(gameState);
     }*/
    if (gridController->isGameOver())
    {
        gameState = GAME_OVER;
        view->gameStateChanged(gameState);
    }
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
    soundController->playSoundEffect(static_cast<std::string>(RESOURCE_DIR).append("/sfx/eat.mp3"));
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
    view->setQuests(gridController->getGrid()->getWinCondition().toString());
}

void GameController::resetGame()
{
    view->setScore(0);
    level = 1;
    gameMode = GameModeFactory::createGameMode(INFINITE, this);
    softReset();
}