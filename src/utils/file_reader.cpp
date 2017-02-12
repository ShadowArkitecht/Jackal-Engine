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
#include <jackal/utils/file_reader.hpp>          // FileReader class declaration.
#include <jackal/utils/log.hpp>                  // Logging warnings or errors to the external logs.
#include <jackal/utils/constants.hpp>            // Using the constant log location.
#include <jackal/core/virtual_file_system.hpp>   // Using the virtual file paths.

namespace jackal
{	
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt");

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	FileReader::FileReader()
		: m_file(), m_lines(), m_absolutePath()
	{
	}

	////////////////////////////////////////////////////////////
	FileReader::~FileReader()
	{
		this->close();
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	std::vector<std::string> FileReader::getLines() const
	{
		return m_lines;
	}

	////////////////////////////////////////////////////////////
	std::string FileReader::getAbsolutePath() const
	{
		return m_absolutePath;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool FileReader::read(const std::string& filename)
	{
		if (!VirtualFileSystem::getInstance().resolve(filename, m_absolutePath))
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. File does not exist.");
			return false;
		}
		
		m_file.open(m_absolutePath, std::ios::in | std::ios::binary);
		if (m_file.fail())
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. File failed to open.");
			m_file.close();

			return false;
		}
		
		std::string line;
		while (std::getline(m_file, line))
		{
			m_lines.push_back(line);
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	void FileReader::close()
	{
		m_file.close();
	}

} // namespace jackal