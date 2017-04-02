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
#include <jackal/rendering/ilight.hpp> // ILight interface declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	ILight::ILight(const std::string& name)
		: IComponent(name), m_colour(), m_intensity(1.0f)
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	const Colour& ILight::getColour() const
	{
		return m_colour;
	}

	////////////////////////////////////////////////////////////
	void ILight::setColour(const Colour& colour)
	{
		m_colour = colour;
	}

	////////////////////////////////////////////////////////////
	void ILight::setColour(float r, float g, float b, float a/*= 1.0f*/)
	{
		m_colour.set(r, g, b, a);
	}

	////////////////////////////////////////////////////////////
	float ILight::getIntensity() const
	{
		return m_intensity;
	}

	////////////////////////////////////////////////////////////
	void ILight::setIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	//====================
	// Protected methods
	//====================
	////////////////////////////////////////////////////////////
	bool ILight::init(const Colour& colour, float intensity)
	{
		m_colour = colour;
		m_intensity = intensity;

		return true;
	}

} // namespace jackal