#include "testClasses.h"
#include "../src/editor/loadTextFile.h"
#include <cstdio>
#include "../src/editor/controller/editorController.h"
#include "../src/editor/view/editorView.h"

class TestEditorView : public IEditorView
{
public:
    bool out1 = true;
    std::string nextOutput1 = "";
    std::string nextOutput2 = "";
    int state = 0;

    std::string showOutput(std::string out)
    {
        if (out1)
        {
            out1 = false;
            return nextOutput1;
        }
        out1 = true;
        return nextOutput2;
    }
    int init() override { return 0; }
    void setCallback(SEngine::IEngineCallback *callback) override {}
    std::string getText() override { return nextOutput1; }
    void setState(int state) { this->state = state; }
    void setGrid(std::vector<std::vector<SEngine::Sprite> *> *grid) {}
};

TEST_CASE("Import text file time")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithWincon2");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    REQUIRE(grid->getLevel()->size() == 15);
    REQUIRE(grid->getWinCondition() == WinCondition(TIME, 20));
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);
    grid = new Grid();
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(grid->getLevel()->size() == 15);
    REQUIRE(grid->getWinCondition() == WinCondition(TIME, 20));
}
TEST_CASE("Import text file score")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithWincon");
    Grid *grid = new Grid();
    loadLevelFromTextFile(path.c_str(), grid);
    REQUIRE(grid->getLevel()->size() == 20);
    REQUIRE(grid->getWinCondition() == WinCondition(SCORE, 40));
    path.append("Binary");
    saveGridAsBinaryFile(path, grid);
    grid = new Grid();
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(grid->getLevel()->size() == 20);
    REQUIRE(grid->getWinCondition() == WinCondition(SCORE, 40));
}
TEST_CASE("Import File with teleporter and Mob")
{
    string path = RESOURCE_DIR;
    path.append("/tests/level/levelWithTeleporter");
    Grid *grid = new Grid();
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(dynamic_cast<Teleporter *>(grid->getLevel()->at(3)->at(3)));
    REQUIRE(dynamic_cast<Mob *>(grid->getLevel()->at(10)->at(10)));
    saveGridAsBinaryFile(path, grid);
    loadLevelFromBinaryFile(path, grid);
    REQUIRE(dynamic_cast<Teleporter *>(grid->getLevel()->at(3)->at(3)));
    REQUIRE(dynamic_cast<Mob *>(grid->getLevel()->at(10)->at(10)));
}
TEST_CASE("Editor controller")
{
    /*  TestEditorView *view = new TestEditorView();
      EditorController *controller = new EditorController(view);
      view->out1 = true;
      view->nextOutput1 = "0";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 0);
      view->out1 = true;
      view->nextOutput1 = "1";
      view->nextOutput2 = "/test/level/level1";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 1);
      view->out1 = true;
      view->nextOutput1 = "4";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 0);
      view->out1 = true;
      view->nextOutput1 = "2";
      controller->mainLoopIteration();
      REQUIRE(controller->exit);
      controller->exit = false;
      view->out1 = true;
      view->nextOutput1 = "1";
      view->nextOutput2 = "/test/level/level1";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 1);
      view->out1 = true;
      view->nextOutput1 = "3";
      view->nextOutput2 = "3";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 2);
      view->out1 = true;
      view->nextOutput1 = "1";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 2);
      view->out1 = true;
      view->nextOutput1 = "2";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 2);
      view->out1 = true;
      view->nextOutput1 = "3";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 2);
      view->out1 = true;
      view->nextOutput1 = "5";
      controller->mainLoopIteration();
      REQUIRE(controller->state == 1);*/
}
TEST_CASE("Editor controller new")
{
    TestEditorView *view = new TestEditorView();
    EditorController *controller = new EditorController(view);
    view->nextOutput1 = "/test/level/level1";
    controller->reactOnInput(GLFW_KEY_ENTER);
    REQUIRE(controller->state == 1);
    REQUIRE(controller->grid->getGridSizeX() == 20);
    REQUIRE(view->state == 1);
    controller->reactOnInput(GLFW_KEY_F25);
    REQUIRE(controller->state == 0);
    controller->reactOnInput(GLFW_KEY_F25);
    REQUIRE(controller->exit);
}
TEST_CASE("Get Sprite vector")
{
    TestEditorView *view = new TestEditorView();
    EditorController *controller = new EditorController(view);
    view->nextOutput1 = "/test/level/level1";
    controller->reactOnInput(GLFW_KEY_ENTER);
    REQUIRE(controller->state == 1);
    std::vector<std::vector<SEngine::Sprite> *> *spriteVector = controller->getSpriteVector();
    REQUIRE(spriteVector->size() == 20);
    REQUIRE(spriteVector->at(1)->size() == 20);
}