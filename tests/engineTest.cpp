#include "testClasses.h"

TEST_CASE("Button produces a colored rectangle")
{
    RenderEngine *engine = new RenderEngine();
    engine->init();
    Button *button = new Button(0, 0, 20, 20);
    button->text = "Test";
    RenderData *data = button->createRenderData();
    REQUIRE(button->text == "Test");
    REQUIRE(data->getVertices().size() == 84);
    REQUIRE(data->getIndices().size() == 18);
}

TEST_CASE("Text renders text")
{
    Text *text = new Text(0, 0, 20, 20);
    text->text = "Test";
    RenderData *data = text->createRenderData();
    REQUIRE(text->text == "Test");
    REQUIRE(data->getText() == "Test");
    REQUIRE(data->getTextPosX() == 0);
    REQUIRE(data->getTextPosY() == 20);
}

TEST_CASE("Button with texture")
{
    Button *button = new Button(0, 0, 20, 20);
    button->text = "Test";
}

TEST_CASE("Sprite grid tests")
{
    // Without sprites
    SpriteGrid *spriteGrid = new SpriteGrid(0, 0, 20, 20, "", 0.5f);
    RenderData *data = spriteGrid->createRenderData();
    REQUIRE(data->getVertices().size() == 0);
    REQUIRE(data->getIndices().size() == 0);
    // With grid, but without texture map
    GridController *gridController = new GridController(new TestEatListener());
    gridController->setRNG(new TestGenerator());
    gridController->updateGrid();
    spriteGrid->setGrid(gridController->getSpriteVector());
    data = spriteGrid->createRenderData();
    REQUIRE(data->getVertices().size() == 11200);
    REQUIRE(data->getIndices().size() == 2400);
    // With texture map, but without grid
    std::string texturePath = ((std::string)RESOURCE_DIR).append("/textures/grid.png");
    SpriteGrid *spriteGrid2 = new SpriteGrid(0, 0, 200, 100, texturePath, 0.25f);
    data = spriteGrid2->createRenderData();
    REQUIRE(data->getVertices().size() == 0);
    REQUIRE(data->getIndices().size() == 0);
    // With texture map and grid
    spriteGrid2->setGrid(gridController->getSpriteVector());
    data = spriteGrid2->createRenderData();
    REQUIRE(data->getVertices().size() == 11200);
    REQUIRE(data->getIndices().size() == 2400);
}