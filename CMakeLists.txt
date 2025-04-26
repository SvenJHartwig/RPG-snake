cmake_minimum_required (VERSION 3.28)
project (Snake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(main src/main.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_directories(main PRIVATE /usr/local/lib /usr/lib64 /usr/include)
include_directories (/usr/include/freetype2 includes)
target_link_libraries(main PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(main PRIVATE SFML::Audio)

target_compile_definitions(main PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")

add_executable(editor src/editor.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_compile_definitions(editor PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")
target_link_directories(editor PRIVATE /usr/local/lib /usr/lib64 /usr/include)
target_link_libraries(editor PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(editor PRIVATE SFML::Audio)


# Copy CTestCustom.cmake to build folder
configure_file(
    ${CMAKE_SOURCE_DIR}/CTestCustom.cmake
    ${CMAKE_BINARY_DIR}/CTestCustom.cmake
    COPYONLY
)

find_package(SFML 3 REQUIRED COMPONENTS Audio)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests tests/test.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_directories(tests PRIVATE /usr/local/lib /usr/lib64)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(tests PRIVATE SFML::Audio)
target_compile_options(tests PRIVATE -coverage)
target_link_options(tests PRIVATE -coverage)
target_compile_definitions(tests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")
include(CTest)

add_test(NAME test COMMAND tests)

add_executable(launchTests tests/launchTest.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_libraries(launchTests PRIVATE Catch2::Catch2WithMain)
target_compile_options(launchTests PRIVATE -coverage)
target_link_libraries(launchTests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(launchTests PRIVATE SFML::Audio)
target_link_options(launchTests PRIVATE -coverage)
target_compile_definitions(launchTests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")

add_test(NAME launchTest COMMAND launchTests)

add_executable(engineTests tests/engineTest.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_directories(engineTests PRIVATE /usr/local/lib /usr/lib64 /usr/include)
target_link_libraries(engineTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(engineTests PRIVATE SFML::Audio)
target_compile_options(engineTests PRIVATE -coverage)
target_link_libraries(engineTests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_options(engineTests PRIVATE -coverage)
target_compile_definitions(engineTests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")

add_test(NAME engineTests COMMAND engineTests)

add_executable(gameModeTests tests/gameModeTest.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_directories(gameModeTests PRIVATE /usr/local/lib /usr/lib64 /usr/include)
target_link_libraries(gameModeTests PRIVATE Catch2::Catch2WithMain)
target_compile_options(gameModeTests PRIVATE -coverage)
target_link_libraries(gameModeTests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(gameModeTests PRIVATE SFML::Audio)
target_link_options(gameModeTests PRIVATE -coverage)
target_compile_definitions(gameModeTests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")

add_test(NAME gameModeTests COMMAND gameModeTests)

add_executable(editorTests tests/editorTest.cpp src/model/grid.cpp src/model/snake.cpp src/controller/gridController.cpp src/controller/gameController.cpp 
    src/view/glView.cpp src/view/engine/TextRenderer/TextRenderer.cpp src/view/engine/elements/button.cpp src/view/engine/elements/scene.cpp
    src/view/engine/elements/element.cpp src/view/engine/renderEngine.cpp src/view/engine/elements/text.cpp src/view/engine/elements/spriteGrid.cpp
    src/view/engine/shaders/shader.cpp src/view/engine/iRenderEngine.cpp src/model/winCondition.cpp src/model/gameMode.cpp src/commonFunctions.cpp
    src/view/engine/elements/image.cpp src/view/engine/renderData.cpp src/model/mob.cpp src/model/gridElement.cpp src/controller/soundController.cpp
    src/model/quest.cpp src/model/teleporter.cpp src/view/engine/elements/textInput.cpp src/editor/controller/editorController.cpp src/editor/view/editorView.cpp 
    src/editor/loadTextFile.cpp src/model/npc.cpp src/view/dialog.cpp src/services/gameModeService.cpp)
target_link_directories(editorTests PRIVATE /usr/local/lib /usr/lib64)
target_link_libraries(editorTests PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(editorTests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")
target_link_directories(editorTests PRIVATE /usr/local/lib /usr/lib64 /usr/include)
target_link_libraries(editorTests PRIVATE glfw3 rt m dl GLEW GLU OpenGL freetype)
target_link_libraries(editorTests PRIVATE SFML::Audio)
target_compile_options(editorTests PRIVATE -coverage)
target_link_options(editorTests PRIVATE -coverage)
target_compile_definitions(editorTests PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/src/resources")

add_test(NAME editorTests COMMAND editorTests)
