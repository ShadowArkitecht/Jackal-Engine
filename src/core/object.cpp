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
#include <jackal/core/object.hpp> // Object class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Object::Object()
		: m_name(), m_active(true), m_flags(eHideFlags::NONE)
	{
	}
	
	////////////////////////////////////////////////////////////
	Object::Object(const std::string& name)
		: m_name(name), m_active(true), m_flags(eHideFlags::NONE)
	{
	}
	
	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	std::string Object::getName() const
	{
		return m_name;
	}
	
	////////////////////////////////////////////////////////////
	void Object::setName(const std::string& name)
	{
		m_name = name;
	}
	
	////////////////////////////////////////////////////////////
	bool Object::isActive() const
	{
		return m_active;
	}
	
	////////////////////////////////////////////////////////////
	void Object::setActive(bool active)
	{
		m_active = active;	
	}

	////////////////////////////////////////////////////////////
	bool Object::flagSet(eHideFlags flag) const
	{
		return m_flags.test(flag);
	}
	
	////////////////////////////////////////////////////////////
	void Object::setFlag(eHideFlags flag, bool state)
	{
		m_flags.set(flag, state);
	}
	
} // namespace jackal