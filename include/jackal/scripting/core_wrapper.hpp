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

#ifndef __JACKAL_CORE_WRAPPER_HPP__
#define __JACKAL_CORE_WRAPPER_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/non_copyable.hpp> // The wrapper should not be copied. 
#include <jackal/core/object.hpp>        // Binding Object and eHideFlag.
#include <jackal/core/icomponent.hpp>    // Binding the base component class.

//====================
// Additional includes
//====================
#include <jackal/utils/ext/sol.hpp>      // Exposing classes and enums to lua.

namespace jackal
{
	class CoreWrapper final
	{
	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binds the eHideFlags to the lua scripting interface.
		///
		/// So that these flags can be utilised and used to change the 
		/// behaviour of Object instances within the scripts, they are
		/// exposed to lua.
		///
		////////////////////////////////////////////////////////////
		void bindHideFlags(sol::state& state);
		
		////////////////////////////////////////////////////////////
		/// @brief Binds the Object class to the lua scripting interface.
		///
		/// The Object class is the base class for many objects that can
		/// be manipulated within lua scripts, therefore it's properties
		/// and flag behaviour are exposed to lua.
		///
		/// @returns The Object class represented as a lua object.
		///
		////////////////////////////////////////////////////////////
		void bindObject(sol::state& state);
		
		////////////////////////////////////////////////////////////
		/// @brief Binds the IComponent interface class to the lua scripting interface.
		///
		/// The IComponent class is the base class for many components that
		/// can be manipulated within lua scripts, therefore its properties
		/// are exposed to the lua scripting interface. It cannot be constructed
		/// within a lua script, construction is handled by its child classes.
		///
		/// @returns The IComponent class represented as a lua object.
		///
		////////////////////////////////////////////////////////////
		void bindComponent(sol::state& state);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the CoreWrapper object.
		////////////////////////////////////////////////////////////
		explicit CoreWrapper() = default;
		
		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the CoreWrapper object.
		////////////////////////////////////////////////////////////
		~CoreWrapper() = default;
		
		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binds all of the classes exposed to the lua interface.
		///
		/// When this method is invoked, it will bind all of the classes
		/// that this class has exposed to the scripting interface.
		///
		/// @param state The global sol state object.
		///
		////////////////////////////////////////////////////////////
		void bind(sol::state& state);
	};
	
} // namespace jackal

#endif//__JACKAL_CORE_WRAPPER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::CoreWrapper
/// @ingroup scripting
///
/// The jackal::CoreWrapper is a simple class that is used to
/// wrap all of the classes contained within the jackal_core 
/// and expose them as lua objects for additional behavior within
/// lua. Only specific classes and properties are exposed to the
/// scripting interface.
///
////////////////////////////////////////////////////////////