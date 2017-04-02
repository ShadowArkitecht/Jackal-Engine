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
// C++ includes
//====================
#include <algorithm>                   // Removing game objects from middle of vector.

//====================
// Jackal includes
//====================
#include "jackal/core/isystem.hpp"	   // Class declaration.
#include "jackal/core/game_object.hpp" // Updating and removing game objects.

namespace jackal 
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	ISystem::ISystem(const EntityComponentSystem& ecs)
		: m_ecs(ecs), m_systemBits(), m_typeBits(), m_objects() 
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	const TypeSet& ISystem::getSystemBits() const 
	{
		return m_systemBits;
	}

	////////////////////////////////////////////////////////////
	void ISystem::setSystemBits(const TypeSet& bits) 
	{
		m_systemBits = bits;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	void ISystem::remove(GameObject* pObject) 
	{
		auto itr = std::find(std::begin(m_objects), std::end(m_objects), pObject);

		if (itr != std::end(m_objects)) {
			m_objects.erase(itr);
			pObject->removeSystemBit(m_systemBits);
		}
	}

	//====================
	// Protected methods
	//====================
	////////////////////////////////////////////////////////////
	void ISystem::addTypeFlag(const TypeList<>& list) 
	{
		// EMPTY.
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void ISystem::initialize()
	{
		// EMPTY.
	}

	////////////////////////////////////////////////////////////
	void ISystem::change(GameObject* pObject) 
	{
		bool contains = (m_systemBits & pObject->getSystemBits()) == m_systemBits;
		bool interest = (m_typeBits & pObject->getTypeBits()) == m_typeBits;

		if (interest && !contains && m_typeBits.any()) 
		{
			m_objects.push_back(pObject);
			pObject->addSystemBit(m_systemBits);
		}
		else if (!interest && contains && m_typeBits.any()) 
		{
			this->remove(pObject);
		}
	}

	////////////////////////////////////////////////////////////
	void ISystem::update()
	{
		for (const auto& object : m_objects)
		{
			this->process(object);
		}
	}

} // namespace jackal
