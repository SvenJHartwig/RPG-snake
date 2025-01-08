#include "glView.h"
#include "engine/elements/button.h"
#include "engine/elements/image.h"
#include "engine/elements/text.h"
#include "engine/elements/spriteGrid.h"
#include "engine/renderEngine.h"
#include <thread>

using std::string, std::vector, SEngine::RenderData, SEngine::Button, SEngine::RenderEngine, SEngine::IRenderEngine,
    SEngine::IEngineCallback, SEngine::Scene, SEngine::Text, SEngine::SpriteGrid, SEngine::Sprite, SEngine::Image;

GlView::GlView() {}

void initView(IRenderEngine *engine, GlView *view)
{
    engine->init();
    view->initMainMenu();
    view->initGameScene();
    view->initGameOverScene();
    view->initWinScene();
    engine->addScene(view->getMainMenu());
    engine->setEngineCallback(view->getGameController());
    view->setInitialized(true);
    engine->renderingLoop();
}

int GlView::init()
{
    delete (engine);
    engine = new RenderEngine();
    const std::thread *initThread = new std::thread(initView, engine, this);

    return 0;
}

void inputP(IEngineCallback *gc)
{
    gc->reactOnInput(GLFW_KEY_P);
}

void inputO(IEngineCallback *gc)
{
    gc->reactOnInput(GLFW_KEY_O);
}

void inputL(IEngineCallback *gc)
{
    gc->reactOnInput(GLFW_KEY_L);
}

void GlView::initMainMenu()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    mainMenu = new Scene();
    Button *first = new Button(windowWidth / 2 - 80, windowHeight / 2 - 30, windowWidth / 2 + 80, windowHeight / 2);
    first->text = "Begin game";
    first->callback = &inputP;
    Button *second = new Button(windowWidth / 2 - 80, windowHeight / 2 + 20, windowWidth / 2 + 80, windowHeight / 2 + 50);
    second->text = "Load level";
    second->callback = &inputO;
    Button *third = new Button(windowWidth / 2 - 40, windowHeight / 2 + 200, windowWidth / 2 + 40, windowHeight / 2 + 230);
    third->text = "Exit";
    third->callback = &inputL;
    mainMenu->scene_elements = new std::vector<SEngine::Element *>(1, first);
    mainMenu->scene_elements->push_back(second);
    mainMenu->scene_elements->push_back(third);
}

void GlView::initGameScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    inGame = new Scene();
    Text *scoreText = new Text(0, 0, 100, 20);
    scoreText->text = "Score: 0";
    inGame->scene_elements = new std::vector<SEngine::Element *>(1, scoreText);
    Image *image = new Image(windowWidth / 2 - 320, 80, windowWidth / 2 + 320, 720, ((std::string)RESOURCE_DIR).append("/textures/grid.png").c_str());
    inGame->scene_elements->push_back(image);
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    SpriteGrid *spriteGrid = new SpriteGrid(windowWidth / 2 - 320, 80, 200, 100, texturePath, 0.25f);
    spriteGrid->setGrid(new vector<vector<SEngine::Sprite> *>());
    inGame->scene_elements->push_back(spriteGrid);
    Text *winConText = new Text(0, 20, 100, 40);
    winConText->text = "Win condition: ";
    inGame->scene_elements->push_back(winConText);
}

void GlView::initGameOverScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    gameOver = new Scene();
    Text *gameOverText = new Text(windowWidth / 2 - 40, windowHeight / 2 - 20, windowWidth / 2 + 40, windowHeight / 2);
    gameOverText->text = "GAME OVER";
    gameOver->scene_elements = new std::vector<SEngine::Element *>(1, gameOverText);
    Text *gameOverText2 = new Text(windowWidth / 2 - 40, windowHeight / 2 + 20, windowWidth / 2 + 40, windowHeight / 2 + 40);
    gameOverText2->text = "PRESS P TO RETURN TO MAIN MENU";
    gameOver->scene_elements->push_back(gameOverText2);
}

void GlView::initWinScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    win = new Scene();
    Text *gameOverText = new Text(windowWidth / 2 - 40, windowHeight / 2 - 20, windowWidth / 2 + 40, windowHeight / 2);
    gameOverText->text = "YOU WON THIS LEVEL!";
    win->scene_elements = new std::vector<SEngine::Element *>(1, gameOverText);
    Text *gameOverText2 = new Text(windowWidth / 2 - 40, windowHeight / 2 + 20, windowWidth / 2 + 40, windowHeight / 2 + 40);
    gameOverText2->text = "PRESS P TO GO TO THE NEXT LEVEL";
    win->scene_elements->push_back(gameOverText2);
}

void GlView::gameStateChanged(GameState game_state)
{
    engine->getScenes()->clear();
    if (game_state == IN_GAME)
    {
        engine->addScene(inGame);
        //  glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (game_state == MAIN_MENU)
    {
        engine->addScene(mainMenu);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (game_state == GAME_OVER)
    {
        engine->addScene(inGame);
        engine->addScene(gameOver);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (game_state == WIN)
    {
        engine->addScene(inGame);
        engine->addScene(win);
    }
}

void GlView::setScore(int count)
{
    static_cast<Text *>(inGame->scene_elements->at(0))->text = "Score: " + std::to_string(count);
}

void GlView::setGrid(vector<vector<SEngine::Sprite> *> *grid)
{
    static_cast<SpriteGrid *>(inGame->scene_elements->at(2))->setGrid(grid);
}

void GlView::setWinCondition(WinCondition condition)
{
    static_cast<Text *>(inGame->scene_elements->at(3))->text = "Win condition: " + condition.toString();
}