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
#include <jackal/core/component_type.hpp> // ComponentType class declaration.

namespace jackal
{
	//====================
	// Local variables
	//====================
	unsigned int ComponentType::m_nextID = 0;
	std::bitset<Constants::Components::MAX_COMPONENTS> ComponentType::m_nextBit(1);

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	ComponentType::ComponentType()
		: m_ID(m_nextID++), m_bit(m_nextBit)
	{
		m_nextBit <<= 1;
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	unsigned int ComponentType::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	const std::bitset<Constants::Components::MAX_COMPONENTS>& ComponentType::getBit() const
	{
		return m_nextBit;
	}

} // namespace jackal