###################################################################################################
#
# Jackal Engine
# 2017 - Benjamin Carter (bencarterdev@outlook.com)
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented;
#    you must not claim that you wrote the original software.
#    If you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.
#
###################################################################################################

#====================
# Setup
#====================
cmake_minimum_required(VERSION 3.1.0)

project(Jackal-Editor)
set(CMAKE_CXX_STANDARD 14)	# C++14 standard. 

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#====================
# Include directories
#====================
include_directories("${CMAKE_SOURCE_DIR}/include")

#====================
# Libraries
#====================
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
	message(STATUS "SDL2 found. Linking to Jackal Engine.")
	include_directories(${SDL2_INCLUDE_DIR})
	link_libraries(${SDL2_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. SDL2 could not be found.")
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	message(STATUS "OpenGL found. Linking to Jackal Engine.")
	link_libraries(${OPENGL_gl_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. OpenGL could not be found.")
endif()

find_package(JGLEW REQUIRED)
if (JGLEW_FOUND)
	message(STATUS "GLEW found. Linking to Jackal Engine.")
	include_directories(${JGLEW_INCLUDE_DIR})
	link_libraries(${JGLEW_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. GLEW count not be found.")
endif()

#====================
# Source directories
#====================
add_subdirectory("${CMAKE_SOURCE_DIR}/src")

#====================
# Variables
#====================
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/main.cpp)

#====================
# Executable
#====================
add_executable(jackal ${SOURCE_FILES})

set_target_properties(jackal PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(jackal jackal_core jackal_utils)