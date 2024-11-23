#include <catch2/catch.hpp>
#include "view/engine/elements/button.h"

TEST_CASE("Button produces a colored rectangle")
{
    Button *button = new Button(0, 0, 20, 20);
    button->text = "Test";
    RenderData *data = button->createRenderData();
    REQUIRE(button->text == "Test");
    REQUIRE(data->getVertices().size() == 20);
    REQUIRE(data->getIndices().size() == 6);
}