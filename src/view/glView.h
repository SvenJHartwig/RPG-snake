#pragma once

#include "iGameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../controller/gameController.h"
#include "engine/elements/scene.h"
#include "engine/iRenderEngine.h"
#include "dialog.h"

class GlView : public IGameView
{
private:
    SEngine::IRenderEngine *engine = NULL;
    IGameController *gameController = NULL;
    SEngine::Scene *mainMenu = NULL;
    SEngine::Scene *inGame = NULL;
    SEngine::Scene *gameOver = NULL;
    SEngine::Scene *win = NULL;
    bool initialized = false;
    Dialog *dialog = NULL;

public:
    GlView();
    int init() override;
    void gameStateChanged(GameState game_state) override;
    SEngine::Scene *getMainMenu() { return mainMenu; }
    SEngine::Scene *getInGameScene() { return inGame; }
    SEngine::Scene *getGameOverScene() { return gameOver; }
    void initMainMenu();
    void initGameScene();
    void initGameOverScene();
    void initWinScene();
    IGameController *getGameController() { return gameController; }
    void setGameController(IGameController *gc) override { this->gameController = gc; }
    void setEngine(SEngine::IRenderEngine *engine) { this->engine = engine; }
    SEngine::IRenderEngine *getEngine() { return engine; }
    bool isInitialized() { return initialized; }
    void setInitialized(bool initialized) { this->initialized = initialized; }
    void setScore(int count) override;
    void setHealth(int count) override;
    void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid) override;
    void setQuests(std::vector<Quest *> *quests) override;
    void showDialog(std::string text) override;
    void closeDialog() override;
};