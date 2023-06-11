# K k
cmake_minimum_required (VERSION 3.26.4)
project (mltcrd VERSION 1.0.0)

###############################################################################
# System-wide includes
###############################################################################

include (GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE)
	set (
		CMAKE_BUILD_TYPE "Release"
		CACHE STRING "Build type (Debug / Release)"
		FORCE
	)
endif ()

###############################################################################
# Variables
###############################################################################

set (CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS} -Wall -Wextra")
set (CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS} -D_GNU_SOURCE")
set (CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS_DEBUG} -Og -DDEBUG")
set (CMAKE_C_FLAGS_RELEASE           "${CMAKE_C_FLAGS_RELEASE} -Werror")
set (CMAKE_VERBOSE_MAKEFILE          ON)
set (MLTCRD_SRC_DIRECTORY            ${PROJECT_SOURCE_DIR}/src)
set (MLTCRD_INCLUDE_DIRECTORY        ${PROJECT_SOURCE_DIR}/include)
set (MLTCRD_SHARED_INSTALL_DIRECTORY ${CMAKE_INSTALL_FULL_LIBDIR})
set (MLTCRD_HEADER_INSTALL_DIRECTORY ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME})

###############################################################################
# Traverse subdirectories
###############################################################################

add_subdirectory (${MLTCRD_SRC_DIRECTORY})
add_subdirectory (${MLTCRD_INCLUDE_DIRECTORY})

###############################################################################
# Generate and install pkg-config file
###############################################################################

# TODO
