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

project(Jackal-Engine)
set(CMAKE_CXX_STANDARD 17)	# C++17 standard. 

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

find_package(SDL2_IMAGE REQUIRED)
if (SDL2_IMAGE_FOUND)
	message(STATUS "SDL2_image found. Linking to Jackal Engine.")
	link_libraries(${SDL2_IMAGE_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. SDL2_image could not be found.")
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

find_package(AWESOMIUM REQUIRED)
if (AWESOMIUM_FOUND)
	message(STATUS "Awesomium found. Linking to Jackal Engine.")
	include_directories(${AWESOMIUM_INCLUDE_DIR})
	link_libraries(${AWESOMIUM_LIBRARY})
else()
	message(FATAL_ERROR "CMake build failed. Awesomium could not be found.")
endif()

find_package(ASSIMP REQUIRED)
if (ASSIMP_FOUND)
	message(STATUS "Assimp found. Linking to Jackal Engine.")
	include_directories(${ASSIMP_INCLUDE_DIR})
	link_libraries(${ASSIMP_LIBRARY})
else()
	messages(FATAL_ERROR "CMake build failed. Assimp could not be found.")
endif()

if (NOT LUA_FOUND AND NOT LUA51_FOUND)
	find_package(Lua51 REQUIRED)
	include_directories("${LUA_INCLUDE_DIR}")
	link_libraries(${LUA_LIBRARIES})
	message(STATUS "Lua found. Linking to Jackal Engine.")
else()
	message(FATAL_ERROR "CMake build failed. Lua could not be found.")
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
target_link_libraries(jackal jackal_core jackal_utils jackal_rendering jackal_math jackal_scripting)