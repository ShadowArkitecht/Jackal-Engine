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

//====================
// Jackal includes
//====================
#include <jackal/scripting/script.hpp>             // Script class declaration.
#include <jackal/utils/log.hpp>                    // Logging warning and errors.
#include <jackal/utils/constants.hpp>              // Constants for lua function names.
#include <jackal/utils/file_system.hpp>            // Checking existence of lua script.
#include <jackal/scripting/scripting_manager.hpp>  // A reference to the manager for lua scripts.
#include <jackal/utils/resource_manager.hpp>       // Retrieve a handle to a Script resource from the manager.

//====================
// Additional includes
//====================
#include <lua.hpp>                                 // Retrieving errors for lua scripts.

namespace jackal
{	
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt");

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Script::Script()
		: Resource(), m_state(ScriptingManager::getInstance().getState()), m_tableName(), m_functions()
	{
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool Script::isFunction(const sol::table& table, const std::string& name) const
	{
		return table[name.c_str()].valid();
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	std::string Script::getTableName() const
	{
		return m_tableName;
	}

	////////////////////////////////////////////////////////////
	std::bitset<eScriptMethods::MAX_FUNCTIONS> Script::getFunctions() const
	{
		return m_functions;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Script::load(const std::string& filename)
	{
		std::string ext = Constants::Extensions::LUA;

		FileSystem system;
		if (!system.hasExtension(filename, ext))
		{
			log.warning(log.function(__FUNCTION__, filename), "failed. Incorrect file extension");
			return false;
		}

		sol::load_result script = m_state.load_file(filename);
		if (!script.valid())
		{
			log.warning(log.function(__FUNCTION__, filename), "compilation error: ", lua_tostring(script.lua_state(), -1));
			return false;
		}

		script();

		std::size_t index = filename.find_last_of('/');
		m_tableName = index == std::string::npos ? filename.substr(0, filename.length() - ext.length() - 1) :
			                                   	   filename.substr(index, filename.length() - ext.length() - 1);

		sol::table t = m_state[m_tableName.c_str()];
		if (!t.valid())
		{
			log.warning(log.function(__FUNCTION__, filename), m_tableName, "is not a valid table.");
			return false;
		}

		// Set relevant functions.
		m_functions.set(eScriptMethods::ON_CREATE, this->isFunction(t, Constants::ScriptFunctions::ON_CREATE));
		m_functions.set(eScriptMethods::UPDATE, this->isFunction(t, Constants::ScriptFunctions::UPDATE));
		m_functions.set(eScriptMethods::ON_DESTROY, this->isFunction(t, Constants::ScriptFunctions::ON_DESTROY));

		log.debug(log.function(__FUNCTION__, filename), "parsed successfully.");
		return true;
	}

	////////////////////////////////////////////////////////////
	ResourceHandle<Script> Script::find(const std::string& name)
	{
		return ResourceManager::getInstance().get<Script>(name);
	}

	////////////////////////////////////////////////////////////
	sol::table Script::createTable() const
	{
		return m_state[m_tableName.c_str()];
	}

} // namespace jackal