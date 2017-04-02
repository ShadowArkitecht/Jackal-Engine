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
#include <bitset>  // Defining alias for ECS bitsets.

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
			static const std::string JSON;            ///< String literal extension of json files.
			static const std::string LUA;             ///< String literal extension of lua files.
			// Graphics-specific.
			static const std::string VERTEX_SHADER;   ///< String literal extension of vertex shader files.
			static const std::string FRAGMENT_SHADER; ///< String literal extension of fragment shader files.
		};

		struct Components
		{
			//====================
			// Member variables
			//====================
			static const std::string MESH_RENDERER;   ///< String literal for the name of the mesh renderer component.
			static constexpr int MAX_COMPONENTS = 32; ///< The maximum amount of components.
		};

		struct ScriptFunctions
		{
			//====================
			// Member variables
			//====================
			static const char* ON_CREATE;            ///< String literal for the on_create function in lua script.
			static const char* UPDATE;               ///< String literal for the update function in lua script.
			static const char* ON_DESTROY;           ///< String literal for the on_destroy function in lua script.
		};
	};

	//====================
	// Type definitions
	//====================
	typedef std::bitset<Constants::Components::MAX_COMPONENTS> TypeSet;

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

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Constants::Extensions
/// @ingroup utils
///
/// jackal::Constants::Extensions is a basic nested struct that
/// contains a number of static string member variables that is used
/// to represent the various different file extensions for external file
/// that will be loaded in for the application to function.
///
/// As the class is just a collection of member variables, no example
/// is provided and specific variables are exposed to the lua scripting
/// interface.
///
////////////////////////////////////////////////////////////