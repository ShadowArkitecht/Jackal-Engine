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
#include <algorithm>                           // Removing and manipulating strings with lambdas.
#include <cctype>                              // C style lambdas.

//====================
// Jackal includes
//====================
#include <jackal/utils/properties.hpp>         // Properties class declaration.
#include <jackal/utils/file_system.hpp>        // Used to check the file has the correct extension.
#include <jackal/utils/file_reader.hpp>        // Read in files from disk.
#include <jackal/utils/constants.hpp>          // Constants used for file extensions.
#include <jackal/core/config_file.hpp>         // Loading the current properties type from the config file.

namespace jackal 
{
	//====================
	// Static variables
	//====================
	std::unordered_map<std::string, Property_t> Properties::m_properties;

	//====================
	// Local variables
	//====================
	const char COMMENT_SYMBOL = '#';	// The commented line in the property file.
	const char EQUALS_SYMBOL = '=';		// The equality operation for properties.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Properties::Properties()
		: NonCopyable(), m_loaded(false), m_log("logs/engine_log.txt")
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	std::string Properties::get(const std::string& name) const
	{
		auto itr = m_properties.find(name);

		if (itr != std::end(m_properties))
		{
			return itr->second.value;
		}

		m_log.warning(m_log.function(__FUNCTION__, name), "Property cannot be found in properties file.");
		return std::string();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Properties::open(const std::string& filename)
	{
		if (!m_loaded)
		{
			FileSystem system;
			if (!system.hasExtension(filename, "properties"))
			{
				m_log.warning(m_log.function(__FUNCTION__, filename), "Failed to load. Incorrect extension.");
				return false;
			}

			FileReader reader;
			if (!reader.read(filename))
			{
				return false;
			}

			int lineNumber = 1;
			for (std::string line : reader.getLines())
			{
				// Removing any redundant/irritating characters.
				line.erase(std::remove_if(std::begin(line), std::end(line), [](char c) {
					return c == '\r' || c == '\n' || c == '\t';
				}));

				// Empty line, no point checking it.
				if (line.empty())
				{
					lineNumber++;
					continue;
				}
				
				std::string formattedStr = line;
				
				auto f = [](unsigned char const c) { return std::isspace(c); };
				formattedStr.erase(std::remove_if(std::begin(formattedStr), std::end(formattedStr), f));

				// It's a comment in the properties file, ignore it. 
				if (formattedStr.at(0) == COMMENT_SYMBOL)
				{	
					lineNumber++;
					continue; 
				}

				std::size_t equalPos = line.find(EQUALS_SYMBOL);
				if (equalPos == std::string::npos)
				{
					m_log.warning(m_log.function(__FUNCTION__, filename), "Incorrectly formatted property on line ", lineNumber);
					lineNumber++;
					continue;
				}

				// Prevent duplicate keys from being added/changed.
				std::string key = formattedStr.substr(0, formattedStr.find(EQUALS_SYMBOL));
				if (this->exists(key))
				{
					m_log.warning(m_log.function(__FUNCTION__, filename), "Duplicate property found on line ", lineNumber, ":", key);
					lineNumber++;
					continue;
				}

				Property_t property;

				property.value = line.substr(equalPos + 1, line.size());

				for (std::size_t i = 0; i < property.value.size(); i++)
				{
					if (std::isdigit(property.value.at(i)))
					{
						// It's a property value. Add it to the list. 
						if (property.value.at(i - 1) == '{' && property.value.at(i + 1) == '}')
						{
							int value = property.value.at(i) - '0';
							property.parameters.push_back(std::make_pair(i, value));
						}
					}
				}

				if (!property.parameters.empty())
				{
					// Sort them numerically so the offsets do not change when replacing values.
					std::sort(std::begin(property.parameters), std::end(property.parameters));
				}

				m_properties.insert(std::make_pair(key, property));
				lineNumber++;
			}

			m_log.debug(m_log.function(__FUNCTION__, filename), "Parsed successfully.");
			m_loaded = true;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	bool Properties::open(const std::string& path, const ConfigFile& config)
	{
		std::string file = path + config.get<std::string>("locale_file");
		return this->open(file);
	}

	////////////////////////////////////////////////////////////
	bool Properties::exists(const std::string& name) const 
	{	
		return m_properties.find(name) != std::end(m_properties);
	}

} // namespace jackal