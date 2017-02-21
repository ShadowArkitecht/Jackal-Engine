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
# Directories
#====================
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/jackal/math") # Headers and inline files.
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/math")            # Source files.

#====================
# Variables
#====================
set(HEADER_FILES "${INCLUDE_DIR}/colour.hpp"
		 "${INCLUDE_DIR}/matrix4.hpp"
		 "${INCLUDE_DIR}/transform.hpp"
	         "${INCLUDE_DIR}/vector2.hpp"
	         "${INCLUDE_DIR}/vector2.inl"
	         "${INCLUDE_DIR}/vector3.hpp"
	         "${INCLUDE_DIR}/vector3.inl"	             
	         "${INCLUDE_DIR}/vector4.hpp"
	          "${INCLUDE_DIR}/vector4.inl")

set(SOURCE_FILES "${SOURCE_DIR}/colour.cpp"
                 "${SOURCE_DIR}/matrix4.cpp"
                 "${SOURCE_DIR}/transform.cpp"
                 "${SOURCE_DIR}/vector2.cpp")

#====================
# Library
#====================
add_library(jackal_math ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(jackal_math PROPERTIES LINKER_LANGUAGE CXX)
