#include "testClasses.h"
#include "../src/view/engine/elements/image.h"
#include "../src/view/engine/elements/textInput.h"

using SEngine::Image, SEngine::StretchMode, SEngine::TextInput;

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
    gridController->addMob(new Enemy(10, 10));
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
    spriteGrid2->click(NULL, 0, 0);
    REQUIRE(spriteGrid2->getFocussedSpriteX() == 0);
    REQUIRE(spriteGrid2->getFocussedSpriteY() == 0);
    spriteGrid2->click(NULL, 40, 0);
    REQUIRE(spriteGrid2->getFocussedSpriteX() == 1);
    REQUIRE(spriteGrid2->getFocussedSpriteY() == 0);
    spriteGrid2->click(NULL, 40, 200);
    REQUIRE(spriteGrid2->getFocussedSpriteX() == 1);
    REQUIRE(spriteGrid2->getFocussedSpriteY() == 6);
}

TEST_CASE("Image compute texture fractions")
{
    Image *image = new Image(0, 0, 64, 64, static_cast<string>(RESOURCE_DIR).append("/test/textures/background.png"), StretchMode::ORIGINAL);
    REQUIRE(image->computeTextureFraction(32, 64) == 2.0f);
    REQUIRE(image->computeTextureFraction(32, 16) == 0.5f);
    image = new Image(0, 0, 64, 64, static_cast<string>(RESOURCE_DIR).append("/test/textures/background.png"), StretchMode::FIT_TO_SIZE);
    REQUIRE(image->computeTextureFraction(32, 64) == 1.0f);
    REQUIRE(image->computeTextureFraction(32, 16) == 1.0f);
}

TEST_CASE("TextInput element")
{
    TextInput *input = new TextInput(0, 0, 20, 20);
    input->click(input, 0, 0);
    input->callback(input, GLFW_KEY_BACKSPACE);
    input->callback(input, GLFW_KEY_BACKSPACE);
    input->callback(input, 'a');
    REQUIRE(input->text.compare("a") == 0);
    SEngine::RenderData *data = input->createRenderData();
    REQUIRE(data->getVertices().size() == 84);
    REQUIRE(data->getIndices().size() == 18);
    input->setFocussed(false);
    SEngine::RenderData *data2 = input->createRenderData();
    REQUIRE(data2->getVertices().size() == 84);
    REQUIRE(data2->getIndices().size() == 18);
    REQUIRE(data->getTexture() != data2->getTexture());
    input->setFocussed(true);
    input->reactOnInput(GLFW_KEY_ESCAPE);
    SEngine::RenderData *data3 = input->createRenderData();
    REQUIRE(data3->getTexture() == data2->getTexture());
}