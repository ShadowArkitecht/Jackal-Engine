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
#include <jackal/core/icomponent.hpp>  // IComponent class declaration.
#include <jackal/core/game_object.hpp> // Comparing the tags of a GameObject and retrieving transform.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	IComponent::IComponent(const std::string& name)
		: Object(name), m_pParent(nullptr)
	{
	}

	//====================
	// Protected methods
	//====================
	////////////////////////////////////////////////////////////
	bool IComponent::init()
	{
		// Defines no behavior.
		return true;
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GameObject* IComponent::getParent() const
	{
		return m_pParent;
	}

	////////////////////////////////////////////////////////////
	void IComponent::setParent(GameObject* pParent)
	{
		m_pParent = pParent;
	}

	////////////////////////////////////////////////////////////
	Transform& IComponent::getTransform()
	{
		return m_pParent->getTransform();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool IComponent::compareTag(const std::string& tag) const
	{
		return m_pParent->getTag() == tag;
	}

} // namespace jackal