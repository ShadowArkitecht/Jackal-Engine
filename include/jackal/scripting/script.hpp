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
#include <bitset>                     // Storing which methods are active within the script.

//====================
// Jackal includes
//====================
#include <jackal/core/icomponent.hpp> // Script is a type of component that can be added to game objects.

namespace jackal 
{
	enum eScriptMethods
	{
		CREATE,      // The create method within the lua script.
		UPDATE,      // The update method within the lua script.
		MAX_METHODS  // The max amount of methods within the script.
	};

	class Script final : public IComponent
	{
	private:
		//====================
		// Member variables
		//====================
		sol::table                               m_self;    ///< A reference to the class contained within the lua script.
		std::string                              m_table;   ///< The name of the table within the lua script.
		std::bitset<eScriptMethods::MAX_METHODS> m_methods; ///< Which methods are active within the script.
		bool                                     m_created; ///< Whether the object's create method has been invoked.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Checks whether the specified method is contained within the script.
		///
		/// When this method is invoked, it will search the class within the lua
		/// script to see if the specified method has been declared. If the method
		/// has been declared, it will return a true result.
		///
		/// @returns True if the method exists within the lua script.
		///
		////////////////////////////////////////////////////////////
		bool isMethod(const std::string& name) const;

	public:
		//====================
		// Ctor and dtor
		//====================
		explicit Script(const std::string& filename);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Script object.
		////////////////////////////////////////////////////////////
		~Script() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the creation state of the current lua script.
		///
		/// Each lua script typically contains a "create" method, this method
		/// is invoked when the script is first processed by the jackal::ScriptSystem.
		/// Create will only be invoked once, on the first frame after the script has
		/// been added as a component.
		///
		/// @returns The created state of the lua object.
		///
		////////////////////////////////////////////////////////////
		bool isCreated() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Invokes the create method within the lua script.
		///
		/// The create method is typically used to store variables
		/// that will persist throughout the lifetime of the object.
		/// The create method is invoked on the frame after the script
		/// component has been attached to a game object and is only
		/// called once. The "create" method is an optional method within
		/// the script.
		///
		////////////////////////////////////////////////////////////
		void create();

		////////////////////////////////////////////////////////////
		/// @brief Invokes the update method within the lua script.
		///
		/// The update method is invoked every frame of the application.
		/// It will call the subsequent "update" method within the lua 
		/// script and pass in the current delta-time. The method usually
		/// includes behaviour that the script should execute each tick.
		///
		/// Similar to the "create" method, it is an optional method within
		/// the script.
		///
		/// @param dt The current delta-time of the application.
		///
		////////////////////////////////////////////////////////////
		void update(float dt);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves a reference to the script as a lua object.
		///
		/// This method operates slightly differently to other components. 
		/// Other components will typically return an instance of the component
		/// itself, however with the script object, it will return the lua
		/// object of the class within the lua script, so that it can be 
		/// accessed and manipulated by other lua scripts and objects.
		///
		/// @returns The lua class object.
		///
		////////////////////////////////////////////////////////////
		sol::table lua_asObject() const override;
	};

} // namespace jackal

#endif//__JACKAL_SCRIPT_HPP__