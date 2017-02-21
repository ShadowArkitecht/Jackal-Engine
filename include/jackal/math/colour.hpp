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

#ifndef __JACKAL_COLOUR_HPP__
#define __JACKAL_COLOUR_HPP__

//====================
// Member variables
//====================
#include <jackal/utils/json/json.hpp> // Serializing and de-serializing json objects.

namespace jackal
{
	class Colour final
	{
	public:
		//====================
		// Member variables
		//====================
		float r; ///< The "red" value of the colour.
		float g; ///< The "green" value of the colur.
		float b; ///< The "blue" value of the colour.
		float a; ///< The "alpha" value of the colour.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Colour object.
		///
		/// The default Colour constructor will set the default colour to
		/// white. (1.0, 1.0, 1.0, 1.0).
		///
		////////////////////////////////////////////////////////////
		explicit Colour();

		////////////////////////////////////////////////////////////
		/// @brief Constructs a new Colour object with a defined red, green and blue values.
		///
		/// When this constructor is called, it can be used to explicitly 
		/// set the red, green and blue values of a Colour. The alpha value
		/// is set to 1.0.
		///
		/// @param r   The red component of the Colour.
		/// @param g   The green component of the Colour.
		/// @param b   The blue component of the Colour.
		///
		////////////////////////////////////////////////////////////
		explicit Colour(float r, float g, float b);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a new Colour object with a defined red, green, blue and alpha value.
		///
		/// When this constructor is called, it can be used to explicitly
		/// set the red, green, blue and alpha values of a Colour. 
		///
		///
		/// @param r   The red component of the Colour.
		/// @param g   The green component of the Colour.
		/// @param b   The blue component of the Colour.
		/// @param a   The alpha component of the Colour.
		///
		////////////////////////////////////////////////////////////
		explicit Colour(float r, float g, float b, float a);
	};

	//====================
	// Functions
	//====================
	////////////////////////////////////////////////////////////
	/// @brief Serializes the Colour object to a json object.
	///
	/// When the application saves instances for persistence use,
	/// any objects that utilise the Colour object as a member
	/// variable can be successfully serializes as a json object.
	///
	/// @param j       The json object to serialize to.
	/// @param vector  The colour to serialize from.
	///
	////////////////////////////////////////////////////////////
	void to_json(nlohmann::json& j, const Colour& colour);

	////////////////////////////////////////////////////////////
	/// @brief De-serializes a json object as a Colour value.
	///
	/// When a Colour object is de-serialized, it will use the values
	/// declared within the json object and create a Colour from each
	/// member field.
	///
	/// @param j      The json object to de-serialize from.
	/// @param vector The colour to de-serialize into. 
	///
	////////////////////////////////////////////////////////////
	void from_json(const nlohmann::json& j, Colour& colour);

} // namespace jackal

#endif//__JACKAL_COLOUR_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Colour
/// @ingroup math
///
/// The jackal::Colour class is a simple wrapper class that is
/// used to represent the colours of meshes and objects within the
/// application. It contains simple methods for manipulating colour
/// such as interpolation and combining colours.
///
/// Due to the constant use througbout the application, it is exposed
/// to the lua scripting interface to alter the colours of materials
/// dynamically.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a new colour.
/// Colour red(1.0f, 0.0f, 0.0f);
///
/// Interpolate from red to green.
/// Colour lerped = Colour::lerp(red, Colour(0.0f, 1.0f, 0.0f), Time::getDeltaTime());
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create a new colour.
/// local red = Colour(1.0, 0.0, 0.0)
///
/// -- Interpolate from red to green.
/// local lerped = Colour.lerp(red, Colour(0.0, 1.0, 0.0), Time.deltatime());
/// @endcode
///
////////////////////////////////////////////////////////////
