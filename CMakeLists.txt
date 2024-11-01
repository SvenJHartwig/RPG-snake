cmake_minimum_required (VERSION 2.9)
project (Tutorial)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(main main.cpp model/grid.cpp model/snake.cpp controller/gridController.cpp controller/gameController.cpp 
    view/cliView.cpp view/glView.cpp TextRenderer/TextRenderer.cpp view/elements/button.cpp view/elements/scene.cpp
    view/elements/element.cpp)
target_link_directories(main PRIVATE /usr/local/lib /usr/lib64)
include_directories (/usr/include/freetype2)
target_link_libraries(main PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_compile_definitions(main PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources")

find_package(Catch2 2 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test.cpp model/grid.cpp model/snake.cpp controller/gridController.cpp controller/gameController.cpp 
view/cliView.cpp view/glView.cpp TextRenderer/TextRenderer.cpp view/elements/button.cpp view/elements/scene.cpp
view/elements/element.cpp)
target_link_directories(tests PRIVATE /usr/local/lib /usr/lib64)
target_link_libraries(tests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_compile_options(tests PRIVATE -coverage)
target_link_options(tests PRIVATE -coverage)
target_compile_definitions(tests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources")
include(CTest)
add_test(NAME test COMMAND tests)
