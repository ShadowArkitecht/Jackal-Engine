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
#include <jackal/utils/file_system.hpp> // FileSystem class declaration.

//====================
// Additional includes
//====================
#ifdef WIN32
#include <Windows.h>                    // Checking the existence of files within Windows.
#elif __linux__
#include <sys/stat.h>                   // Checking the existence of files within Linux.
#endif

namespace jackal 
{
	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool FileSystem::exists(const std::string& filename) const
	{
#ifdef WIN32
		DWORD result = GetFileAttributes(filename.c_str());
		return !(result == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
#elif __linux__
		struct stat info;
		return stat(filename.c_str(), &info) == 0;
#endif
		return false;
	}

} // namespace jackal 