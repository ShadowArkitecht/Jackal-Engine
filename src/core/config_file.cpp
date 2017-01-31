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
#include <algorithm>                             // Removing specific characters from string.
#include <cctype>                                // Using c-style functors.

//====================
// Jackal includes
//====================
#include <jackal/core/config_file.hpp>           // ConfigFile class declaration.
#include <jackal/utils/log.hpp>                  // Logging warnings and errors.
#include <jackal/utils/file_system.hpp>          // Checking the file has the correct extension.
#include <jackal/utils/constants.hpp>            // Using the defined constants for extensions.
#include <jackal/utils/file_reader.hpp>          // Reading in information from disk.


namespace jackal 
{
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt");  // Log errors and warnings.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	ConfigFile::ConfigFile()
		: NonCopyable(), m_variants()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	template <>
	int ConfigFile::get<int>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::INT)
			{
				return std::stoi(cv.value);
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return 0;
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return 0;
	}

	////////////////////////////////////////////////////////////
	template <>
	unsigned int ConfigFile::get<unsigned int>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::UINT)
			{
				return std::stoi(cv.value);
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return 0;
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return 0;
	}

	////////////////////////////////////////////////////////////
	template <>
	float ConfigFile::get<float>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::FLOAT)
			{
				return std::stof(cv.value);
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return 0.0f;
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return 0.0f;	
	}

	////////////////////////////////////////////////////////////
	template <>
	double ConfigFile::get<double>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::DOUBLE)
			{
				return std::stod(cv.value);
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return 0.0;
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return 0.0;	
	}

	////////////////////////////////////////////////////////////
	template <>
	bool ConfigFile::get<bool>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::BOOLEAN)
			{
				return cv.value == "true";
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return false;
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return false;
	}

	////////////////////////////////////////////////////////////
	template <>
	std::string ConfigFile::get<std::string>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::STRING)
			{
				return cv.value;
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Incorrect datatype.");
				return "";
			}
		}

		log.warning(log.function(__FUNCTION__, variable), "Unable to find variable.");
		return "";
	}

	////////////////////////////////////////////////////////////
	template <>
	Vector2i ConfigFile::get<Vector2i>(const std::string& variable) const
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			ConfigVariant_t cv = itr->second;
			if (cv.type == eVariantType::VECTOR2I)
			{
				std::stringstream ss(cv.value);
				std::vector<std::string> elements;

				while (ss.good())
				{
					std::string el;
					std::getline(ss, el, ',');
					elements.push_back(el);
				}

				Vector2i result;
				result.x = std::stoi(elements.at(0));
				result.y = std::stoi(elements.at(1));

				return result;
			}
			else
			{
				log.warning(log.function(__FUNCTION__, variable), "Unable to find variable");
				return Vector2i::zero();
			}
		}

		return Vector2i::zero();
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	void ConfigFile::removeComments(std::string& line)
	{
		for (unsigned int i = 0; i < line.length(); i++) {
			if (line.at(i) == '#') {
				line = line.substr(0, i);
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////
	bool ConfigFile::parseVariant(const std::string& variable, const std::string& datatype, const std::string& value)
	{
		auto itr = m_variants.find(variable);
		if (itr != std::end(m_variants))
		{
			log.warning(log.function(__FUNCTION__, variable, datatype, value), "Failed to parse.", variable, "is already defined.");
			return false; 
		}

		auto isDigit = [](const std::string& value) -> bool {
			return value.find_first_not_of("-.0123456789") == std::string::npos;
		};

		ConfigVariant_t variant;

		if (datatype == "int" || datatype == "uint" || datatype == "float" || datatype == "double")
		{
			if (!isDigit(value))
			{	
				log.warning(log.function(__FUNCTION__, variable, datatype, value), "Failed to parse. It is not numerical");
				return false;
			}

			variant.type = datatype == "int" ? eVariantType::INT :
						   datatype == "uint" ? eVariantType::UINT :
						   datatype == "float" ? eVariantType::FLOAT :
						   datatype == "double" ? eVariantType::DOUBLE :
						   eVariantType::INT;
						   
			variant.value = value;
		} 
		else if (datatype == "boolean")
		{
			if (value != "true" || value != "false")
			{
				log.warning(log.function(__FUNCTION__, variable, datatype, value), "Failed to parse. It is not a boolean value");
				return false;
			}

			variant.type = eVariantType::BOOLEAN;
			variant.value = value;
		}
		else if (datatype == "string")
		{
			if (value.at(0) != '\"' || value.at(value.length() - 1) != '\"')
			{
				log.warning(log.function(__FUNCTION__, variable, datatype, value), "Failed to parse. It is not a correctly formatted string");
				return false;
			}

			variant.type = eVariantType::STRING;
			variant.value = value.substr(1, value.length() - 2);
		} 
		else if (datatype.substr(0, 4) == "vec2") 
		{
			if (value.at(0) == '(' && value.at(value.length() - 1) == ')') 
			{
				switch (datatype.at(4))
				{
				case 'i':
					variant.type = eVariantType::VECTOR2I;
					break;

				case 'd':
					variant.type = eVariantType::VECTOR2D;
					break;
				}
			} 
			else
			{
				log.warning(log.function(__FUNCTION__, variable, datatype, value), "Failed to parse. It is not a correctly formatted vec2");
				return false;
			}

			variant.value = value.substr(1, value.length() - 1);
		}

		m_variants.insert(std::make_pair(variable, variant));
		return true;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool ConfigFile::open(const std::string& filename)
	{
		FileSystem system;
		if (!system.hasExtension(filename, Constants::Extensions::CONFIGURATION))
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. Incorrect extension.");
			return false;
		}

		FileReader reader;
		if (!reader.read(filename))
		{
			return false;
		}

		std::string section;
		for (std::string line : reader.getLines())
		{
			// Removing any redundant/irritating characters.
			line.erase(std::remove_if(std::begin(line), std::end(line), [](char c) {
				return c == '\r' || c == '\n' || c == '\t' || std::isspace(c);
			}));

			if (line.empty())
			{
				continue;
			}

			// For some reason the last two characters are copied, remove them.
			if (line.at(0) != '[')
			{
				line = line.substr(0, line.length() - 2);
			}

			switch (line.at(0))
			{
				case '#':
					continue;

				case '[':
					section = line.substr(1, line.length() - 2);
					continue;
			}

			int namePos = -1;
			int dataPos = -1;

			for (std::size_t i = 0; i < line.length(); i++)
			{
				switch (line.at(i))
				{
					case ':':
						namePos = i;
						break;

					case '=':
						dataPos = i;
						break;
				}
			}

			if (namePos == -1 || dataPos == -1)
			{
				log.warning(log.function(__FUNCTION__, filename), "Failed to parse line:", line);
				continue;
			}

			this->removeComments(line);
			std::string variable = line.substr(0, namePos);

			if (m_variants.find(variable) != std::end(m_variants))
			{
				log.warning(log.function(__FUNCTION__, filename), variable, "is already defined within the config file.");
				continue;
			}

			std::string datatype = line.substr(namePos + 1, (dataPos - namePos) - 1);
			std::string value = line.substr(dataPos + 1, line.length());

			if (!section.empty())
			{
				variable = section + "." + variable;
			}

			if (!this->parseVariant(variable, datatype, value))
			{
				continue;
			}
		}

		log.debug(log.function(__FUNCTION__, filename), "Parsed successfully.");
		return true;
	}

} // namespace jackal