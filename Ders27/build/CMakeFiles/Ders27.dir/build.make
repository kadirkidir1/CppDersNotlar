# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/abdulkadir/CppDersNotlar/Ders27

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abdulkadir/CppDersNotlar/Ders27/build

# Include any dependencies generated for this target.
include CMakeFiles/Ders27.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ders27.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ders27.dir/flags.make

CMakeFiles/Ders27.dir/main.cpp.o: CMakeFiles/Ders27.dir/flags.make
CMakeFiles/Ders27.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abdulkadir/CppDersNotlar/Ders27/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ders27.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ders27.dir/main.cpp.o -c /home/abdulkadir/CppDersNotlar/Ders27/main.cpp

CMakeFiles/Ders27.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ders27.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abdulkadir/CppDersNotlar/Ders27/main.cpp > CMakeFiles/Ders27.dir/main.cpp.i

CMakeFiles/Ders27.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ders27.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abdulkadir/CppDersNotlar/Ders27/main.cpp -o CMakeFiles/Ders27.dir/main.cpp.s

# Object files for target Ders27
Ders27_OBJECTS = \
"CMakeFiles/Ders27.dir/main.cpp.o"

# External object files for target Ders27
Ders27_EXTERNAL_OBJECTS =

Ders27: CMakeFiles/Ders27.dir/main.cpp.o
Ders27: CMakeFiles/Ders27.dir/build.make
Ders27: CMakeFiles/Ders27.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abdulkadir/CppDersNotlar/Ders27/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Ders27"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ders27.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ders27.dir/build: Ders27

.PHONY : CMakeFiles/Ders27.dir/build

CMakeFiles/Ders27.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ders27.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ders27.dir/clean

CMakeFiles/Ders27.dir/depend:
	cd /home/abdulkadir/CppDersNotlar/Ders27/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abdulkadir/CppDersNotlar/Ders27 /home/abdulkadir/CppDersNotlar/Ders27 /home/abdulkadir/CppDersNotlar/Ders27/build /home/abdulkadir/CppDersNotlar/Ders27/build /home/abdulkadir/CppDersNotlar/Ders27/build/CMakeFiles/Ders27.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ders27.dir/depend

