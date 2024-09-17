cmake_minimum_required (VERSION 2.9)
project (Tutorial)
add_executable(main main.cpp model/grid.cpp model/snake.cpp controller/gridController.cpp controller/gameController.cpp view/cliView.cpp kbhit.cpp)

find_package(Catch2 2 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test.cpp model/grid.cpp model/snake.cpp controller/gridController.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)