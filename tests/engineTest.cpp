#include <catch2/catch.hpp>
#include "testClasses.h"

TEST_CASE("Button produces a colored rectangle")
{
    RenderEngine *engine = new RenderEngine();
    engine->init();
    Button *button = new Button(0, 0, 20, 20);
    button->text = "Test";
    RenderData *data = button->createRenderData();
    REQUIRE(button->text == "Test");
    REQUIRE(data->getVertices().size() == 28);
    REQUIRE(data->getIndices().size() == 6);
}

TEST_CASE("Text renders text")
{
    RenderEngine *engine = new RenderEngine();
    engine->init();
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