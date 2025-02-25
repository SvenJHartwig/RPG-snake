# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sven/Dokumente/workplace/cProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sven/Dokumente/workplace/cProject

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sven/Dokumente/workplace/cProject/CMakeFiles /home/sven/Dokumente/workplace/cProject//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sven/Dokumente/workplace/cProject/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

#=============================================================================
# Target rules for targets named tests

# Build rule for target.
tests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 tests
.PHONY : tests

# fast build rule for target.
tests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/build
.PHONY : tests/fast

TextRenderer/TextRenderer.o: TextRenderer/TextRenderer.cpp.o
.PHONY : TextRenderer/TextRenderer.o

# target to build an object file
TextRenderer/TextRenderer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextRenderer/TextRenderer.cpp.o
.PHONY : TextRenderer/TextRenderer.cpp.o

TextRenderer/TextRenderer.i: TextRenderer/TextRenderer.cpp.i
.PHONY : TextRenderer/TextRenderer.i

# target to preprocess a source file
TextRenderer/TextRenderer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextRenderer/TextRenderer.cpp.i
.PHONY : TextRenderer/TextRenderer.cpp.i

TextRenderer/TextRenderer.s: TextRenderer/TextRenderer.cpp.s
.PHONY : TextRenderer/TextRenderer.s

# target to generate assembly for a file
TextRenderer/TextRenderer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/TextRenderer/TextRenderer.cpp.s
.PHONY : TextRenderer/TextRenderer.cpp.s

controller/gameController.o: controller/gameController.cpp.o
.PHONY : controller/gameController.o

# target to build an object file
controller/gameController.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gameController.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gameController.cpp.o
.PHONY : controller/gameController.cpp.o

controller/gameController.i: controller/gameController.cpp.i
.PHONY : controller/gameController.i

# target to preprocess a source file
controller/gameController.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gameController.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gameController.cpp.i
.PHONY : controller/gameController.cpp.i

controller/gameController.s: controller/gameController.cpp.s
.PHONY : controller/gameController.s

# target to generate assembly for a file
controller/gameController.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gameController.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gameController.cpp.s
.PHONY : controller/gameController.cpp.s

controller/gridController.o: controller/gridController.cpp.o
.PHONY : controller/gridController.o

# target to build an object file
controller/gridController.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gridController.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gridController.cpp.o
.PHONY : controller/gridController.cpp.o

controller/gridController.i: controller/gridController.cpp.i
.PHONY : controller/gridController.i

# target to preprocess a source file
controller/gridController.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gridController.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gridController.cpp.i
.PHONY : controller/gridController.cpp.i

controller/gridController.s: controller/gridController.cpp.s
.PHONY : controller/gridController.s

# target to generate assembly for a file
controller/gridController.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/controller/gridController.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/controller/gridController.cpp.s
.PHONY : controller/gridController.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

model/grid.o: model/grid.cpp.o
.PHONY : model/grid.o

# target to build an object file
model/grid.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/grid.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/grid.cpp.o
.PHONY : model/grid.cpp.o

model/grid.i: model/grid.cpp.i
.PHONY : model/grid.i

# target to preprocess a source file
model/grid.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/grid.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/grid.cpp.i
.PHONY : model/grid.cpp.i

model/grid.s: model/grid.cpp.s
.PHONY : model/grid.s

# target to generate assembly for a file
model/grid.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/grid.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/grid.cpp.s
.PHONY : model/grid.cpp.s

model/snake.o: model/snake.cpp.o
.PHONY : model/snake.o

# target to build an object file
model/snake.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/snake.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/snake.cpp.o
.PHONY : model/snake.cpp.o

model/snake.i: model/snake.cpp.i
.PHONY : model/snake.i

# target to preprocess a source file
model/snake.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/snake.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/snake.cpp.i
.PHONY : model/snake.cpp.i

model/snake.s: model/snake.cpp.s
.PHONY : model/snake.s

# target to generate assembly for a file
model/snake.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/model/snake.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/model/snake.cpp.s
.PHONY : model/snake.cpp.s

test.o: test.cpp.o
.PHONY : test.o

# target to build an object file
test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i
.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s
.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/test.cpp.s
.PHONY : test.cpp.s

view/cliView.o: view/cliView.cpp.o
.PHONY : view/cliView.o

# target to build an object file
view/cliView.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/cliView.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/view/cliView.cpp.o
.PHONY : view/cliView.cpp.o

view/cliView.i: view/cliView.cpp.i
.PHONY : view/cliView.i

# target to preprocess a source file
view/cliView.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/cliView.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/view/cliView.cpp.i
.PHONY : view/cliView.cpp.i

view/cliView.s: view/cliView.cpp.s
.PHONY : view/cliView.s

# target to generate assembly for a file
view/cliView.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/cliView.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/view/cliView.cpp.s
.PHONY : view/cliView.cpp.s

view/elements/button.o: view/elements/button.cpp.o
.PHONY : view/elements/button.o

# target to build an object file
view/elements/button.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/button.cpp.o
.PHONY : view/elements/button.cpp.o

view/elements/button.i: view/elements/button.cpp.i
.PHONY : view/elements/button.i

# target to preprocess a source file
view/elements/button.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/button.cpp.i
.PHONY : view/elements/button.cpp.i

view/elements/button.s: view/elements/button.cpp.s
.PHONY : view/elements/button.s

# target to generate assembly for a file
view/elements/button.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/button.cpp.s
.PHONY : view/elements/button.cpp.s

view/elements/element.o: view/elements/element.cpp.o
.PHONY : view/elements/element.o

# target to build an object file
view/elements/element.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/element.cpp.o
.PHONY : view/elements/element.cpp.o

view/elements/element.i: view/elements/element.cpp.i
.PHONY : view/elements/element.i

# target to preprocess a source file
view/elements/element.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/element.cpp.i
.PHONY : view/elements/element.cpp.i

view/elements/element.s: view/elements/element.cpp.s
.PHONY : view/elements/element.s

# target to generate assembly for a file
view/elements/element.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/element.cpp.s
.PHONY : view/elements/element.cpp.s

view/elements/scene.o: view/elements/scene.cpp.o
.PHONY : view/elements/scene.o

# target to build an object file
view/elements/scene.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/scene.cpp.o
.PHONY : view/elements/scene.cpp.o

view/elements/scene.i: view/elements/scene.cpp.i
.PHONY : view/elements/scene.i

# target to preprocess a source file
view/elements/scene.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/scene.cpp.i
.PHONY : view/elements/scene.cpp.i

view/elements/scene.s: view/elements/scene.cpp.s
.PHONY : view/elements/scene.s

# target to generate assembly for a file
view/elements/scene.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/elements/scene.cpp.s
.PHONY : view/elements/scene.cpp.s

view/glView.o: view/glView.cpp.o
.PHONY : view/glView.o

# target to build an object file
view/glView.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/glView.cpp.o
.PHONY : view/glView.cpp.o

view/glView.i: view/glView.cpp.i
.PHONY : view/glView.i

# target to preprocess a source file
view/glView.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/glView.cpp.i
.PHONY : view/glView.cpp.i

view/glView.s: view/glView.cpp.s
.PHONY : view/glView.s

# target to generate assembly for a file
view/glView.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/view/glView.cpp.s
.PHONY : view/glView.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... main"
	@echo "... tests"
	@echo "... TextRenderer/TextRenderer.o"
	@echo "... TextRenderer/TextRenderer.i"
	@echo "... TextRenderer/TextRenderer.s"
	@echo "... controller/gameController.o"
	@echo "... controller/gameController.i"
	@echo "... controller/gameController.s"
	@echo "... controller/gridController.o"
	@echo "... controller/gridController.i"
	@echo "... controller/gridController.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... model/grid.o"
	@echo "... model/grid.i"
	@echo "... model/grid.s"
	@echo "... model/snake.o"
	@echo "... model/snake.i"
	@echo "... model/snake.s"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
	@echo "... view/cliView.o"
	@echo "... view/cliView.i"
	@echo "... view/cliView.s"
	@echo "... view/elements/button.o"
	@echo "... view/elements/button.i"
	@echo "... view/elements/button.s"
	@echo "... view/elements/element.o"
	@echo "... view/elements/element.i"
	@echo "... view/elements/element.s"
	@echo "... view/elements/scene.o"
	@echo "... view/elements/scene.i"
	@echo "... view/elements/scene.s"
	@echo "... view/glView.o"
	@echo "... view/glView.i"
	@echo "... view/glView.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

