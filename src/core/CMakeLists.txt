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
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/jackal/core") # Headers and inline files.
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/core")            # Source files.

#====================
# Variables
#====================
set(HEADER_FILES "${INCLUDE_DIR}/camera.hpp"
                 "${INCLUDE_DIR}/component_type.hpp"
                 "${INCLUDE_DIR}/component_type_controller.hpp"
                 "${INCLUDE_DIR}/config_file.hpp"
                 "${INCLUDE_DIR}/entity_component_system.hpp"
                 "${INCLUDE_DIR}/game_object.hpp"
                 "${INCLUDE_DIR}/icomponent.hpp"
                 "${INCLUDE_DIR}/isystem.hpp"
                 "${INCLUDE_DIR}/object.hpp"
                 "${INCLUDE_DIR}/virtual_file_system.hpp"
                 "${INCLUDE_DIR}/window.hpp")

set(SOURCE_FILES "${SOURCE_DIR}/camera.cpp"
                 "${SOURCE_DIR}/component_type.cpp"
                 "${SOURCE_DIR}/component_type_controller.cpp"
                 "${SOURCE_DIR}/config_file.cpp"
                 "${SOURCE_DIR}/entity_component_system.cpp"
                 "${SOURCE_DIR}/game_object.cpp" 
                 "${SOURCE_DIR}/icomponent.cpp" 
                 "${SOURCE_DIR}/isystem.cpp" 
                 "${SOURCE_DIR}/object.cpp" 
                 "${SOURCE_DIR}/virtual_file_system.cpp"
                 "${SOURCE_DIR}/window.cpp")

#====================
# Library
#====================
add_library(jackal_core ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(jackal_core PROPERTIES LINKER_LANGUAGE CXX)
