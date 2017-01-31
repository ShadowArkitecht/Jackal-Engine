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
#include <jackal/utils/context_settings.hpp> // ContextSettings_t struct declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//==================== 
	////////////////////////////////////////////////////////////  
	ContextSettings_t::ContextSettings_t(unsigned int depth, unsigned int stencil, unsigned int major, unsigned int minor)
		: NonCopyable(), depthBits(depth), stencilBits(stencil), majorVersion(major), minorVersion(minor)
	{
	}

} // namespace jackal 