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
#include <string>                             // Overriding the lua to_string operator.

//====================
// Jackal includes
//====================
#include <jackal/scripting/math_wrapper.hpp> // MathWrapper class declaration.
#include <jackal/math/colour.hpp>            // Wrapping Colour class.

namespace jackal
{
	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	void MathWrapper::bindColour(sol::state& state)
	{
		state.new_usertype<Colour>("Colour",
			// Constructors
			sol::constructors<sol::types<>, sol::types<float, float, float>, sol::types<float, float, float, float>>(),
			// Variables
			"r", &Colour::r,
			"g", &Colour::g,
			"b", &Colour::b, 
			"a", &Colour::a,
			// Operators
			sol::meta_function::to_string, [](const Colour& c) {
				return c.lua_toString();
			},
			"white", &Colour::white,
			"black", &Colour::black);
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void MathWrapper::bind(sol::state& state)
	{
		this->bindColour(state);
	}

} // namespace jackal