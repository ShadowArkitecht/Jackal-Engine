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

#ifndef __JACKAL_MATH_WRAPPER_HPP__
#define __JACKAL_MATH_WRAPPER_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/ext/sol.hpp> // Used for wrapping classes as lua objects.

namespace jackal
{
	class MathWrapper final
	{
	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binds the Colour class to the lua scripting interface.
		///
		/// The Colour class is the class utilised by many rendering classes for
		/// controlling the colour of object. It can be manipulated within lua scripts,
		/// therefore its properties are exposed to the lua scripting interface.
		///
		/// @param state   The global lua state.
		///
		/// @returns The Colour class represented as a lua object.
		///
		////////////////////////////////////////////////////////////
		void bindColour(sol::state& state);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the MathWrapper object.
		////////////////////////////////////////////////////////////
		explicit MathWrapper() = default;

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the MathWrapper object.
		////////////////////////////////////////////////////////////
		~MathWrapper() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binds all of the math classes and exposes them to the lua interface.
		///
		/// When this method is invoked, it will bind all of the math classes
		/// that this class has exposed to the scripting interface.
		///
		/// @param state The global lua state object.
		///
		////////////////////////////////////////////////////////////
		void bind(sol::state& state);
	};

} // namespace jackal

#endif//__JACKAL_MATH_WRAPPER_HPP__

  ////////////////////////////////////////////////////////////
  /// @author Benjamin Carter
  ///
  /// @class jackal::MathWrapper
  /// @ingroup scripting
  ///
  /// The jackal::MathWrapper is a simple class that is used to
  /// wrap all of the classes contained within the jackal_math
  /// and expose them as lua objects for additional behavior within
  /// lua. Only specific classes and properties are exposed to the
  /// scripting interface.
  ///
  ////////////////////////////////////////////////////////////