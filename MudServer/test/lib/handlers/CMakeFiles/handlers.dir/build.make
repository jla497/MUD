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
include lib/handlers/CMakeFiles/handlers.dir/depend.make

# Include the progress variables for this target.
include lib/handlers/CMakeFiles/handlers.dir/progress.make

# Include the compile flags for this target's objects.
include lib/handlers/CMakeFiles/handlers.dir/flags.make

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o: lib/handlers/CMakeFiles/handlers.dir/flags.make
lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o: ../lib/handlers/PlayHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/handlers.dir/PlayHandler.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/PlayHandler.cpp

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/handlers.dir/PlayHandler.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/PlayHandler.cpp > CMakeFiles/handlers.dir/PlayHandler.cpp.i

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/handlers.dir/PlayHandler.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/PlayHandler.cpp -o CMakeFiles/handlers.dir/PlayHandler.cpp.s

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.requires:

.PHONY : lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.requires

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.provides: lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.requires
	$(MAKE) -f lib/handlers/CMakeFiles/handlers.dir/build.make lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.provides.build
.PHONY : lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.provides

lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.provides.build: lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o


lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o: lib/handlers/CMakeFiles/handlers.dir/flags.make
lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o: ../lib/handlers/LoginHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/handlers.dir/LoginHandler.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/LoginHandler.cpp

lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/handlers.dir/LoginHandler.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/LoginHandler.cpp > CMakeFiles/handlers.dir/LoginHandler.cpp.i

lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/handlers.dir/LoginHandler.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers/LoginHandler.cpp -o CMakeFiles/handlers.dir/LoginHandler.cpp.s

lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.requires:

.PHONY : lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.requires

lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.provides: lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.requires
	$(MAKE) -f lib/handlers/CMakeFiles/handlers.dir/build.make lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.provides.build
.PHONY : lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.provides

lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.provides.build: lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o


# Object files for target handlers
handlers_OBJECTS = \
"CMakeFiles/handlers.dir/PlayHandler.cpp.o" \
"CMakeFiles/handlers.dir/LoginHandler.cpp.o"

# External object files for target handlers
handlers_EXTERNAL_OBJECTS =

lib/libhandlers.a: lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o
lib/libhandlers.a: lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o
lib/libhandlers.a: lib/handlers/CMakeFiles/handlers.dir/build.make
lib/libhandlers.a: lib/handlers/CMakeFiles/handlers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../libhandlers.a"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && $(CMAKE_COMMAND) -P CMakeFiles/handlers.dir/cmake_clean_target.cmake
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/handlers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/handlers/CMakeFiles/handlers.dir/build: lib/libhandlers.a

.PHONY : lib/handlers/CMakeFiles/handlers.dir/build

lib/handlers/CMakeFiles/handlers.dir/requires: lib/handlers/CMakeFiles/handlers.dir/PlayHandler.cpp.o.requires
lib/handlers/CMakeFiles/handlers.dir/requires: lib/handlers/CMakeFiles/handlers.dir/LoginHandler.cpp.o.requires

.PHONY : lib/handlers/CMakeFiles/handlers.dir/requires

lib/handlers/CMakeFiles/handlers.dir/clean:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers && $(CMAKE_COMMAND) -P CMakeFiles/handlers.dir/cmake_clean.cmake
.PHONY : lib/handlers/CMakeFiles/handlers.dir/clean

lib/handlers/CMakeFiles/handlers.dir/depend:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jla497/CMPT373/adventure2018/MudServer /home/jla497/CMPT373/adventure2018/MudServer/lib/handlers /home/jla497/CMPT373/adventure2018/MudServer/test /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers /home/jla497/CMPT373/adventure2018/MudServer/test/lib/handlers/CMakeFiles/handlers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/handlers/CMakeFiles/handlers.dir/depend
