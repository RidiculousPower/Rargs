# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = "/Applications/CMake 2.8-2.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-2.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-2.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/asher/Projects/rp/ruby/rargs/cspec

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/asher/Projects/rp/ruby/rargs/cspec/run

# Include any dependencies generated for this target.
include test/CMakeFiles/rargs_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/rargs_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/rargs_test.dir/flags.make

test/CMakeFiles/rargs_test.dir/main_spec.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/main_spec.c.o: ../test/main_spec.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/main_spec.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/main_spec.c.o   -c /Users/asher/Projects/rp/ruby/rargs/cspec/test/main_spec.c

test/CMakeFiles/rargs_test.dir/main_spec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/main_spec.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/cspec/test/main_spec.c > CMakeFiles/rargs_test.dir/main_spec.c.i

test/CMakeFiles/rargs_test.dir/main_spec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/main_spec.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/cspec/test/main_spec.c -o CMakeFiles/rargs_test.dir/main_spec.c.s

test/CMakeFiles/rargs_test.dir/main_spec.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/main_spec.c.o.requires

test/CMakeFiles/rargs_test.dir/main_spec.c.o.provides: test/CMakeFiles/rargs_test.dir/main_spec.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/main_spec.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/main_spec.c.o.provides

test/CMakeFiles/rargs_test.dir/main_spec.c.o.provides.build: test/CMakeFiles/rargs_test.dir/main_spec.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/main_spec.c.o.provides.build

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o: ../test/rb_Rargs_define_spec.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o   -c /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_define_spec.c

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_define_spec.c > CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.i

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_define_spec.c -o CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.s

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.requires

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.provides: test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.provides

test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.provides.build: test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.provides.build

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o: ../test/rb_Rargs_parse_spec.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o   -c /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_parse_spec.c

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_parse_spec.c > CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.i

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/cspec/test/rb_Rargs_parse_spec.c -o CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.s

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.requires

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.provides: test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.provides

test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.provides.build: test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.provides.build

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o: /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o   -c /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c > CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.i

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.s

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.requires

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.provides: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.provides

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.provides.build: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.provides.build

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o: /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o   -c /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c > CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.i

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.s

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.requires

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.provides: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.provides

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.provides.build: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.provides.build

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o: /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o   -c /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c > CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.i

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.s

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.requires

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.provides: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.provides

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.provides.build: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.provides.build

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o: /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o   -c /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c > CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.i

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.s

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.requires

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.provides: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.provides

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.provides.build: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.provides.build

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o: test/CMakeFiles/rargs_test.dir/flags.make
test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o: /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/ruby/rargs/cspec/run/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o   -c /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.i"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c > CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.i

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.s"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c -o CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.s

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.requires:
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.requires

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.provides: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.requires
	$(MAKE) -f test/CMakeFiles/rargs_test.dir/build.make test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.provides.build
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.provides

test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.provides.build: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o
.PHONY : test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.provides.build

# Object files for target rargs_test
rargs_test_OBJECTS = \
"CMakeFiles/rargs_test.dir/main_spec.c.o" \
"CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o" \
"CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o" \
"CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o" \
"CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o" \
"CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o" \
"CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o" \
"CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o"

# External object files for target rargs_test
rargs_test_EXTERNAL_OBJECTS =

test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/main_spec.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o
test/../rargs_test.cspec: /Users/asher/.rvm/rubies/ruby-1.9.2-p0/lib/libruby.dylib
test/../rargs_test.cspec: /usr/local/lib/libcspec.a
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/build.make
test/../rargs_test.cspec: test/CMakeFiles/rargs_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../rargs_test.cspec"
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rargs_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/rargs_test.dir/build: test/../rargs_test.cspec
.PHONY : test/CMakeFiles/rargs_test.dir/build

test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/main_spec.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/rb_Rargs_define_spec.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/rb_Rargs_parse_spec.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_define.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_describe.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_error.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_free.c.o.requires
test/CMakeFiles/rargs_test.dir/requires: test/CMakeFiles/rargs_test.dir/Users/asher/Projects/rp/ruby/rargs/ext/rargs/rb_Rargs_parse.c.o.requires
.PHONY : test/CMakeFiles/rargs_test.dir/requires

test/CMakeFiles/rargs_test.dir/clean:
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run/test && $(CMAKE_COMMAND) -P CMakeFiles/rargs_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/rargs_test.dir/clean

test/CMakeFiles/rargs_test.dir/depend:
	cd /Users/asher/Projects/rp/ruby/rargs/cspec/run && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/asher/Projects/rp/ruby/rargs/cspec /Users/asher/Projects/rp/ruby/rargs/cspec/test /Users/asher/Projects/rp/ruby/rargs/cspec/run /Users/asher/Projects/rp/ruby/rargs/cspec/run/test /Users/asher/Projects/rp/ruby/rargs/cspec/run/test/CMakeFiles/rargs_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/rargs_test.dir/depend

