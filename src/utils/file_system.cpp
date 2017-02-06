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
#include <vector>                       // Storing subsequent extensions of file.

//====================
// Jackal includes
//====================
#include <jackal/utils/file_system.hpp> // FileSystem class declaration.

//====================
// Additional includes
//====================
#ifdef WIN32
#include <Windows.h>                    // Checking the existence of files within Windows.
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
#endif
		return false;
	}

	////////////////////////////////////////////////////////////
	bool FileSystem::hasExtension(const std::string& file, const std::string& extension) const
	{
		std::size_t index = file.find_last_of('.');
		return index != std::string::npos ? file.substr(index + 1, file.length()) == extension : false;
	}

	////////////////////////////////////////////////////////////
	bool FileSystem::hasExtensions(const std::string& file, const std::string& extension, unsigned int count) const
	{
		std::vector<std::size_t> indices;
		for (std::size_t i = file.length(); i > 0; i--)
		{
			if (file[i] == '.')
			{
				indices.push_back(i);
			}
		}

		if (indices.size() < count)
		{
			return false;
		}

		std::size_t pos = indices.at(count - 1);
		return file.substr(pos + 1, file.length()) == extension;
	}

} // namespace jackal 