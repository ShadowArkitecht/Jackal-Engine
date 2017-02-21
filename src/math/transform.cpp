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
#include <jackal/math/transform.hpp> // Transform class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Transform::Transform()
		: m_position()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Vector3f Transform::getPosition() const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	void Transform::setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	////////////////////////////////////////////////////////////
	void Transform::setPosition(const Vector3f& position)
	{
		m_position = position;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Transform::translate(float x, float y, float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	////////////////////////////////////////////////////////////
	void Transform::translate(const Vector3f& translation)
	{
		m_position += translation;
	}

} // namespace jackal