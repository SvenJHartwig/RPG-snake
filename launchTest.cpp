#include <catch2/catch.hpp>
#include "./view/engine/renderEngine.h"

TEST_CASE("Initialize OpenGL")
{
    RenderEngine *engine = new RenderEngine();
    REQUIRE(engine->init() == 0);
}