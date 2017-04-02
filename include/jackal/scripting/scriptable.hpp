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

#ifndef __JACKAL_SCRIPTABLE_HPP__
#define __JACKAL_SCRIPTABLE_HPP__

//====================
// C++ includes
//====================
#include <bitset>                           // Storing which methods are active within the script.

//====================
// Jackal includes
//====================
#include <jackal/core/icomponent.hpp>       // Scriptable is a type of component that can be added to game objects.
#include <jackal/utils/resource_handle.hpp> // A handle to the Script object.
#include <jackal/scripting/script.hpp>      // Maintaining a reference to the script.

namespace jackal 
{
	class Scriptable final : public IComponent
	{
	private:
		//====================
		// Member variables
		//====================
		sol::table                                 m_self;      ///< A reference to the table contained within the lua script.
		std::bitset<eScriptMethods::MAX_FUNCTIONS> m_functions; ///< Which methods are active within the script.
		bool                                       m_created;   ///< Whether the object's create method has been invoked.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Initialises the Scriptable component, ready for use.
		///
		/// This method is invoked by the subsequent Scriptable::create method,
		/// when the object is being initialised, it will use the desired script
		/// resource and create a new table instance and populate the desired 
		/// functions for use. The initialisation will fail if the resource passed
		/// in is equal to null.
		///
		/// @param resource The resource retrieved from the ResourceManager.
		///
		/// @returns True if the object initialised successfully.
		///
		////////////////////////////////////////////////////////////
		bool init(const ResourceHandle<Script>& resource);

		////////////////////////////////////////////////////////////
		/// @brief Initialises the Scriptable component, with the path of a lua script.
		///
		/// This method is invoked by the subsequent Scriptable::create method,
		/// when the object is being initialised, it will use the desired script
		/// resource and create a new table instance and populate the desired 
		/// functions for use. The initialisation will fail if the resource passed
		/// in is equal to null.
		///
		/// @param script The file path of the lua script.
		///
		/// @returns True if the object initialised successfully.
		///
		////////////////////////////////////////////////////////////
		bool init(const std::string& script);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Scriptable component.
		///
		/// The default constructor will initialise all of the member
		/// variables to default values. If the class is created with the
		/// constructor rather than invoking the Scriptable::create method,
		/// it is not in a useable state for the application.
		///
		////////////////////////////////////////////////////////////
		explicit Scriptable();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Scriptable object.
		////////////////////////////////////////////////////////////
		~Scriptable() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the creation state of the current lua script.
		///
		/// Each lua script typically contains a "on_create" method, this method
		/// is invoked when the script is first processed by the jackal::ScriptSystem.
		/// Create will only be invoked once, on the first frame after the script has
		/// been added as a component.
		///
		/// @returns The created state of the lua table.
		///
		////////////////////////////////////////////////////////////
		bool isCreated() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates a new Scriptable component from a resource.
		///
		/// This method is a convenience method for wrapping the behavior
		/// around how the jackal engine will handle memory management
		/// with dynamic resources. This method will invoke the desired
		/// object pools and initialise the Scriptable component. If creation
		/// fails, the object is released back to the pool and a null value is
		/// returned.
		///
		/// @param resource A handle to the script resource retrieved from the ResourceManager.
		///
		/// @returns A new Scriptable object.
		///
		////////////////////////////////////////////////////////////
		static Scriptable* create(const ResourceHandle<Script>& resource);

		////////////////////////////////////////////////////////////
		/// @brief Creates a new Scriptable component from a lua script file.
		///
		/// This method is a convenience method for wrapping the behavior
		/// around how the jackal engine will handle memory management
		/// with dynamic resources. This method will invoke the desired
		/// object pools and initialise the Scriptable component. If creation
		/// fails, the object is released back to the pool and a null value is
		/// returned.
		///
		/// @param script The file path of the designated lua script.
		///
		/// @returns A new Scriptable object.
		///
		////////////////////////////////////////////////////////////
		static Scriptable* create(const std::string& script);

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
		void onCreate();

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

#endif//__JACKAL_SCRIPTABLE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Scriptable
/// @ingroup scripting
///
/// The jackal::Scriptable is a component class that can be attached
/// to GameObject's within a scene to run behavior contained within
/// a lua script. The Scriptable object itself only contains a 
/// reference to a table within the specified lua script, it is only
/// responsible for that table's lifetime, it is not responsible
/// for loading and compiling scripts. That responsibility is contained
/// within the jackal::Script object.
///
/// All of the gameplay behavior should be contained within scripts,
/// so that utilising the engine does not utilise constant re-compilation.
/// In combination with json data files, this allows the engine to be used
/// dynamically with a quick iteration time.
///
/// The Scriptable component is accessible within scripts, it is different
/// to different components, it will not return a reference to the Scriptable
/// component itself. Rather, it will return a reference to the retained lua
/// table, so that functions within other scripts can be accessed between
/// scripts.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Retrieve a handle to the lua script.
/// ResourceHandle<Script> script = Script::create("~assets/scripts/test_script.lua");
/// // Create the component.
/// Scriptable* scriptable = Scriptable::create(script);
///
/// // Create the game object.
/// GameObject* object = GameObject::create();
/// // Add the scriptable component.
/// object->addComponent(scriptable);
/// @endcode
///
/// Lua Code example:
/// @code
/// function another_script:on_create(entity)
/// 	-- Retain the entity this script is attached to.
/// 	self.entity = entity
///
/// 	-- Retrieve the other script attached to this entity.
/// 	local test_script = self.entity:get_component("test_script")
/// 	-- Call a function on the other script.
/// 	-- In order to call a function from another file, it must be a function of that table.
/// end
/// @endcode
///
////////////////////////////////////////////////////////////