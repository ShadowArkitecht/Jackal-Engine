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
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/jackal/utils") # Headers and inline files.
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/utils")            # Source files.

#====================
# Variables
#====================
set(HEADER_FILES "${INCLUDE_DIR}/constants.hpp"
                 "${INCLUDE_DIR}/context_settings.hpp"
                 "${INCLUDE_DIR}/csv_file_reader.hpp"
	         "${INCLUDE_DIR}/file_policy.hpp"
                 "${INCLUDE_DIR}/file_reader.hpp"
                 "${INCLUDE_DIR}/file_system.hpp" 
                 "${INCLUDE_DIR}/ipolicy.hpp" 
                 "${INCLUDE_DIR}/log.hpp" 
                 "${INCLUDE_DIR}/log.inl" 
                 "${INCLUDE_DIR}/non_copyable.hpp"
                 "${INCLUDE_DIR}/properties.hpp"
                 "${INCLUDE_DIR}/singleton.hpp")

set(SOURCE_FILES "${SOURCE_DIR}/constants.cpp" 
                 "${SOURCE_DIR}/context_settings.cpp" 
                 "${SOURCE_DIR}/csv_file_reader.cpp"  
                 "${SOURCE_DIR}/file_policy.cpp" 
	         "${SOURCE_DIR}/file_reader.cpp" 
                 "${SOURCE_DIR}/file_system.cpp" 
                 "${SOURCE_DIR}/properties.cpp")

#====================
# Library
#====================
add_library(jackal_utils ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(jackal_utils PROPERTIES LINKER_LANGUAGE CXX)
