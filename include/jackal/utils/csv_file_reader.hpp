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

#ifndef __JACKAL_CSV_FILE_READER_HPP__
#define __JACKAL_CSV_FILE_READER_HPP__

//====================
// C++ includes
//====================
#include <vector> // Storage type for each row of the csv file.
#include <string> // Each element of the csv is stored as a string.

namespace jackal 
{
	class CSVFileReader final
	{
	private:
		//====================
		// Member variables
		//====================
		std::vector<std::vector<std::string>> m_rows; ///< The number of rows and subsequent elements in the csv file.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the CSVFileReader.
		///
		/// The default constructor for the CSVFileReader will set the
		/// member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit CSVFileReader();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the CSVFileReader.
		////////////////////////////////////////////////////////////
		~CSVFileReader() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the number of rows within the csv file.
		///
		/// @returns The number of rows within the csv file.
		///
		////////////////////////////////////////////////////////////
		std::size_t getRowCount() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves a row from the csv file.
		///
		/// A csv file is made up of a collection of rows, each with a 
		/// select number of elements/values. This method will retrieve 
		/// a row from the csv file.
		///
		/// @param index   The index of the row to retrieve.
		///
		/// @returns       The row from the csv file.
		///
		////////////////////////////////////////////////////////////
		std::vector<std::string> getRow(std::size_t index) const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Reads the CSVFileReader and stores the results.
		///
		/// When the CSV file is loaded, it checks if that the file exists
		/// and can be loaded. If the file can, it will load each row of the
		/// file and store the results. A flag can be set as to whether each
		/// row should contain an equal number of elements and columns.
		///
		/// @param filename       The file name of the csv file.
		/// @param uniformColumns Whether each row should have have an equal number of elements.
		///
		/// @returns True if the csv file parsed and loaded successfully.
		///
		////////////////////////////////////////////////////////////
		bool read(const std::string& filename, bool uniformColumns = false);
	};

} // namespace jackal 

#endif//__JACKAL_CSV_FILE_READER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::CSVFileReader
/// @ingroup utils
///
/// The jackal::CSVFileReader is a wrapper class for loading
/// csv files from disk. The csv files are predominantly used
/// by the random name generation class for parsing the names
/// and data used. The csv file can be specified to either use
/// uniform rows and elements, or ignore them and loading the
/// data sequentially. 
///
/// The CSVFileReader is only used internally and is not exposed
/// the lua scripting interface. 
///
/// C++ Code example:
/// @code
/// // Create a reader and load the file.
/// jackal::CSVFileReader reader;
/// if (!reader.read("~csv/test.csv"))
/// {
///		std::cout << "File failed to load!" << std::endl;
/// }
/// @endcode
///
////////////////////////////////////////////////////////////