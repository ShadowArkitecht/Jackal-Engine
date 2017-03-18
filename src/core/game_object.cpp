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
#include <jackal/core/game_object.hpp> // GameObject class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	GameObject::GameObject()
		: m_transform(), m_ID(0), m_typeBits(), m_systemBits()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Transform& GameObject::getTransform()
	{
		return m_transform;
	}

	////////////////////////////////////////////////////////////
	unsigned int GameObject::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	const std::bitset<32>& GameObject::getTypeBits() const
	{
		return m_typeBits;
	}

	////////////////////////////////////////////////////////////
	void GameObject::setTypeBits(const std::bitset<32>& bits)
	{
		m_typeBits = bits;
	}

	////////////////////////////////////////////////////////////
	const std::bitset<32>& GameObject::getSystemBits() const
	{
		return m_systemBits;
	}

	////////////////////////////////////////////////////////////
	void GameObject::setSystemBits(const std::bitset<32>& bits)
	{
		m_systemBits = bits;
	}

	////////////////////////////////////////////////////////////
	sol::table GameObject::lua_getComponent(const std::string& name) const
	{
		return sol::table();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void GameObject::addTypeBit(const std::bitset<32>& bit)
	{
		m_typeBits |= bit;
	}

	////////////////////////////////////////////////////////////
	void GameObject::removeTypeBit(const std::bitset<32>& bit)
	{
		m_typeBits &= ~bit;
	}

	////////////////////////////////////////////////////////////
	void GameObject::addSystemBit(const std::bitset<32>& bit)
	{
		m_systemBits |= bit;
	}

	////////////////////////////////////////////////////////////
	void GameObject::removeSystemBit(const std::bitset<32>& bit)
	{
		m_systemBits &= ~bit;
	}

	////////////////////////////////////////////////////////////
	void GameObject::addComponent(IComponent* pComponent)
	{
		// TODO:
	}

} // namespace jackal