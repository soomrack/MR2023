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
CMAKE_SOURCE_DIR = "/home/prlx/MR2023/Каримуллин Семён/Matrix"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/prlx/MR2023/Каримуллин Семён/Matrix/build"

# Include any dependencies generated for this target.
include CMakeFiles/matrix.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/matrix.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/matrix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrix.dir/flags.make

CMakeFiles/matrix.dir/Matrix.c.o: CMakeFiles/matrix.dir/flags.make
CMakeFiles/matrix.dir/Matrix.c.o: ../Matrix.c
CMakeFiles/matrix.dir/Matrix.c.o: CMakeFiles/matrix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/prlx/MR2023/Каримуллин Семён/Matrix/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/matrix.dir/Matrix.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/matrix.dir/Matrix.c.o -MF CMakeFiles/matrix.dir/Matrix.c.o.d -o CMakeFiles/matrix.dir/Matrix.c.o -c "/home/prlx/MR2023/Каримуллин Семён/Matrix/Matrix.c"

CMakeFiles/matrix.dir/Matrix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/matrix.dir/Matrix.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/prlx/MR2023/Каримуллин Семён/Matrix/Matrix.c" > CMakeFiles/matrix.dir/Matrix.c.i

CMakeFiles/matrix.dir/Matrix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/matrix.dir/Matrix.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/prlx/MR2023/Каримуллин Семён/Matrix/Matrix.c" -o CMakeFiles/matrix.dir/Matrix.c.s

# Object files for target matrix
matrix_OBJECTS = \
"CMakeFiles/matrix.dir/Matrix.c.o"

# External object files for target matrix
matrix_EXTERNAL_OBJECTS =

libmatrix.a: CMakeFiles/matrix.dir/Matrix.c.o
libmatrix.a: CMakeFiles/matrix.dir/build.make
libmatrix.a: CMakeFiles/matrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/prlx/MR2023/Каримуллин Семён/Matrix/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmatrix.a"
	$(CMAKE_COMMAND) -P CMakeFiles/matrix.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrix.dir/build: libmatrix.a
.PHONY : CMakeFiles/matrix.dir/build

CMakeFiles/matrix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrix.dir/clean

CMakeFiles/matrix.dir/depend:
	cd "/home/prlx/MR2023/Каримуллин Семён/Matrix/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/prlx/MR2023/Каримуллин Семён/Matrix" "/home/prlx/MR2023/Каримуллин Семён/Matrix" "/home/prlx/MR2023/Каримуллин Семён/Matrix/build" "/home/prlx/MR2023/Каримуллин Семён/Matrix/build" "/home/prlx/MR2023/Каримуллин Семён/Matrix/build/CMakeFiles/matrix.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/matrix.dir/depend

