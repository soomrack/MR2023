# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_SOURCE_DIR = "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build"

# Include any dependencies generated for this target.
include CMakeFiles/container_exception.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/container_exception.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/container_exception.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/container_exception.dir/flags.make

CMakeFiles/container_exception.dir/src/container_exception.cpp.o: CMakeFiles/container_exception.dir/flags.make
CMakeFiles/container_exception.dir/src/container_exception.cpp.o: ../src/container_exception.cpp
CMakeFiles/container_exception.dir/src/container_exception.cpp.o: CMakeFiles/container_exception.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/container_exception.dir/src/container_exception.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/container_exception.dir/src/container_exception.cpp.o -MF CMakeFiles/container_exception.dir/src/container_exception.cpp.o.d -o CMakeFiles/container_exception.dir/src/container_exception.cpp.o -c "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/src/container_exception.cpp"

CMakeFiles/container_exception.dir/src/container_exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/container_exception.dir/src/container_exception.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/src/container_exception.cpp" > CMakeFiles/container_exception.dir/src/container_exception.cpp.i

CMakeFiles/container_exception.dir/src/container_exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/container_exception.dir/src/container_exception.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/src/container_exception.cpp" -o CMakeFiles/container_exception.dir/src/container_exception.cpp.s

# Object files for target container_exception
container_exception_OBJECTS = \
"CMakeFiles/container_exception.dir/src/container_exception.cpp.o"

# External object files for target container_exception
container_exception_EXTERNAL_OBJECTS =

libcontainer_exception.a: CMakeFiles/container_exception.dir/src/container_exception.cpp.o
libcontainer_exception.a: CMakeFiles/container_exception.dir/build.make
libcontainer_exception.a: CMakeFiles/container_exception.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcontainer_exception.a"
	$(CMAKE_COMMAND) -P CMakeFiles/container_exception.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/container_exception.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/container_exception.dir/build: libcontainer_exception.a
.PHONY : CMakeFiles/container_exception.dir/build

CMakeFiles/container_exception.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/container_exception.dir/cmake_clean.cmake
.PHONY : CMakeFiles/container_exception.dir/clean

CMakeFiles/container_exception.dir/depend:
	cd "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5" "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5" "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build" "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build" "/home/simeonidi03/Documents/GitHub/MR2023/Papasymeonidis Aristotelis/Task5/build/CMakeFiles/container_exception.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/container_exception.dir/depend

