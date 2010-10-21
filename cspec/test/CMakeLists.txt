
set( _RUBY_DEBUG_OUTPUT ON)
#	make sure we have libdb
find_package( Ruby REQUIRED )
find_package( CSpec REQUIRED )

message( STATUS "Using Ruby Lib: ${RUBY_LIBRARY}" )
message( STATUS "Using Ruby Headers: ${RUBY_INCLUDE_DIRS}" )
message( STATUS "Using CSpec Lib: ${CSPEC_LIBRARY}" )
message( STATUS "Using CSpec Headers: ${CSPEC_INCLUDE_DIR}" )

get_directory_property( cmake_current_include_dir INCLUDE_DIRECTORIES )

LINK_DIRECTORIES( "/usr/local/lib" )
include_directories( ${RUBY_INCLUDE_DIRS} ${CSPEC_INCLUDE_DIR} )

#	define shared library with sources
file( GLOB SPEC_SOURCE "*_spec.c" )
file( GLOB RARGS_SOURCE "../../ext/rargs/*.c" )

set( RARGS_SPEC_SOURCE ${SPEC_SOURCE} ${RARGS_SOURCE})

add_executable( rargs_test ${RARGS_SPEC_SOURCE} )
target_link_libraries( rargs_test ${RUBY_LIBRARY} )
target_link_libraries( rargs_test ${CSPEC_LIBRARY} )

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
set_target_properties( rargs_test	PROPERTIES	LINKER_LANGUAGE C 
																						OUTPUT_NAME "../rargs_test"
																						PREFIX ""
																						SUFFIX ".cspec"
																						LINK_FLAGS "-Wl,-rpath,-L${CMAKE_INSTALL_RPATH}"
																						INSTALL_RPATH ${CMAKE_INSTALL_RPATH}
																						INSTALL_NAME_DIR ${CMAKE_INSTALL_NAME_DIR}
																						C_FLAGS "-ggdb -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror" )

# Installation of the library
#install( TARGETS rargs_test DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
