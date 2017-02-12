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
#include <sstream>                             // Seperating the directories by '/'.

//====================
// Jackal includes
//====================
#include <jackal/core/virtual_file_system.hpp> // VirtualFileSystem class declaration.
#include <jackal/utils/file_system.hpp>        // Testing the location of files and directories.

namespace jackal
{
	//====================
	// Local variables
	//====================
	const char VFS_SYMBOL = '~';	// Represents the starting character for virtual paths.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	VirtualFileSystem::VirtualFileSystem()
		: Singleton<VirtualFileSystem>(), m_paths()
	{
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void VirtualFileSystem::mount(const std::string& path, const std::string& directory)
	{
		m_paths[path].push_back(directory);
	}

	////////////////////////////////////////////////////////////
	void VirtualFileSystem::dismount(const std::string& path)
	{
		const auto itr = m_paths.find(path);

		if (itr != std::end(m_paths))
		{
			m_paths[path].clear();
		}
	}

	////////////////////////////////////////////////////////////
	void VirtualFileSystem::dismountAll()
	{
		m_paths.clear();
	}

	////////////////////////////////////////////////////////////
	bool VirtualFileSystem::resolve(const std::string& path, std::string& result)
	{
		FileSystem system;
		// The directory passed in is not utilising a virtual path, do a standard directory look-up.
		if (path.at(0) != VFS_SYMBOL)
		{
			result = path;
			return system.exists(result);
		}

		std::size_t lastIndex = path.find_last_of('/');
		std::string dir = path.substr(1, lastIndex - 1);

		if (m_paths.find(dir) == std::end(m_paths))
		{
			return false;
		}		

		std::string remainder = path.substr(dir.size() + 1, path.length());
		for (auto p : m_paths[dir])
		{
			p.append(remainder);
			if (system.exists(p))
			{
				result = p;
				return true;
			}
		}

		return true;
	}

} // namespace jackal