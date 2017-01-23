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

#ifndef __JACKAL_FILE_SYSTEM_HPP__
#define __JACKAL_FILE_SYSTEM_HPP__

//====================
// C++ includes
//====================
#include <string> // Checking if file exists by filename.

namespace jackal 
{
	class FileSystem final 
	{
	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the FileSystem object.
		////////////////////////////////////////////////////////////
		explicit FileSystem() = default;

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the FileSystem object.
		////////////////////////////////////////////////////////////
		~FileSystem() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Checks the existence of a file on disk.
		///
		/// This method can be used to check if a file in the specified
		/// directory exists. This method will only accept local or absolute
		/// paths and does not used the VirtualFileSystem functionality.
		///
		/// @param filename    The directory or file to check the existense of.
		///
		/// @returns           True if the file has been found.
		///
		////////////////////////////////////////////////////////////
		bool exists(const std::string& filename) const;
	}; 

} // namespace jackal 

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::FileSystem
/// @ingroup utils
///
/// jackal::FileSystem is a basic utility class that is used for
/// conditional checks against local or absolute directories, such as
/// file existence and state of file. It is predominantly used by the 
/// VirtualFileSystem for checking if the virtual paths are pointing
/// to valid directories or files.
///
/// The FileSystem can be utilised by the user and is exposed to 
/// the lua scripting interface.
///
/// C++ Code example:
/// @code
/// jackal::FileSystem system;
///
/// if (system.exists("assets/textures/image.png") 
/// {
///		std::cout << "It exists!" << std::endl; 
/// }
/// @endcode
///
/// Lua Code example:
/// @code
/// local system = FileSystem()
///
/// if system:exists("assets/textures/image.png") then
///		print("It exists!")
/// end
/// @endcode
///
////////////////////////////////////////////////////////////

#endif//__JACKAL_FILE_SYSTEM_HPP__