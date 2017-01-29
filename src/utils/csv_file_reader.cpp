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
#include <algorithm>                        // Counting the number of commas in each line.
#include <sstream>                          // Streaming and seperating by comma.

//====================
// Jackal includes
//====================
#include <jackal/utils/csv_file_reader.hpp> // CSVFileReader class declaration.
#include <jackal/utils/log.hpp>             // Logging warnings and errors.
#include <jackal/utils/file_system.hpp>     // Checking for the correct extension.
#include <jackal/utils/constants.hpp>       // Constant for file extension.
#include <jackal/utils/file_reader.hpp>     // Loading the file from disk.

namespace jackal
{	
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt");
	const char COMMA_SYMBOL = ',';

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	CSVFileReader::CSVFileReader()
		: m_rows()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	std::size_t CSVFileReader::getRowCount() const
	{
		return m_rows.size();
	}

	////////////////////////////////////////////////////////////
	std::vector<std::string> CSVFileReader::getRow(std::size_t index) const
	{
		return m_rows.at(index);
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool CSVFileReader::read(const std::string& filename, bool uniformColumns/*= false*/)
	{
		FileSystem system;
		if (!system.hasExtension(filename, Constants::Extensions::CSV))
		{
			log.warning(log.function(__func__, filename), "Failed. Incorrect extension.");
			return false;
		}

		FileReader reader;
		if (!reader.read(filename))
		{
			return false;
		}

		std::string definition = reader.getLines().at(0);
		std::size_t columns = std::count(std::begin(definition), std::end(definition), COMMA_SYMBOL);

		for (std::size_t i = 0; i < reader.getLines().size(); i++)
		{
			std::string row = reader.getLines().at(i);
			if (uniformColumns)
			{
				if (i == 0)
				{
					continue;
				}

				std::size_t count = std::count(std::begin(row), std::end(row), COMMA_SYMBOL);

				if (count != columns)
				{
					log.warning(log.function(__func__, filename), "Failed to parse line", i, "incorrect number of elements.");
					continue;
				}
			}

			std::stringstream ss(row);
			std::vector<std::string> elements;

			while (ss.good())
			{
				std::string el;
				std::getline(ss, el, COMMA_SYMBOL);
				elements.push_back(el);
			}

			m_rows.push_back(elements);
		}

		return true;
	}

} // namespace jackal