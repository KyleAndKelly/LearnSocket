# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/select_server.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/select_server.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/select_server.dir/flags.make

bin/CMakeFiles/select_server.dir/server.cpp.o: bin/CMakeFiles/select_server.dir/flags.make
bin/CMakeFiles/select_server.dir/server.cpp.o: ../src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/select_server.dir/server.cpp.o"
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/select_server.dir/server.cpp.o -c /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/src/server.cpp

bin/CMakeFiles/select_server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/select_server.dir/server.cpp.i"
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/src/server.cpp > CMakeFiles/select_server.dir/server.cpp.i

bin/CMakeFiles/select_server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/select_server.dir/server.cpp.s"
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/src/server.cpp -o CMakeFiles/select_server.dir/server.cpp.s

bin/CMakeFiles/select_server.dir/server.cpp.o.requires:

.PHONY : bin/CMakeFiles/select_server.dir/server.cpp.o.requires

bin/CMakeFiles/select_server.dir/server.cpp.o.provides: bin/CMakeFiles/select_server.dir/server.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/select_server.dir/build.make bin/CMakeFiles/select_server.dir/server.cpp.o.provides.build
.PHONY : bin/CMakeFiles/select_server.dir/server.cpp.o.provides

bin/CMakeFiles/select_server.dir/server.cpp.o.provides.build: bin/CMakeFiles/select_server.dir/server.cpp.o


# Object files for target select_server
select_server_OBJECTS = \
"CMakeFiles/select_server.dir/server.cpp.o"

# External object files for target select_server
select_server_EXTERNAL_OBJECTS =

../bin/select_server: bin/CMakeFiles/select_server.dir/server.cpp.o
../bin/select_server: bin/CMakeFiles/select_server.dir/build.make
../bin/select_server: bin/CMakeFiles/select_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/select_server"
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/select_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/select_server.dir/build: ../bin/select_server

.PHONY : bin/CMakeFiles/select_server.dir/build

bin/CMakeFiles/select_server.dir/requires: bin/CMakeFiles/select_server.dir/server.cpp.o.requires

.PHONY : bin/CMakeFiles/select_server.dir/requires

bin/CMakeFiles/select_server.dir/clean:
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/select_server.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/select_server.dir/clean

bin/CMakeFiles/select_server.dir/depend:
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/src /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin /home/kylechen/Work/Project/APUEProject/LearnSocket/select_server/build/bin/CMakeFiles/select_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/select_server.dir/depend

