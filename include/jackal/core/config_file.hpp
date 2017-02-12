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

#ifndef __JACKAL_CONFIG_FILE_HPP__
#define __JACKAL_CONFIG_FILE_HPP__

//====================
// C++ includes
//====================
#include <string>                         // Storing the variants by string-key.
#include <unordered_map>                  // Hashmap for all of the different variants.

//====================
// C++ includes
//====================
#include <jackal/utils/non_copyable.hpp> // ConfigFile should be copied or assigned to different objects.
#include <jackal/math/vector2.hpp>       // Returning elements as a Vector2.
#include <jackal/math/vector3.hpp>       // Returning elements as a Vector3.

namespace jackal 
{
	//====================
	// Enumerations
	//====================
	enum class eVariantType
	{
		INT,
		UINT,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		STRING,
		VECTOR2I,
		VECTOR2F,
		VECTOR2D,
		VECTOR3I,
		VECTOR3F,
		VECTOR3D, 
		VECTOR4I,
		VECTOR4F, 
		VECTOR4D
	};

	struct ConfigVariant_t
	{
		//====================
		// Member variables
		//====================
		eVariantType type; ///< The data-type of the variant (int, float etc).
		std::string value; ///< The value attached to the variable.

	};

	class ConfigFile final : NonCopyable
	{
	private:
		//====================
		// Member variables
		//====================
		std::unordered_map<std::string, ConfigVariant_t> m_variants; ///< All of the variants and their attached values.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Removes inline comments from the currently parsing line.
		///
		/// When a line is being parsed, it will remove any comments currently
		/// inline so that undefined variables or behavior is avoided.
		///
		/// @param line   The current line being parsed.
		///
		////////////////////////////////////////////////////////////
		void removeComments(std::string& line);

		////////////////////////////////////////////////////////////
		/// @brief Provides additional checks to the variable and parses it.
		///
		/// This method will check that each individual line within the configuration
		/// file is properly formatted and structured. This method is only invoked when
		/// a variable or type is discovered on the currently parsing line. This method
		/// will provide additional checks and only add the variable if all of the
		/// correct structural conditions are met. 
		///
		/// @brief variable     The name of the variable to parse.
		/// @brief datatype     The variables specified datatype.
		/// @brief value        The value attached to the variable.
		///
		/// @returns True if no formatting errors were detected with the current variable.
		///
		////////////////////////////////////////////////////////////
		bool parseVariant(const std::string& variable, const std::string& datatype, const std::string& value);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the ConfigFile object.
		////////////////////////////////////////////////////////////
		explicit ConfigFile();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ConfigFile object.
		////////////////////////////////////////////////////////////
		~ConfigFile() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a variable from the configuration file.
		///
		/// When the user wishes to retrieve a value from the configuration
		/// file, this method can be invoked with the specified datatype. The
		/// datatype must match the type within the configuration file or a
		/// empty value is returned. This method relies on template specialization
		/// in order to retrieve the correct variables and corresponding values.
		///
		/// @param variable     The string literal name of the config variable.
		///
		/// @returns            The value attached to the variable, or an empty value if not found.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		T get(const std::string& variable) const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Opens and parses the configuration file.
		///
		/// When the configuration file is opened, it will parse and process
		/// the variables contained within the file and ready them for use
		/// and retrieval. If any errors or formatting issues occur during parsing,
		/// a message is logged to the external log files with additional information.
		/// This method utilises the VirtualFileSystem system so configurations can be
		/// loaded from several different directories.
		///
		/// @param filename     The filename of the configuration file to parse.
		///
		/// @returns            True if the file parsed successfully.
		///
		////////////////////////////////////////////////////////////
		bool open(const std::string& filename);
	};

	////////////////////////////////////////////////////////////
	/// @brief Retrieves an integer value from the ConfigFile.
	///
	/// This is the template specialization for retrieving integer
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	int ConfigFile::get<int>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves an unsigned integer value from the ConfigFile.
	///
	/// This is the template specialization for retrieving unsigned integer
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	unsigned int ConfigFile::get<unsigned int>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a floating point value from the ConfigFile.
	///
	/// This is the template specialization for retrieving floating point
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	float ConfigFile::get<float>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a double value from the ConfigFile.
	///
	/// This is the template specialization for retrieving double
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	double ConfigFile::get<double>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a boolean value from the ConfigFile.
	///
	/// This is the template specialization for retrieving boolean
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	bool ConfigFile::get<bool>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a string value from the ConfigFile.
	///
	/// This is the template specialization for retrieving string
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An empty value is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	std::string ConfigFile::get<std::string>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Vector2i value from the ConfigFile.
	///
	/// This is the template specialization for retrieving Vector2i
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An zero-ed Vector2 is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////
	template <>
	Vector2i ConfigFile::get<Vector2i>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Vector2f value from the ConfigFile.
	///
	/// This is the template specialization for retrieving Vector2i
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An zero-ed Vector2 is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////	
	template <>
	Vector2f ConfigFile::get<Vector2f>(const std::string& variable) const;

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Vector2d value from the ConfigFile.
	///
	/// This is the template specialization for retrieving Vector2i
	/// values from the config file. If the variable is not found 
	/// or is the incorrect datatype. An zero-ed Vector2 is returned.
	///
	/// @param variable The name of the variable.
	///
	/// @returns The value attached to the variable.
	///
	////////////////////////////////////////////////////////////	
	template <>
	Vector2d ConfigFile::get<Vector2d>(const std::string& variable) const;

} // namespace jackal

#endif//__JACKAL_CONFIG_FILE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::ConfigVariant_t
/// @ingroup utils
///
/// The ConfigVariant_t struct is a convenience struct that is used
/// by the ConfigFile class for storing information about the different
/// variables within the configuration file, such as the type
/// and value.
///
/// Due to its internal use only wihin the ConfigFile class, it is
/// not exposed to the lua scripting interface for use by users.
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::ConfigFile
/// @ingroup utils
///
/// jackal::ConfigFile is a class that is used to parse and format
/// the Jackal Engines configuration files and prepare them for use
/// within the engine. The configuration files are used to determine
/// aspects of the application that should rarely change throughout all 
/// uses and instances of the application.
///
/// As generic .ini files lack additional information, jackal engine configuration
/// files allow for static type definitions and sectioning of variables, in order
/// to make it easier for the user to define and write effective config files.
/// Below is an example of a simple configuration file, the files must end with the
/// extension .jcfg.
///
/// Config file example:
/// @code 
/// # jcfg files allow for both line and inline comments.
///
/// global_variable: string = "I'm global!"  # This variable is not tied to a section.
///
/// [Section1]	# This is declaring a section of variables.
/// local_variable: boolean = true
///
/// [Section2]	# Multiple sections can be declared.
/// local_variable: int = 1
/// @endcode
///
/// Communication with these variables is done by parsing the file and using some simple
/// template specialization.
///
/// C++ Code example: 
/// @code
/// // Mount the drives.
/// auto& vfs = jackal::VirtualFileSystem::getInstance();
/// vfs.mount("config", "assets/config");
///
/// jackal::ConfigFile config;
/// config.open("~config/main.jcfg");	// Config files can use the VirtualFileSystem.
///
///	std::string globalVariable = config.get<std::string>("global_variable");	// Retrieving the global variable.
///
///	// Retrieving variables from sections is done by using the dot operator.
///	bool localVariable1 = config.get<bool>("Section1.local_variable");
///	int localVariable2 = config.get<int>("Section2.local_variable");
/// @endcode
///
/// The variables within a ConfigFile can also be loaded and parsed within the lua interface.
/// As lua does not support templates, it makes use of named methods for retrieving data of different
/// types.
///
/// @code
/// -- Mount the drives.
/// local vfs = VirtualFileSystem.get_instance()
/// vfs:mount("config", "assets/config")
///
/// local config = ConfigFile()
/// config:open("~config/main.jcfg") -- Config files can use the VirtualFileSystem.
///
///	local global_variable = config:get_string("global_variable") -- Retrieving the global variable.
///	
///	-- Retrieving variables from sections is done by using the dot operator.
///	local local_variable1 = config:get_boolean("Section1.local_variable")
///	local local_variable2 = config:get_int("Section2.local_variable")
/// @endcode
///
////////////////////////////////////////////////////////////