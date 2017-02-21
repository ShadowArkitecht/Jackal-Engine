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
#include <jackal/utils/json_file_reader.hpp>   // JSONFileReader class declaration.
#include <jackal/utils/log.hpp>                // Logging warnings and errors.
#include <jackal/utils/constants.hpp>          // Using constants for log location.
#include <jackal/utils/file_system.hpp>        // Checking the extension of the file passed into the read method.
#include <jackal/utils/constants.hpp>          // File extension constants.
#include <jackal/core/virtual_file_system.hpp> // Utilising the virtual file system for file paths.

namespace jackal
{
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt"); // Logging warnings and errors

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	JSONFileReader::JSONFileReader()
		: FileReader(), m_root()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	nlohmann::json JSONFileReader::getRoot() const
	{
		return m_root;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool JSONFileReader::read(const std::string& filename)//override
	{
		FileSystem system;
		if (!system.hasExtension(filename, Constants::Extensions::JSON))
		{
			log.warning(log.function(__FUNCTION__, filename), "Incorrect file extension");
			return false;
		}

		// For some reason the file reader from the parent class won't pass correctly
		// therefore the vfs has to be re-used here aswell.
		std::ifstream file;
		if (!VirtualFileSystem::getInstance().resolve(filename, m_absolutePath))
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. File does not exist.");
			file.close();

			return false;
		}

		file.open(m_absolutePath, std::ios::in | std::ios::binary);
		if (file.fail())
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. File failed to open.");
			file.close();

			return false;
		}

		file >> m_root;
		return true;
	}
	
} // namespace jackal