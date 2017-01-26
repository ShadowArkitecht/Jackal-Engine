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

#ifndef __JACKAL_IPOLICY_HPP__
#define __JACKAL_IPOLICY_HPP__

//====================
// C++ includes
//====================
#include <string> // Used for opening the file and writing to the policy.

namespace jackal 
{
	class IPolicy 
	{
	public:
		//====================
		// Dtor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the IPolicy interface.
		////////////////////////////////////////////////////////////
		explicit IPolicy() = default;

		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the IPolicy interface.
		////////////////////////////////////////////////////////////
		virtual ~IPolicy() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Pure virtual method for opening the IPolicy for opening.
		///
		/// This method provides the child classes with a method to open 
		/// whatever implementation the child class chooses and readies it for
		/// writing. Open is commonly called within the Log class for 
		/// writing to external and internal logs. 
		///
		/// @param name    The name of the file to open and ready for writing.
		///
		////////////////////////////////////////////////////////////
		virtual bool open(const std::string& name) = 0;

		////////////////////////////////////////////////////////////
		/// @brief Pure virtual method to write to the opened IPolicy.
		///
		/// This method provides the child classes with a method to write
		/// to the specified IPolicy implementation. Due to the nature of different
		/// policies, each will write to its buffer or file differently.
		///
		/// @param msg		The message to write to the IPolicy.
		///
		////////////////////////////////////////////////////////////
		virtual void write(const std::string& msg) = 0;
	};
}

#endif//__JACKAL_IPOLICY_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::IPolicy
/// @ingroup utils
///
/// jackal::IPolicy is an interface class that can be used to manipulate 
/// and write to external formats without potentially exposing the 
/// complexities of file manipulation. It must be inherited from in order 
/// to provide any sort of functionality. See jackal::FilePolicy.
///
/// Due to the nature of the interface, it is not exposed for use
/// within the lua scripting interface.
///
////////////////////////////////////////////////////////////