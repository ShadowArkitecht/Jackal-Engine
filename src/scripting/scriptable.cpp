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
#include <jackal/scripting/scriptable.hpp>         // Scriptable class declaration.
#include <jackal/utils/log.hpp>                    // Logging warnings and errors.
#include <jackal/utils/constants.hpp>              // file extension constant.
#include <jackal/utils/resource_manager.hpp>       // Retrieving a script resource.

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
	Scriptable::Scriptable()
		: IComponent("Scriptable"), m_self(), m_functions(), m_created(false)
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	bool Scriptable::isCreated() const
	{
		return m_created;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool Scriptable::init(const ResourceHandle<Script>& resource)
	{
		// Initialisation failed or a nullptr was passed in.
		if (!IComponent::init() || !resource.get())
		{
			log.warning(log.function(__FUNCTION__), "failed. Script resource argument is null.");
			return false;
		}

		// Set the new lua object.
		m_self = resource->createTable();
		m_functions = resource->getFunctions();

		this->setName(resource->getTableName());
		return true;
	}

	////////////////////////////////////////////////////////////
	bool Scriptable::init(const std::string& script)
	{
		return this->init(ResourceManager::getInstance().get<Script>(script));
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	Scriptable* Scriptable::create(const ResourceHandle<Script>& resource)
	{
		// TODO(Ben): Retrieve from a object pool.
		Scriptable* pScriptable = new Scriptable();

		if (pScriptable->init(resource))
		{
			return pScriptable;
		}
		
		// TODO(Ben): Reset the object and release back to the pool.
		return nullptr;
	}

	////////////////////////////////////////////////////////////
	Scriptable* Scriptable::create(const std::string& script)
	{
		// TODO(Ben): Retrieve from a object pool.
		Scriptable* pScriptable = new Scriptable();

		if (pScriptable->init(script))
		{
			return pScriptable;
		}

		// TODO(Ben): Reset the object and release back to the pool.
		return nullptr;
	}

	////////////////////////////////////////////////////////////
	void Scriptable::onCreate()
	{
		if (m_functions.test(eScriptMethods::ON_CREATE))
		{
			m_self[Constants::ScriptFunctions::ON_CREATE]();
		}

		m_created = true;
	}

	////////////////////////////////////////////////////////////
	void Scriptable::update(float dt)
	{
		if (m_functions.test(eScriptMethods::UPDATE))
		{
			m_self[Constants::ScriptFunctions::UPDATE](dt);
		}
	}

	////////////////////////////////////////////////////////////
	sol::table Scriptable::lua_asObject() const
	{
		return m_self;
	}

} // namespace jackal