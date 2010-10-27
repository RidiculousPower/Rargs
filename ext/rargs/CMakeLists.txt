
set( _RUBY_DEBUG_OUTPUT ON)
#	make sure we have libdb
find_package( Ruby REQUIRED )

message( STATUS "Using Ruby Lib: ${RUBY_LIBRARY}" )
message( STATUS "Using Ruby Headers: ${RUBY_INCLUDE_DIRS}" )

get_directory_property( cmake_current_include_dir INCLUDE_DIRECTORIES )

LINK_DIRECTORIES( "/usr/local/lib" )
include_directories( ${RUBY_INCLUDE_DIRS} ${CSPEC_INCLUDE_DIR} )

#	define shared library with sources
file( GLOB RARGS_SOURCE "*.c" )
file( GLOB RARGS_HEADERS "include/rargs/*.h" )

add_library( rargs ${RARGS_SOURCE} )
target_link_libraries( rargs ${RUBY_LIBRARY} )

# use, i.e. don't skip the full RPATH for the build tree
set( CMAKE_SKIP_BUILD_RPATH  OFF )

# when building, don't use the install RPATH already
# (but later on when installing)
set( CMAKE_BUILD_WITH_INSTALL_RPATH ON )

set( CMAKE_INSTALL_NAME_DIR "@rpath" )

# the RPATH to be used when installing
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# Set the build version (VERSION) and the API version (SOVERSION)
set_target_properties( rargs	PROPERTIES	LINKER_LANGUAGE C 
																					OUTPUT_NAME "../rargs"
																					PREFIX ""
																					SUFFIX ".dylib"
																					LINK_FLAGS "-Wl,-rpath,-L${CMAKE_INSTALL_RPATH}"
																					INSTALL_RPATH ${CMAKE_INSTALL_RPATH}
																					INSTALL_NAME_DIR ${CMAKE_INSTALL_NAME_DIR}
																					C_FLAGS "-ggdb -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror" )

# Installation of the library
install( TARGETS rargs DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
INSTALL( FILES ${RARGS_HEADERS} DESTINATION "include/rargs" )
INSTALL( FILES "${cmake_current_include_dir}/../rargs.h" DESTINATION "include" )
