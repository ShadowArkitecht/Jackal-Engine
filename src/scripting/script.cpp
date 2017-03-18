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
#include <jackal/utils/log.hpp>                    // Logging warnings and errors.
#include <jackal/scripting/scripting_manager.hpp>  // Retrieving the global lua state.
#include <jackal/utils/file_system.hpp>            // Checking the file extension.
#include <jackal/utils/constants.hpp>              // file extension constant.

//====================
// Additional includes
//====================
#include <lua.hpp>                                 // Storing the lua_State.

namespace jackal
{
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt"); // Logging warnings and errors.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Script::Script(const std::string& filename)
		: IComponent(""), m_self(), m_table(), m_methods(), m_created(false)
	{
		std::string ext = Constants::Extensions::LUA;
		sol::state& state = ScriptingManager::getInstance().getState();

		FileSystem system;
		if (!system.hasExtension(filename, ext))
		{
			log.warning(log.function(__FUNCTION__, filename), "failed. Incorrect file extension");
			return;
		}

		sol::load_result script = state.load_file(filename);
		if (!script.valid())
		{
			log.warning(log.function(__FUNCTION__, filename), "compilation error: ", lua_tostring(script.lua_state(), -1));
			return;
		}

		script();

		std::size_t index = filename.find_last_of('/');
		m_table = index == std::string::npos ? filename.substr(0, filename.length() - ext.length() - 1) :
			                                   filename.substr(index, filename.length() - ext.length() - 1);

		m_self = state[m_table.c_str()];
		if (!m_self.valid())
		{
			log.warning(log.function(__FUNCTION__, filename), m_table, "is not a valid table.");
		}

		this->setName(m_table);
		m_methods.set(eScriptMethods::CREATE, this->isMethod("create"));
		m_methods.set(eScriptMethods::UPDATE, this->isMethod("update"));
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	bool Script::isCreated() const
	{
		return m_created;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool Script::isMethod(const std::string& name) const
	{
		return m_self[name.c_str()].valid();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Script::create()
	{
		if (m_methods.test(eScriptMethods::CREATE))
		{
			m_self["create"]();
		}

		m_created = true;
	}

	////////////////////////////////////////////////////////////
	void Script::update(float dt)
	{
		if (m_methods.test(eScriptMethods::UPDATE))
		{
			m_self["update"](dt);
		}
	}

	////////////////////////////////////////////////////////////
	sol::table Script::lua_asObject() const
	{
		return m_self;
	}

} // namespace jackal