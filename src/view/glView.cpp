#include "glView.h"
#include "engine/elements/button.h"
#include "engine/elements/text.h"
#include "engine/elements/spriteGrid.h"
#include "engine/renderEngine.h"
#include <thread>

using std::string, std::vector;

void initView(IRenderEngine *engine, GlView *view)
{
    engine->init();
    view->initMainMenu();
    view->initGameScene();
    view->initGameOverScene();
    view->initWinScene();
    engine->setCurrentScene(view->getMainMenu());
    engine->setEngineCallback(view->getGameController());
    view->setInitialized(true);
    engine->renderingLoop();
}

int GlView::init()
{
    engine = new RenderEngine();
    std::thread *initThread = new std::thread(initView, engine, this);

    return 0;
}

void inputP(IEngineCallback *gc)
{
    gc->reactOnInput('p');
}

void inputO(IEngineCallback *gc)
{
    gc->reactOnInput('o');
}

void inputL(IEngineCallback *gc)
{
    gc->reactOnInput('l');
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
    mainMenu->scene_elements = new std::vector<Element *>(1, first);
    mainMenu->scene_elements->push_back(second);
    mainMenu->scene_elements->push_back(third);
}

void GlView::initGameScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    inGame = new Scene();
    Text *scoreText = new Text(0, 20, 40, windowHeight);
    scoreText->text = "Score: 0";
    inGame->scene_elements = new std::vector<Element *>(1, scoreText);
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    SpriteGrid *spriteGrid = new SpriteGrid(windowWidth / 2 - 320, 80, 200, 100, texturePath);
    spriteGrid->setGrid(new vector<vector<Sprite> *>());
    inGame->scene_elements->push_back(spriteGrid);
}

void GlView::initGameOverScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    gameOver = new Scene();
    Text *scoreText = new Text(0, 20, 40, windowHeight);
    scoreText->text = "Score: 0";
    gameOver->scene_elements = new std::vector<Element *>(1, scoreText);
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    SpriteGrid *spriteGrid = new SpriteGrid(windowWidth / 2 - 320, 80, 200, 100, texturePath);
    spriteGrid->setGrid(new vector<vector<Sprite> *>());
    gameOver->scene_elements->push_back(spriteGrid);
    Text *gameOverText = new Text(windowWidth / 2 - 40, windowHeight / 2 - 20, windowWidth / 2 + 40, windowHeight / 2);
    gameOverText->text = "GAME OVER";
    gameOver->scene_elements->push_back(gameOverText);
    Text *gameOverText2 = new Text(windowWidth / 2 - 40, windowHeight / 2 + 20, windowWidth / 2 + 40, windowHeight / 2 + 40);
    gameOverText2->text = "PRESS P TO RETURN TO MAIN MENU";
    gameOver->scene_elements->push_back(gameOverText2);
}

void GlView::initWinScene()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(engine->getWindow(), &windowWidth, &windowHeight);
    win = new Scene();
    Text *scoreText = new Text(0, 20, 40, windowHeight);
    scoreText->text = "Score: 0";
    win->scene_elements = new std::vector<Element *>(1, scoreText);
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    SpriteGrid *spriteGrid = new SpriteGrid(windowWidth / 2 - 320, 80, 200, 100, texturePath);
    spriteGrid->setGrid(new vector<vector<Sprite> *>());
    win->scene_elements->push_back(spriteGrid);
    Text *gameOverText = new Text(windowWidth / 2 - 40, windowHeight / 2 - 20, windowWidth / 2 + 40, windowHeight / 2);
    gameOverText->text = "YOU WON THIS LEVEL!";
    win->scene_elements->push_back(gameOverText);
    Text *gameOverText2 = new Text(windowWidth / 2 - 40, windowHeight / 2 + 20, windowWidth / 2 + 40, windowHeight / 2 + 40);
    gameOverText2->text = "PRESS P TO GO TO THE NEXT LEVEL";
    win->scene_elements->push_back(gameOverText2);
}

void GlView::gameStateChanged(GameState game_state)
{
    if (game_state == IN_GAME)
    {
        engine->setCurrentScene(inGame);
        //  glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (game_state == MAIN_MENU)
    {
        engine->setCurrentScene(mainMenu);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (game_state == GAME_OVER)
    {
        engine->setCurrentScene(gameOver);
        glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (game_state == WIN)
    {
        engine->setCurrentScene(win);
    }
}

void GlView::setScore(int count)
{
    ((Text *)inGame->scene_elements->at(0))->text = "Score: " + std::to_string(count);
    ((Text *)gameOver->scene_elements->at(0))->text = "Score: " + std::to_string(count);
    ((Text *)win->scene_elements->at(0))->text = "Score: " + std::to_string(count);
}

void GlView::setGrid(vector<vector<Sprite> *> *grid)
{
    ((SpriteGrid *)inGame->scene_elements->at(1))->setGrid(grid);
    ((SpriteGrid *)gameOver->scene_elements->at(1))->setGrid(grid);
    ((SpriteGrid *)win->scene_elements->at(1))->setGrid(grid);
}