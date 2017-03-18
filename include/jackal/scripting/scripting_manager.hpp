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

#ifndef __JACKAL_SCRIPTING_MANAGER_HPP__
#define __JACKAL_SCRIPTING_MANAGER_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/singleton.hpp> // The scripting manager is a type of singleton.
#include <jackal/utils/ext/sol.hpp>   // The sol lua state object.

namespace jackal
{
	class ScriptingManager final : public Singleton<ScriptingManager>
	{
		friend class Singleton<ScriptingManager>;

	private:
		//====================
		// Member variables
		//====================
		sol::state m_state;

	private:
		//====================
		// Private ctor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Private default constructor for the ScriptingManager.
		///
		/// The constructor is kept private to conform with the Singleton
		/// design pattern. The constructor will initialise the global lua
		/// state and bind the specific luabind behaviour.
		///
		////////////////////////////////////////////////////////////
		explicit ScriptingManager();

	public:
		//====================
		// Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Destructor for the ScriptingManager singleton.
		///
		/// The destructor will close the global lua state and de-allocate
		/// the resources.
		///
		////////////////////////////////////////////////////////////
		~ScriptingManager() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the global lua state.
		///
		/// The global lua state is used throughout the application to
		/// manipulate any behaviour associated with lua scripting
		/// or the lua stack. It is used to retrieve variables and call specific
		/// functions within a lua class.
		///
		/// @returns The global lua state.
		///
		////////////////////////////////////////////////////////////
		sol::state& getState();

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binds all of the relevant C++ classes to lua.
		///
		/// This method is a simple abstraction around the different
		/// wrapper classes that are utilised to expose the relevant
		/// classes and variables within each jackal library.
		///
		////////////////////////////////////////////////////////////
		void bind();
	};

} // namespace jackal

#endif//__JACKAL_SCRIPTING_MANAGER_HPP__