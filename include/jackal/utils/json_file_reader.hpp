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

#ifndef __JACKAL_JSON_FILE_READER_HPP__
#define __JACKAL_JSON_FILE_READER_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/file_reader.hpp> // Inherits from the FileReader object.
#include <jackal/utils/ext/json.hpp>    // Storing the root json value of the reader.

namespace jackal
{
	class JSONFileReader final : public FileReader
	{
	private:
		//====================
		// Member variables
		//====================
		nlohmann::json m_root;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		// @brief Default constructor for the JSONFileReader object.
		///
		/// The default constructor will call the parent FileReader 
		/// constructor and set all of the member variables to default
		/// values.
		///
		////////////////////////////////////////////////////////////
		explicit JSONFileReader();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the JSONFileReader object.
		////////////////////////////////////////////////////////////
		~JSONFileReader() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the root Json object from the reader
		///
		/// Each file that successfully parses is assigned a root object,
		/// the root refers to the first opening curly brace, and can be
		/// used to retrieve all other variables and objects within the
		/// file.
		///
		/// @returns The root object of the json file.
		///
		////////////////////////////////////////////////////////////
		nlohmann::json getRoot() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Reads in the Json file object. 
		///
		/// When the file is read in, the directory supplied is tested
		/// for existence. If the file exists and is read in successfully
		/// the json inside the file is parsed. If the file failed to parse,
		/// the method will return false and a message will be logged to the
		/// external log file. The read method can also make use of the
		/// VirtualFileSystem.
		///
		/// @param filename   The file name of the json file.
		///
		/// @returns True if the file successfully loaded and parsed.
		///
		////////////////////////////////////////////////////////////
		bool read(const std::string& filename) override;
	};

} // namespace jackal

#endif//__JACKAL_JSON_FILE_READER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::JSONFileReader
/// @ingroup utils
///
/// The jackal::JSONFileReader class is a simple class that is
/// used to load and parse a json file from an external location
/// or directory. It inherits from the FileReader object but does
/// not make use of the majority of the functionality, as the json
/// parsing relies on slightly different methodologies.
///
/// The class is mostly used internally when a resource is first loaded.
/// Due to the internal use, its functionality is not exposed to the
/// lua scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a file reader and load a json file.
/// JSONFileReader reader;
/// if (!reader.read("path/to/file.json"))
/// {
/// 	std::cout << "File failed to read!" << std::endl;
/// }
/// @endcode
///
////////////////////////////////////////////////////////////