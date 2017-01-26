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

#ifndef __JACKAL_LOG_HPP__
#define __JACKAL_LOG_HPP__

//====================
// C++ includes
//====================
#include <type_traits>                    // Checking that the template inherits from the IPolicy object.
#include <iostream>                       // Printing errors to the console.
#include <sstream>                        // Streaming the log information and sending it to the log.
#include <mutex>                          // Locking the logging to prevent unformatted messages.
#include <chrono>                         // Retrieving the current system time and run-time.
#include <ctime>                          // Converting time to a string variable.

//====================
// Jackal includes
//====================
#include <jackal/utils/non_copyable.hpp>  // The log should not be copied or assigned to different instances.
#include <jackal/utils/file_policy.hpp>   // Used to log the message externally. 

namespace jackal 
{
	template <typename T>
	class Log final : NonCopyable
	{
		static_assert(std::is_base_of<IPolicy, T>::value, "The template for the Log class must inherit from the IPolicy interface");

	private:
		//====================
		// Member variables
		//====================
		unsigned int       m_line;             ///< The current line of the log file.
		T                  m_policy;           ///< The writing policy the log will use.
		std::ostringstream m_stream;           ///< Streaming the log information into the external log.
		std::mutex         m_mutex;            ///< Locking the logging to prevent unformatted messages.

		static bool        m_debugEnabled;     ///< Whether debug messages will be logged.
		static bool        m_warningEnabled;   ///< Whether warning messages will be logged.
		static bool        m_errorEnabled;     ///< Whether error messages will be logged.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a time stamp of the system.
		///
		/// Whenever a log message is processed, it will contains a
		/// stamp (in milli-seconds) for how long the current system
		/// has been operating for. 
		///
		/// @returns  A time stamp indicating the amount of time that application has been running.
		///
		////////////////////////////////////////////////////////////
		std::string getTimeStamp() const;

		////////////////////////////////////////////////////////////
		/// @brief Formats the log message stamp.
		///
		/// Whenever a log is processed and about to be sent to the 
		/// external log, it is prefixed with a collection of information:
		/// the line number, date and time and the system time stamp.
		///
		/// @returns  A string of information about the current application.
		///
		////////////////////////////////////////////////////////////
		std::string formatStamp();

		////////////////////////////////////////////////////////////
		/// @brief Variadic unpacking method for log file writing.
		///
		/// This method is used to unpack the parameters of the variadic 
		/// templates and construct it into a format that can be streamed
		/// to the external log file.
		///
		////////////////////////////////////////////////////////////
		void write();

		////////////////////////////////////////////////////////////
		/// @brief Variadic unpacking method for log file writing.
		///
		/// This method is used to unpack the parameters of the variadic 
		/// templates and construct it into a format that can be streamed
		/// to the external log file.
		///
		/// @param arg     The first argument to write to the log file.
		/// @param args    The remaining arguments to process.
		///
		////////////////////////////////////////////////////////////
		template <typename Arg, typename... Args>
		void write(Arg&& arg, Args&&... args);

		////////////////////////////////////////////////////////////
		/// @brief Streams a function name and its arguments to the stream.
		///
		/// In order to easily identify the location of the logging, this method
		/// can be invoked to print the name of the function and its parameters
		/// and format it to a easily identifiable state. This helps in finding
		/// the source of the error and the location of the log.
		///
		/// @param ss		The stream to populate with function data.
		/// @param arg		The argument to send to the stream.
		///
		////////////////////////////////////////////////////////////
		template <typename Arg>
		void function(std::stringstream& ss, Arg&& arg) const;

		////////////////////////////////////////////////////////////
		/// @brief Streams a function name and its arguments to the stream.
		///
		/// In order to easily identify the location of the logging, this method
		/// can be invoked to print the name of the function and its parameters
		/// and format it to a easily identifiable state. This helps in finding
		/// the source of the error and the location of the log.
		///
		/// @param ss		The stream to populate with function data.
		/// @param arg      The first argument to send to the stream.
		/// @param args		The additional argument to send to the stream.
		///
		////////////////////////////////////////////////////////////
		template <typename Arg, typename... Args>
		void function(std::stringstream& ss, Arg&& arg, Args&&... args) const;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Constructs a log file for external logging of information.
		///
		/// This constructor will take the file location of the external log
		/// and utilise the IPolicy interface to open and write to it. If the
		/// log failed to open, a message is printed to the console.
		///
		/// @param filename     The file location of the log file.
		///
		////////////////////////////////////////////////////////////
		explicit Log(const std::string& filename);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor of the log file object.
		////////////////////////////////////////////////////////////
		~Log() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Writes a debug message to the external log file.
		///
		/// Makes use of C++11 variadic templates to print an arbitrary
		/// amount of arguments to the specified external log file which is
		/// prefixed with the message: "DEBUG". 
		///
		/// @param args    The arguments to pass to the log file.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		void debug(Args&&... args);

		////////////////////////////////////////////////////////////
		/// @brief Writes a warning message to the external log file.
		///
		/// Makes use of C++11 variadic templates to print an arbitrary
		/// amount of arguments to the specified external log file which is
		/// prefixed with the message: "WARNING". 
		///
		/// @param args    The arguments to pass to the log file.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		void warning(Args&&... args);

		////////////////////////////////////////////////////////////
		/// @brief Writes a error message to the external log file.
		///
		/// Makes use of C++11 variadic templates to print an arbitrary
		/// amount of arguments to the specified external log file which is
		/// prefixed with the message: "ERROR". 
		///
		/// @param args    The arguments to pass to the log file.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		void error(Args&&... args);

		////////////////////////////////////////////////////////////
		/// @brief Formats a function to be printed to the log file.
		///
		/// When this method is called. It constructs a log consisting of the
		/// function name and sends it to the external file. This method is useful 
		/// for tracking the exact location of potential bugs or errors.
		///
		/// @param func     The name of the function.
		///
		/// @returns        The result of the function formatted as a string.
		///
		////////////////////////////////////////////////////////////
		std::string function(const std::string& func) const;

		////////////////////////////////////////////////////////////
		/// @brief Formats a function to be printed to the log file.
		///
		/// When this method is called. It constructs a log consisting of the
		/// function name and its parameters and sends it to the external file.
		/// This method is useful for tracking the exact location of potential
		/// bugs or errors.
		///
		/// @param func     The name of the function.
		/// @param args     The arguments to pass to the log file.
		///
		/// @returns        The result of the function formatted as a string.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		std::string function(const std::string& func, Args&&... args) const;
	};

	//====================
	// Type definitions
	//====================
	typedef Log<FilePolicy> DebugLog; ///< Type definition for logging external messages.

	//====================
	// Jackal includes
	//====================
	#include <jackal/utils/log.inl> // Load the template definitions.

} // namespace jackal

#endif//__JACKAL_LOG_HPP__

////////////////////////////////////////////////////////////	
/// @author Benjamin Carter
///
/// @class jackal::Log
/// @ingroup utils
///
/// jackal::Log is a templated class that is used to print log information to different
/// file formats or locations. It is used extensively throughout the engine for messaging, 
/// warning or errors so that bugs and problems can be resolved quickly and the flow of 
/// the application can be properly monitored.
///
/// The templated parameter must inherit from the jackal::IPolicy object
/// so that it does not result in undefined behavior. As the logging is a templated method,
/// only specific types are exposed to the lua scripting interface. 
/// 
/// C++ Code example:
/// @code
/// const DebugLog log("logs/engine_log.txt");
///
/// void foo(int bar) {
///		log.message(log.function(__func__, bar), "function called.");
/// }
///
/// log.warning("This is a warning message.");
/// @endcode
///
/// Lua Code example:
/// @code
/// local log = ConsoleLog("");
///	log:message("This is a message from lua!")
/// @endcode
///
////////////////////////////////////////////////////////////