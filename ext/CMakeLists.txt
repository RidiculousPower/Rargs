cmake_minimum_required(VERSION 2.6)

project( rargs C )

#  add local modules path for project
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

#  where to look for source files (headers and source)
include_directories( rargs/include )

#  define sub-directories of source that cmake knows about as well a where their output will be put
add_subdirectory( rargs )

#  compiler-dependent flags:
if( CMAKE_COMPILER_IS_GNUCC )
  #  gcc
  add_definitions(-ggdb -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
else( CMAKE_COMPILER_IS_GNUCC )
  #  non-gcc (intended for clang)
  add_definitions(-ggdb -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
endif( CMAKE_COMPILER_IS_GNUCC )

message( STATUS "Compiling with flags: ${CMAKE_C_FLAGS}" )

#  distribution configuration
set(CMAKE_C_FLAGS_DISTRIBUTION "-O3")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")

set( CMAKE_VERBOSE_MAKEFILE ON )
