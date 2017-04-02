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

#ifndef __JACKAL_SCRIPT_HPP__
#define __JACKAL_SCRIPT_HPP__

//====================
// C++ includes
//====================
#include <bitset>                           // Containing which functions are active within a script.

//====================
// Jackal includes
//====================
#include <jackal/utils/resource.hpp>        // Script is a type of resource.
#include <jackal/utils/ext/sol.hpp>         // Storing the state and references to the lua table.
#include <jackal/utils/resource_handle.hpp> // A handle to the Script resource.

namespace jackal
{
	//====================
	// Enumerations
	//====================
	enum eScriptMethods
	{
		ON_CREATE,    // The create method within the lua script.
		UPDATE,       // The update method within the lua script.
		ON_DESTROY,   // The destroy method within the lua script.
		MAX_FUNCTIONS // The max amount of methods within the script.
	};

	class Script final : public Resource
	{
	private:
		//====================
		// Member variables
		//====================
		sol::state&                                m_state;      ///< A reference to the global lua state.
		std::string                                m_tableName;  ///< The name of the table within the lua script.
		std::bitset<eScriptMethods::MAX_FUNCTIONS> m_functions;  ///< Which functions are active within the script.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Checks whether the specified function is contained within the script.
		///
		/// When this method is invoked, it will search the table within the lua
		/// script to see if the specified function has been declared. If the function
		/// has been declared, it will return a true result.
		///
		/// @param table The table to check for the existence of the function.
		/// @param name  The name of the function to check for.
		///
		/// @returns True if the function exists within the lua script.
		///
		////////////////////////////////////////////////////////////
		bool isFunction(const sol::table& table, const std::string& name) const;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Script object.
		///
		/// When this constructor is invoked, it will set all of the member
		/// variables to default values. If the script is not added to the
		/// ResourceManager, it is not useable in this state until Script::load
		/// is invoked.
		///
		////////////////////////////////////////////////////////////
		explicit Script();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Script object.
		////////////////////////////////////////////////////////////
		~Script() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the name of the table.
		///
		/// The name of the table refers to the name of both the lua
		/// script file and the name of the table within the script itself.
		/// This function is used to retrieve the table from the script
		/// itself.
		///
		/// @returns The name of the script file/table.
		///
		////////////////////////////////////////////////////////////
		std::string getTableName() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves which funnctions are active within the script.
		///
		/// Each special named function within the lua scripts are assigned
		/// a specific flag, if the function has been declared within the script
		/// the corresponding flag is set to true. Refer to the lua documentation
		/// to see a full list of named functions.
		///
		/// @returns A list of flags with the corresponding active functions.
		///
		////////////////////////////////////////////////////////////
		std::bitset<eScriptMethods::MAX_FUNCTIONS> getFunctions() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Overrides the load method and loads the external script.
		///
		/// This method is invoked when a script is first retrieved from
		/// the ResourceManager. When the script is loaded, it will parse
		/// the external file and only successfully parse if no syntax errors
		/// were found. If the load is successful, it is retained by the ResourceManager
		/// and returned as handles.
		///
		/// @param filename The file location of the script. (Can be a virtual path).
		///
		/// @returns True if the script was loaded and parsed successfully.
		///
		////////////////////////////////////////////////////////////
		bool load(const std::string& filename) override;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves a Script from the list of resources.
		///
		/// This method is a simple short-hand method for retrieving a 
		/// handle to the Script resource from the ResourceManager class.
		/// If the resource was not found, a default resource is returned
		/// and a warning is logged.
		///
		/// @param name The name of the Script object to retrieve.
		///
		/// @returns A handle to the Script resoure.
		///
		////////////////////////////////////////////////////////////
		static ResourceHandle<Script> find(const std::string& name);

		////////////////////////////////////////////////////////////
		/// @brief Creates a table instance to the lua table within the script.
		///
		/// When the Script resource is utilised by the Scriptable
		/// components, it creates an instance of the lua table which is 
		/// retained and utilised by the Scriptable component when manipulating
		/// behaviour.
		///
		/// @returns A instance to the table within the lua script.
		///
		////////////////////////////////////////////////////////////
		sol::table createTable() const;
	};

} // namespace jackal

#endif//__JACKAL_SCRIPT_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Script
/// @grouping scripting
///
/// The jackal::Script class is a Resource class that is used
/// to retain the behaviour defined within an external lua script.
/// Each script within the application must contain a table, which
/// is used to communicate information between lua scripts and C++
/// objects. One of the caveats of the implementation, is that the
/// table within the script must match the name of the script. For example:
///
/// @code
/// test_script = {
/// 	entity = nil	
/// }
/// @endcode 
///
/// Therefore the filename must be ../test_script.lua. The Script
/// objects are retained and their lifetime managed by the ResourceManager, to
/// prevent duplicate objects and constant re-compilation of scripts.
/// Script loading is typically handled internally so no examples
/// are provided.
///
////////////////////////////////////////////////////////////