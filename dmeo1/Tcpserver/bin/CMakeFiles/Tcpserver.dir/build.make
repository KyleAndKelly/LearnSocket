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
CMAKE_SOURCE_DIR = /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin

# Include any dependencies generated for this target.
include CMakeFiles/Tcpserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tcpserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tcpserver.dir/flags.make

CMakeFiles/Tcpserver.dir/Tcpserver.c.o: CMakeFiles/Tcpserver.dir/flags.make
CMakeFiles/Tcpserver.dir/Tcpserver.c.o: ../Tcpserver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Tcpserver.dir/Tcpserver.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Tcpserver.dir/Tcpserver.c.o   -c /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/Tcpserver.c

CMakeFiles/Tcpserver.dir/Tcpserver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Tcpserver.dir/Tcpserver.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/Tcpserver.c > CMakeFiles/Tcpserver.dir/Tcpserver.c.i

CMakeFiles/Tcpserver.dir/Tcpserver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Tcpserver.dir/Tcpserver.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/Tcpserver.c -o CMakeFiles/Tcpserver.dir/Tcpserver.c.s

CMakeFiles/Tcpserver.dir/Tcpserver.c.o.requires:

.PHONY : CMakeFiles/Tcpserver.dir/Tcpserver.c.o.requires

CMakeFiles/Tcpserver.dir/Tcpserver.c.o.provides: CMakeFiles/Tcpserver.dir/Tcpserver.c.o.requires
	$(MAKE) -f CMakeFiles/Tcpserver.dir/build.make CMakeFiles/Tcpserver.dir/Tcpserver.c.o.provides.build
.PHONY : CMakeFiles/Tcpserver.dir/Tcpserver.c.o.provides

CMakeFiles/Tcpserver.dir/Tcpserver.c.o.provides.build: CMakeFiles/Tcpserver.dir/Tcpserver.c.o


CMakeFiles/Tcpserver.dir/error.c.o: CMakeFiles/Tcpserver.dir/flags.make
CMakeFiles/Tcpserver.dir/error.c.o: ../error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Tcpserver.dir/error.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Tcpserver.dir/error.c.o   -c /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/error.c

CMakeFiles/Tcpserver.dir/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Tcpserver.dir/error.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/error.c > CMakeFiles/Tcpserver.dir/error.c.i

CMakeFiles/Tcpserver.dir/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Tcpserver.dir/error.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/error.c -o CMakeFiles/Tcpserver.dir/error.c.s

CMakeFiles/Tcpserver.dir/error.c.o.requires:

.PHONY : CMakeFiles/Tcpserver.dir/error.c.o.requires

CMakeFiles/Tcpserver.dir/error.c.o.provides: CMakeFiles/Tcpserver.dir/error.c.o.requires
	$(MAKE) -f CMakeFiles/Tcpserver.dir/build.make CMakeFiles/Tcpserver.dir/error.c.o.provides.build
.PHONY : CMakeFiles/Tcpserver.dir/error.c.o.provides

CMakeFiles/Tcpserver.dir/error.c.o.provides.build: CMakeFiles/Tcpserver.dir/error.c.o


# Object files for target Tcpserver
Tcpserver_OBJECTS = \
"CMakeFiles/Tcpserver.dir/Tcpserver.c.o" \
"CMakeFiles/Tcpserver.dir/error.c.o"

# External object files for target Tcpserver
Tcpserver_EXTERNAL_OBJECTS =

Tcpserver: CMakeFiles/Tcpserver.dir/Tcpserver.c.o
Tcpserver: CMakeFiles/Tcpserver.dir/error.c.o
Tcpserver: CMakeFiles/Tcpserver.dir/build.make
Tcpserver: CMakeFiles/Tcpserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Tcpserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tcpserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tcpserver.dir/build: Tcpserver

.PHONY : CMakeFiles/Tcpserver.dir/build

CMakeFiles/Tcpserver.dir/requires: CMakeFiles/Tcpserver.dir/Tcpserver.c.o.requires
CMakeFiles/Tcpserver.dir/requires: CMakeFiles/Tcpserver.dir/error.c.o.requires

.PHONY : CMakeFiles/Tcpserver.dir/requires

CMakeFiles/Tcpserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tcpserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tcpserver.dir/clean

CMakeFiles/Tcpserver.dir/depend:
	cd /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin /home/kylechen/Work/Project/APUEProject/LearnSocket/dmeo1/Tcpserver/bin/CMakeFiles/Tcpserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tcpserver.dir/depend
