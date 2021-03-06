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
#include <jackal/math/vector2.hpp> // Vector2 class declaration.

namespace jackal
{
	//====================
	// Functions
	//====================
	////////////////////////////////////////////////////////////
	void to_json(nlohmann::json& j, const Vector2f& vector) 
	{
		j = nlohmann::json{{ "x", vector.x }, { "y", vector.y }};
	}

	////////////////////////////////////////////////////////////
	void from_json(const nlohmann::json& j, Vector2f& vector) 
	{
		vector.x = j.value("x", 0.0f);
		vector.y = j.value("y", 0.0f);
	}

	////////////////////////////////////////////////////////////
	void to_json(nlohmann::json& j, const Vector2i& vector)
	{
		j = nlohmann::json{ { "x", vector.x },{ "y", vector.y } };
	}

	////////////////////////////////////////////////////////////
	void from_json(const nlohmann::json& j, Vector2i& vector)
	{
		vector.x = j.value("x", 0);
		vector.y = j.value("y", 0);
	}

	////////////////////////////////////////////////////////////
	void to_json(nlohmann::json& j, const Vector2d& vector)
	{
		j = nlohmann::json{ { "x", vector.x },{ "y", vector.y } };
	}

	////////////////////////////////////////////////////////////
	void from_json(const nlohmann::json& j, Vector2d& vector)
	{
		vector.x = j.value("x", 0.0);
		vector.y = j.value("y", 0.0);
	}

} // namespace jackal