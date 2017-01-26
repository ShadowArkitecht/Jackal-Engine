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

#ifndef __JACKAL_FILE_POLICY_HPP__
#define __JACKAL_FILE_POLICY_HPP__

//====================
// C++ includes
//====================
#include <fstream>                    // Loading a file from disk and writing to it.

//====================
// Jackal includes
//====================
#include <jackal/utils/ipolicy.hpp>  // FilePolicy is a type of IPolicy.

namespace jackal 
{
	class FilePolicy final : public IPolicy 
	{
	private:
		//====================
		// Member variables
		//====================
		std::ofstream m_file; ///< Loading the external file and writing to it.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the FilePolicy object.
		///
		/// The constructor calls the default constructor of the parent
		/// IPolicy class and sets the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit FilePolicy();

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the FilePolicy object.
		///
		/// The destructor will close the opened stream that is used to
		/// stream information to the external file to prevent further use.
		///
		////////////////////////////////////////////////////////////
		~FilePolicy();

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Opens the FilePolicy object, ready for writing.
		///
		/// The open method is overriden method of the parent IPolicy
		/// class. This method will check the file existence of the 
		/// path argument and attempt to open it. If any problems are
		/// encountered, a console error message is invoked and the 
		/// method will return false.
		///
		/// @param name   The name of the file to open and write to.
		///
		/// @returns      True if the file opened successfully.
		///
		////////////////////////////////////////////////////////////
		bool open(const std::string& name) override;

		////////////////////////////////////////////////////////////
		/// @brief Writes a message to the external file.
		///
		/// The write method is the overriden method of the parent IPolicy
		/// class. This method will write to the external file that was 
		/// opened when the open method was invoked. If the file failed
		/// to open, no message will be written.
		///
		/// @param msg     The message to write to the file.
		///
		////////////////////////////////////////////////////////////
		void write(const std::string& msg) override; 
	};

} // namespace jackal

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::FilePolicy
/// @ingroup utils
///
/// The jackal::FilePolicy is a policy object that inherits from
/// the IPolicy interface. It is responsible for opening an external
/// file (such as a text file) and writing information to it. It is 
/// predominantly used by the external logging system for logging
/// over-arching engine warning and errors to a file for 
/// debugging. If the policy fails to open a file, an error message
/// is produced to the console. 
///
/// Due to the nature and predominantly internal use of the class,
/// it is not exposed to the lua scripting interface.
///
/// C++ Code example:
/// @code
/// // Create a policy object and open a file.
/// jackal::FilePolicy policy;
/// policy.open("logs/engine_log.txt");
///
/// // Write to the external file.
/// policy.write("This is a message!");
/// @endcode
///
////////////////////////////////////////////////////////////

#endif//__JACKAL_FILE_POLICY_HPP__