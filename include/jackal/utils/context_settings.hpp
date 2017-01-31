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

#ifndef __JACKAL_CONTEXT_SETTINGS_HPP__
#define __JACKAL_CONTEXT_SETTINGS_HPP__

//====================
// Jackal includes
//==================== 
#include <jackal/utils/non_copyable.hpp> // Preventing the context settings being copied. 

namespace jackal
{
	struct ContextSettings_t final : NonCopyable
	{
		//====================
		// Member variables
		//==================== 
		unsigned int depthBits;    ///< The number of depth stencil bits within the window.
		unsigned int stencilBits;  ///< The number of stencil bits within the window.
		unsigned int majorVersion; ///< Major version of OpenGL to use.
		unsigned int minorVersion; ///< Minor version of OpenGL to use.

		//====================
		// Ctor and dtor
		//==================== 
		////////////////////////////////////////////////////////////  
		/// @brief Default destructor for the ContextSettings_t object.
		////////////////////////////////////////////////////////////  
		explicit ContextSettings_t() = default;

		////////////////////////////////////////////////////////////  
		/// @brief Constructor for the ContextSettings_t object.
		///
		/// This constructor is used to set the slightly more advanced
		/// options of the OpenGL context that will be utilised throughout
		/// the application, these variables can have a dramatic effect on the
		/// end result of the engine. 
		///
		/// @param depth    The number of depth stencil bits.
		/// @param stencil  The number of stencil bits.
		/// @param major    Major version of OpenGL to utilise.
		/// @param minor    Minor version of OpenGL to utilise. 
		///
		////////////////////////////////////////////////////////////  
		explicit ContextSettings_t(unsigned int depth, unsigned int stencil, unsigned int major, unsigned int minor);

		////////////////////////////////////////////////////////////  
		/// @brief Default destructor for the ContextSettings_t object.
		////////////////////////////////////////////////////////////  
		~ContextSettings_t() = default;
	};

} // namespace jackal 

#endif//__JACKAL_CONTEXT_SETTINGS_HPP__

////////////////////////////////////////////////////////////  
/// @author Benjamin Carter
///
/// @class jackal::ContextSettings_t
/// @ingroup utils
///
/// The jackal::ContextSettings_t is a simple struct object
/// that is utilised when the window is first initialised to set
/// and store specific values of the application that will persist
/// throughout the application, such as version and stencil bits.
///
/// Due to the structs internal use by the window, it is not
/// exposed to the lua scripting interface and no example is provided.
///
////////////////////////////////////////////////////////////  