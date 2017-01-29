///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Jackal Engine
// 2017 - Benjamin Carter (bencarterdev@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgement
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __JACKAL_CONSTANTS_HPP__
#define __JACKAL_CONSTANTS_HPP__

//====================
// C++ includes
//====================
#include <string>  // Storing the names of extensions and component names.

namespace jackal 
{
	class Constants final
	{
	public:
		//====================
		// Member variables
		//====================
		struct Extensions
		{
			//====================
			// Member variables
			//====================
			// Common extensions.
			static const std::string PROPERTIES;      ///< String literal extension of properties files.
			static const std::string CONFIGURATION;   ///< String literal extension of configuration files.
			static const std::string CSV;             ///< String literal extension of comma seperated values files.
			// Graphics-specific.
			static const std::string VERTEX_SHADER;   ///< String literal extension of vertex shader files.
			static const std::string FRAGMENT_SHADER; ///< String literal extension of fragment shader files.
		};
	};

} // namespace jackal

#endif//__JACKAL_CONSTANTS_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Constants
/// @ingroup utils
///
/// The jackal::Constants class is a wrapper class around several
/// nested classes that is used to represent commonly used values
/// that will not change throughout the course of the application 
/// (such as extensions). It is used just to contain these common
/// values within a single file.
///
/// Due to the simplicity of the class, an example is not provided.
/// Specific variables of the classes will be exposed for use by
/// the lua scripting interface. 
///
////////////////////////////////////////////////////////////