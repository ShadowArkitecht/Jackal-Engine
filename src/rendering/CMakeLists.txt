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
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/jackal/rendering") # Headers and inline files.
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/rendering")            # Source files.

#====================
# Variables
#====================
set(HEADER_FILES "${INCLUDE_DIR}/buffer.hpp"
                 "${INCLUDE_DIR}/directional_light.hpp"
	             "${INCLUDE_DIR}/glsl_object.hpp"
	             "${INCLUDE_DIR}/gui_texture.hpp"
	             "${INCLUDE_DIR}/gui_texture_factory.hpp"
				 "${INCLUDE_DIR}/ilight.hpp"
	             "${INCLUDE_DIR}/irenderable.hpp"
	             "${INCLUDE_DIR}/material.hpp"	
	             "${INCLUDE_DIR}/mesh.hpp"	
	             "${INCLUDE_DIR}/model.hpp"	             
	             "${INCLUDE_DIR}/program.hpp"
	             "${INCLUDE_DIR}/shader.hpp"
	             "${INCLUDE_DIR}/texture.hpp"
	             "${INCLUDE_DIR}/uniform.hpp"
                 "${INCLUDE_DIR}/vertex.hpp")

set(SOURCE_FILES "${SOURCE_DIR}/buffer.cpp"
	             "${SOURCE_DIR}/directional_light.cpp"
	             "${SOURCE_DIR}/glsl_object.cpp"
	             "${SOURCE_DIR}/gui_texture.cpp"
	             "${SOURCE_DIR}/gui_texture_factory.cpp"
				 "${SOURCE_DIR}/ilight.cpp"
	             "${SOURCE_DIR}/irenderable.cpp"
	             "${SOURCE_DIR}/material.cpp"
	             "${SOURCE_DIR}/mesh.cpp"
	             "${SOURCE_DIR}/model.cpp"
	             "${SOURCE_DIR}/program.cpp"
	             "${SOURCE_DIR}/shader.cpp"
	             "${SOURCE_DIR}/texture.cpp"
	             "${SOURCE_DIR}/uniform.cpp")

#====================
# Library
#====================
add_library(jackal_rendering ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(jackal_rendering PROPERTIES LINKER_LANGUAGE CXX)
