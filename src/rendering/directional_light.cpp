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
#include <jackal/rendering/directional_light.hpp> // DirectionalLight class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	DirectionalLight::DirectionalLight()
		: ILight("DirectionalLight"), m_direction()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Vector3f DirectionalLight::getDirection() const
	{
		return m_direction;
	}

	////////////////////////////////////////////////////////////
	void DirectionalLight::setDirection(const Vector3f& direction)
	{
		m_direction = direction;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool DirectionalLight::init(const Colour& colour, float intensity, const Vector3f& direction)
	{
		if (!ILight::init(colour, intensity))
		{
			return false;
		}

		m_direction = direction;

		return true;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	sol::table DirectionalLight::lua_asObject() const // override
	{
		return sol::table();
	}

	////////////////////////////////////////////////////////////
	DirectionalLight* DirectionalLight::create(const Colour& colour, float intensity, const Vector3f& direction)
	{
		// TODO(BEN): Return the object from a object pool.
		DirectionalLight* pLight = new DirectionalLight();
		if (pLight && pLight->init(colour, intensity, direction))
		{
			return pLight;
		}

		return nullptr;
	}

} // namespace jackal