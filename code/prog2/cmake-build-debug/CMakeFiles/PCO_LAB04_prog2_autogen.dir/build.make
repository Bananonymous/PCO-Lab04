# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/leon/pco/pco24_lab04/code/prog2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug

# Utility rule file for PCO_LAB04_prog2_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/PCO_LAB04_prog2_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PCO_LAB04_prog2_autogen.dir/progress.make

CMakeFiles/PCO_LAB04_prog2_autogen: PCO_LAB04_prog2_autogen/timestamp

PCO_LAB04_prog2_autogen/timestamp: /usr/lib/qt5/bin/moc
PCO_LAB04_prog2_autogen/timestamp: /usr/lib/qt5/bin/uic
PCO_LAB04_prog2_autogen/timestamp: CMakeFiles/PCO_LAB04_prog2_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target PCO_LAB04_prog2"
	/usr/bin/cmake -E cmake_autogen /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug/CMakeFiles/PCO_LAB04_prog2_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug/PCO_LAB04_prog2_autogen/timestamp

PCO_LAB04_prog2_autogen: CMakeFiles/PCO_LAB04_prog2_autogen
PCO_LAB04_prog2_autogen: PCO_LAB04_prog2_autogen/timestamp
PCO_LAB04_prog2_autogen: CMakeFiles/PCO_LAB04_prog2_autogen.dir/build.make
.PHONY : PCO_LAB04_prog2_autogen

# Rule to build all files generated by this target.
CMakeFiles/PCO_LAB04_prog2_autogen.dir/build: PCO_LAB04_prog2_autogen
.PHONY : CMakeFiles/PCO_LAB04_prog2_autogen.dir/build

CMakeFiles/PCO_LAB04_prog2_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PCO_LAB04_prog2_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PCO_LAB04_prog2_autogen.dir/clean

CMakeFiles/PCO_LAB04_prog2_autogen.dir/depend:
	cd /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leon/pco/pco24_lab04/code/prog2 /home/leon/pco/pco24_lab04/code/prog2 /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug /home/leon/pco/pco24_lab04/code/prog2/cmake-build-debug/CMakeFiles/PCO_LAB04_prog2_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PCO_LAB04_prog2_autogen.dir/depend

