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
include tools/client/CMakeFiles/chatclient.dir/depend.make

# Include the progress variables for this target.
include tools/client/CMakeFiles/chatclient.dir/progress.make

# Include the compile flags for this target's objects.
include tools/client/CMakeFiles/chatclient.dir/flags.make

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o: tools/client/CMakeFiles/chatclient.dir/flags.make
tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o: ../tools/client/chatclient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatclient.dir/chatclient.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/tools/client/chatclient.cpp

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatclient.dir/chatclient.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/tools/client/chatclient.cpp > CMakeFiles/chatclient.dir/chatclient.cpp.i

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatclient.dir/chatclient.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/tools/client/chatclient.cpp -o CMakeFiles/chatclient.dir/chatclient.cpp.s

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.requires:

.PHONY : tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.requires

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.provides: tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.requires
	$(MAKE) -f tools/client/CMakeFiles/chatclient.dir/build.make tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.provides.build
.PHONY : tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.provides

tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.provides.build: tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o


tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o: tools/client/CMakeFiles/chatclient.dir/flags.make
tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o: ../tools/client/ChatWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatclient.dir/ChatWindow.cpp.o -c /home/jla497/CMPT373/adventure2018/MudServer/tools/client/ChatWindow.cpp

tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatclient.dir/ChatWindow.cpp.i"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jla497/CMPT373/adventure2018/MudServer/tools/client/ChatWindow.cpp > CMakeFiles/chatclient.dir/ChatWindow.cpp.i

tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatclient.dir/ChatWindow.cpp.s"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jla497/CMPT373/adventure2018/MudServer/tools/client/ChatWindow.cpp -o CMakeFiles/chatclient.dir/ChatWindow.cpp.s

tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.requires:

.PHONY : tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.requires

tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.provides: tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.requires
	$(MAKE) -f tools/client/CMakeFiles/chatclient.dir/build.make tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.provides.build
.PHONY : tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.provides

tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.provides.build: tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o


# Object files for target chatclient
chatclient_OBJECTS = \
"CMakeFiles/chatclient.dir/chatclient.cpp.o" \
"CMakeFiles/chatclient.dir/ChatWindow.cpp.o"

# External object files for target chatclient
chatclient_EXTERNAL_OBJECTS =

bin/chatclient: tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o
bin/chatclient: tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o
bin/chatclient: tools/client/CMakeFiles/chatclient.dir/build.make
bin/chatclient: lib/libnetworking.a
bin/chatclient: /usr/lib/x86_64-linux-gnu/libboost_system.so
bin/chatclient: /usr/lib/x86_64-linux-gnu/libcurses.so
bin/chatclient: /usr/lib/x86_64-linux-gnu/libform.so
bin/chatclient: tools/client/CMakeFiles/chatclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jla497/CMPT373/adventure2018/MudServer/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/chatclient"
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chatclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/client/CMakeFiles/chatclient.dir/build: bin/chatclient

.PHONY : tools/client/CMakeFiles/chatclient.dir/build

tools/client/CMakeFiles/chatclient.dir/requires: tools/client/CMakeFiles/chatclient.dir/chatclient.cpp.o.requires
tools/client/CMakeFiles/chatclient.dir/requires: tools/client/CMakeFiles/chatclient.dir/ChatWindow.cpp.o.requires

.PHONY : tools/client/CMakeFiles/chatclient.dir/requires

tools/client/CMakeFiles/chatclient.dir/clean:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client && $(CMAKE_COMMAND) -P CMakeFiles/chatclient.dir/cmake_clean.cmake
.PHONY : tools/client/CMakeFiles/chatclient.dir/clean

tools/client/CMakeFiles/chatclient.dir/depend:
	cd /home/jla497/CMPT373/adventure2018/MudServer/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jla497/CMPT373/adventure2018/MudServer /home/jla497/CMPT373/adventure2018/MudServer/tools/client /home/jla497/CMPT373/adventure2018/MudServer/test /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client /home/jla497/CMPT373/adventure2018/MudServer/test/tools/client/CMakeFiles/chatclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/client/CMakeFiles/chatclient.dir/depend
