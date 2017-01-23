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

#ifndef __JACKAL_NON_COPYABLE_HPP__
#define __JACKAL_NON_COPYABLE_HPP__

namespace  jackal 
{
	class NonCopyable
	{
	private:
		//====================
		// Private ctor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Deleted copy constructor for the NonCopyable object.
		///
		/// This method disallows the use of the copy constructor by this
		/// object and its subsequent children. Deleting the copy constructor
		/// can prevent undefined behavior when copying an object that is 
		/// by definition unique.
		///
		////////////////////////////////////////////////////////////
		explicit NonCopyable(const NonCopyable&) = delete;

		//====================
		// Private operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Deleted assignment operator for the NonCopyable object.
		///
		/// This disallows the use of assignment between different instances
		/// of this class and its children. Similar to deleting the copy constructor,
		/// this can be used to prevent undefined behavior when assigning complex
		/// or unique objects. 
		///
		/// returns		This method would return a reference to the newly assigned object.
		///
		////////////////////////////////////////////////////////////
		NonCopyable& operator=(const NonCopyable&) = delete;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the NonCopyable object.
		////////////////////////////////////////////////////////////
		explicit NonCopyable() = default;

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the NonCopyable object.
		////////////////////////////////////////////////////////////
		virtual ~NonCopyable() = default;
	};

} // namespace jackal 

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::NonCopyable
/// @ingroup utils
///
/// The jackal::NonCopyable is a simple class that is primarily 
/// designed to be inherited from. Any object that inherits from this
/// class is prevented from copying or assigning objects to a different
/// instance of that object. The class abstracts and deletes the copy
/// constructor and assignment operators.
///
/// Due to the nature of the class and its uses within the application,
/// it is not exposed to the lua scripting interface and is purely
/// for internal use.
///
////////////////////////////////////////////////////////////

#endif//__JACKAL_NON_COPYABLE_HPP__