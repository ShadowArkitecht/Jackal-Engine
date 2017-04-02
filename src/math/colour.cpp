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
#include <jackal/math/colour.hpp> // Colour class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Colour::Colour()
		: r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{
	}

	////////////////////////////////////////////////////////////
	Colour::Colour(float r, float g, float b)
		: r(r), g(g), b(b)
	{
	}

	////////////////////////////////////////////////////////////
	Colour::Colour(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{
	}

	//====================
	// Operators
	//====================
	////////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& os, const Colour& colour)
	{
		return os << "(" << colour.r << ", " << colour.g << ", " << colour.b << ", " << colour.a << ")";
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	void Colour::set(float r, float g, float b, float a/*= 1.0f*/)
	{
		this->r = r;
		this->g = b;
		this->b = b;
		this->a = a;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	std::string Colour::lua_toString() const
	{
		return "(" + std::to_string(this->r) + ", " + std::to_string(this->g) + ", " + 
				std::to_string(this->b) + ", " + std::to_string(this->a) + ")";
	}

	//====================
	// Properties
	//====================
	////////////////////////////////////////////////////////////
	Colour Colour::white()
	{
		return Colour(1.0f, 1.0f, 1.0f, 1.0f);
	}

	////////////////////////////////////////////////////////////
	Colour Colour::black()
	{
		return Colour(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//====================
	// Functions
	//====================
	////////////////////////////////////////////////////////////
	void to_json(nlohmann::json& j, const Colour& colour)
	{
		j = nlohmann::json{ { "r", colour.r }, { "g", colour.g }, { "b", colour.b }, { "a", colour.a } };
	}

	////////////////////////////////////////////////////////////
	void from_json(const nlohmann::json& j, Colour& colour)
	{
		colour.r = j.value("r", 1.0f);
		colour.g = j.value("g", 1.0f);
		colour.b = j.value("b", 1.0f);
		colour.a = j.value("a", 1.0f);
	}

} // namespace jackal