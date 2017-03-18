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
#include <jackal/scripting/core_wrapper.hpp> // CoreWrapper class declaration.

namespace jackal
{
	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	void CoreWrapper::bindHideFlags(sol::state& state)
	{
		state.new_enum("HideFlags",
			"NONE", eHideFlags::NONE,
			"DONT_SAVE", eHideFlags::DONT_SAVE,
			"DONT_UNLOAD", eHideFlags::DONT_UNLOAD
		);
	}
	
	////////////////////////////////////////////////////////////
	void CoreWrapper::bindObject(sol::state& state) 
	{
		state.new_usertype<Object>("Object",
			// Properties
			"name", sol::property(&Object::getName, &Object::setName),
			"active", sol::property(&Object::isActive, &Object::setActive),
			// Methods
			"flag_set", &Object::flagSet,
			"set_flag", &Object::setActive
		);
	}

	////////////////////////////////////////////////////////////
	void CoreWrapper::bindComponent(sol::state& state)
	{
		state.new_usertype<IComponent>("Component");
	}
	
	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void CoreWrapper::bind(sol::state& state)
	{
		this->bindHideFlags(state);
		this->bindObject(state);
		this->bindComponent(state);
	}	

} // namespace jackal