# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jla497/CMPT373/adventure2018/MudServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jla497/CMPT373/adventure2018/MudServer/test

# Include any dependencies generated for this target.
include lib/connectionman/CMakeFiles/connectionman.dir/depend.make

# Include the progress variables for this target.
include lib/connectionman/CMakeFiles/connectionman.dir/progress.make

# Include the compile flags for this target's objects.
include lib/connectionman/CMakeFiles/connectionman.dir/flags.make

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o: lib/connectionman/CMakeFiles/connectionman.dir/flags.make
lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o: ../lib/connectionman/ConnectionManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectionman.dir/ConnectionManager.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionManager.cpp

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectionman.dir/ConnectionManager.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionManager.cpp > CMakeFiles/connectionman.dir/ConnectionManager.cpp.i

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectionman.dir/ConnectionManager.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionManager.cpp -o CMakeFiles/connectionman.dir/ConnectionManager.cpp.s

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.requires:

.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.requires

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.provides: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.requires
	$(MAKE) -f lib/connectionman/CMakeFiles/connectionman.dir/build.make lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.provides.build
.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.provides

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.provides.build: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o


lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o: lib/connectionman/CMakeFiles/connectionman.dir/flags.make
lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o: ../lib/connectionman/ConnectionContainer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionContainer.cpp

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectionman.dir/ConnectionContainer.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionContainer.cpp > CMakeFiles/connectionman.dir/ConnectionContainer.cpp.i

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectionman.dir/ConnectionContainer.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman/ConnectionContainer.cpp -o CMakeFiles/connectionman.dir/ConnectionContainer.cpp.s

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.requires:

.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.requires

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.provides: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.requires
	$(MAKE) -f lib/connectionman/CMakeFiles/connectionman.dir/build.make lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.provides.build
.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.provides

lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.provides.build: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o


# Object files for target connectionman
connectionman_OBJECTS = \
"CMakeFiles/connectionman.dir/ConnectionManager.cpp.o" \
"CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o"

# External object files for target connectionman
connectionman_EXTERNAL_OBJECTS =

lib/libconnectionman.a: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o
lib/libconnectionman.a: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o
lib/libconnectionman.a: lib/connectionman/CMakeFiles/connectionman.dir/build.make
lib/libconnectionman.a: lib/connectionman/CMakeFiles/connectionman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../libconnectionman.a"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && $(CMAKE_COMMAND) -P CMakeFiles/connectionman.dir/cmake_clean_target.cmake
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/connectionman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/connectionman/CMakeFiles/connectionman.dir/build: lib/libconnectionman.a

.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/build

lib/connectionman/CMakeFiles/connectionman.dir/requires: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionManager.cpp.o.requires
lib/connectionman/CMakeFiles/connectionman.dir/requires: lib/connectionman/CMakeFiles/connectionman.dir/ConnectionContainer.cpp.o.requires

.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/requires

lib/connectionman/CMakeFiles/connectionman.dir/clean:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman && $(CMAKE_COMMAND) -P CMakeFiles/connectionman.dir/cmake_clean.cmake
.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/clean

lib/connectionman/CMakeFiles/connectionman.dir/depend:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jla497/CMPT373/adventure2018/MudServer /home/jla497/CMPT373/adventure2018/MudServer/lib/connectionman /home/jla497/CMPT373/adventure2018/MudServer/test /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman /home/jla497/CMPT373/adventure2018/MudServer/test/lib/connectionman/CMakeFiles/connectionman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/connectionman/CMakeFiles/connectionman.dir/depend

