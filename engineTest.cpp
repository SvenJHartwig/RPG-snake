#include <catch2/catch.hpp>
#include "view/engine/elements/button.h"
#include "view/engine/elements/text.h"

TEST_CASE("Button produces a colored rectangle")
{
    Button *button = new Button(0, 0, 20, 20);
    button->text = "Test";
    RenderData *data = button->createRenderData();
    REQUIRE(button->text == "Test");
    REQUIRE(data->getVertices().size() == 20);
    REQUIRE(data->getIndices().size() == 6);
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