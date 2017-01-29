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

#ifndef __JACKAL_FILE_READER_HPP__
#define __JACKAL_FILE_READER_HPP__

//====================
// C++ includes
//====================
#include <vector>   // The results of the FileReader.
#include <string>   // Using strings as the directory location.

namespace jackal
{
	class FileReader final
	{
	private:
		//====================
		// Member variables
		//====================
		std::vector<std::string> m_lines; ///< Each subsequent line of the stream.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the FileReader.
		///
		/// The default constructor will initialise the object and 
		/// set the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit FileReader();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the FileReader object.
		////////////////////////////////////////////////////////////
		~FileReader() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the lines of the stream loaded in.
		///
		/// When the file is loaded, each line within the external file
		/// is loaded and stored. In order to manipulate the information,
		/// it must be iterated upon.
		///
		/// @returns  All of the lines stored within the reader.
		///
		////////////////////////////////////////////////////////////
		std::vector<std::string> getLines() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Reads in the external file into memory.
		///
		/// In order for the stream to manipulated and used throughout
		/// the application, it must read and loaded in correctly. This method
		/// will fail if the file is not found (either through a local or virtual directory),
		/// or if the file fails to open correctly.
		///
		/// @param filename    The file name to open and stream.
		///
		/// @returns           True if the file opened and streamed correctly.
		///
		////////////////////////////////////////////////////////////
		bool read(const std::string& filename);
	};

} // namespace jackal

#endif//__JACKAL_FILE_READER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::FileReader
/// @ingroup utils
///
/// The jackal::FileReader object is a basic wrapper class for 
/// loading and manipulating streams of information that is 
/// currently contained on disk. The FileReader will automatically
/// provide a number of checks critical to success when loading files
/// within the Jackal Engine. 
///
/// The class can make use of the VirtualFileSystem, or load information
/// directly from a specified source. Due to the streaming nature, it is not
/// exposed to the lua scripting interface.
///
/// C++ Code example:
/// @code
/// // Create a new FileReader object and check it read the file correctly.
/// jackal::FileReader reader;
/// // The reader can use the virtual file system.
/// if (!reader.read("~data/file.txt"))
/// {
///		std::cout << "File failed to load!" << std::endl;
/// }
///
////////////////////////////////////////////////////////////