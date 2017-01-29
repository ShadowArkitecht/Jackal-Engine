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

#ifndef __JACKAL_PROPERTIES_HPP__
#define __JACKAL_PROPERTIES_HPP__

//====================
// C++ includes
//====================
#include <string>                           // Storing and retrieving property values by string.
#include <vector>                           // Storing the property parameters and retrieving them.
#include <sstream>                          // Creating the parameters passed into variadic methods as temporary csv files.
#include <unordered_map>                    // Key-Value map for properties and their subsequent names.

//====================
// Jackal includes
//====================
#include <jackal/utils/non_copyable.hpp>    // Preventing the Properties class from being assigned or copied. 
#include <jackal/utils/log.hpp>             // Logging warnings and errors.

namespace jackal 
{	
	//====================
	// Forward declarations
	//====================
	class ConfigFile;

	struct Property_t final
	{
		//====================
		// Member variables
		//====================
		std::string value;                                    ///< Default string value associated with the key.
		std::vector<std::pair<std::size_t, int>> parameters;  ///< The parameters and their ordering within the property.
	};

	class Properties final : NonCopyable
	{
	private:
		//====================
		// Member variables
		//====================
		static std::unordered_map<std::string, Property_t> m_properties; ///< All of the properties within the locale file.
		bool                                               m_loaded;     ///< Whether the properties file has already been loaded.
		mutable DebugLog                                   m_log;        ///< Logging any problems to an external log.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Passes a single variadic argument into the stream.
		///
		/// When a property is detected with parameters, the arguments
		/// passed into the variadic get method will be converted into a 
		/// temporary csv format. This will then be used to set and retrieve
		/// the correct arguments and map them to the desired locations. This
		/// method is used to unravel the variadic arguments of the get method.
		///
		/// @param ss   The stream to stream the csv arguments into.
		/// @tparam arg The current unravelled argument.
		///
		////////////////////////////////////////////////////////////
		template <typename Arg>
		void process(std::stringstream& ss, Arg&& arg) const;

		////////////////////////////////////////////////////////////
		/// @brief Passes several variadic arguments into the stream.
		///
		/// When a property is detected with parameters, the arguments
		/// passed into the variadic get method will be converted into a 
		/// temporary csv format. This will then be used to set and retrieve
		/// the correct arguments and map them to the desired locations. This
		/// method is used to unravel the variadic arguments of the get method.
		///
		/// @param ss     The stream to stream the csv arguments into.
		/// @tparam arg   The current unravelled argument.
		/// @tparam args  The arguments left to unravel.
		///
		////////////////////////////////////////////////////////////
		template <typename Arg, typename... Args>
		void process(std::stringstream& ss, Arg&& arg, Args&&... args) const;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Properties object.
		///
		/// The default constructor will just set the member variables
		/// to default values.
		///
		////////////////////////////////////////////////////////////
		explicit Properties();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Properties object.
		////////////////////////////////////////////////////////////
		~Properties() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a value from the properties file.
		///
		/// The properties are stored in an unordered map. Each property
		/// is mapped to a specific key, this key will retrieve the value
		/// associated with it. If the key is not found, a warning is logged
		/// and the method will return an empty string. This method should only 
		/// be used when retrieving a value that contains no parameters. 
		///
		/// @param name     The name of the key of the property.
		///
		/// @returns        The value of the key if found, a blank string if not found.
		///
		////////////////////////////////////////////////////////////
		std::string get(const std::string& name) const;
		
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a value from the properties file.
		///
		/// The properties are stored in an unordered map. Each property
		/// is mapped to a specific key, this key will retrieve the value
		/// associated with it. If the key is not found, a warning is logged
		/// and the method will return an empty string. This method should be
		/// used if the property that you are attempting to retrieve contains 
		/// a variable number of parameters that need to be set to specific 
		/// values. The method is variadic and will accept an arbitrary number
		/// of arguments.
		///
		/// @param name     The name of the key associated with the property.
		/// @tparam args    The variable number of arguments to set within the property.
		///
		/// @returns        The value of the key if found, a blank string if not.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		std::string get(const std::string& name, Args&&... args) const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Opens the specified locale file.
		///
		/// The different locale files are stored within the data/locale
		/// directory. The chosen locale for the application can be set
		/// within the jackal configuration file or changed within the 
		/// editor. If any incorrectly formatted lines are detected within the
		/// locale file, a warning is externally logged. 
		///
		/// @param filename     The filename of the locale to load.
		///
		/// @returns            True if the file opened and parsed successfully. 
		///
		////////////////////////////////////////////////////////////
		bool open(const std::string& filename);

		////////////////////////////////////////////////////////////
		/// @brief Opens the specified locale file.
		///
		/// The different locale files are stored within the data/locale
		/// directory. The chosen locale for the application can be set
		/// within the jackal configuration file or changed within the 
		/// editor. If any incorrectly formatted lines are detected within the
		/// locale file, a warning is externally logged. 
		///
		/// @param path         The virtual or local path of the properties files.
		/// @param config       The config file to load the type from.
		///
		/// @returns            True if the file opened and parsed successfully. 
		///
		////////////////////////////////////////////////////////////
		bool open(const std::string& path, const ConfigFile& config);

		////////////////////////////////////////////////////////////
		/// @brief Checks if a property exists in the locale file.
		///
		/// This method can be used to check if a property exists within the
		/// specified locale file, this can be useful if a specific element
		/// relies on a property to prevent undefined behavior.
		///
		/// @param name     The name of the property to check for.
		///
		/// @returns        True if the property exists within the locale file.
		///
		////////////////////////////////////////////////////////////
		bool exists(const std::string& name) const;
	};

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	template <typename Arg>
	void Properties::process(std::stringstream& ss, Arg&& arg) const
	{
		ss << arg;
	}

	////////////////////////////////////////////////////////////
	template <typename Arg, typename... Args>
	void Properties::process(std::stringstream& ss, Arg&& arg, Args&&... args) const
	{
		ss << arg << ',';
		this->process(ss, args...);
	}

	////////////////////////////////////////////////////////////
	template <typename... Args>
	std::string Properties::get(const std::string& name, Args&&... args) const
	{
		auto itr = m_properties.find(name);

		if (itr != std::end(m_properties))
		{
			Property_t p = itr->second;

			std::stringstream ss;
			std::vector<std::string> results;

			this->process(ss, args...);
		
			while (ss.good())
			{
				std::string sub;
				std::getline(ss, sub, ',');
				results.push_back(sub);
			}

			for (auto itr = std::rbegin(p.parameters); itr != std::rend(p.parameters); ++itr)
			{
				std::size_t start = (*itr).first;
				std::size_t end = results.at((*itr).second).length();

				std::string param = results.at((*itr).second);
				p.value.insert(start, param);

				p.value.erase(start + end, 2);
				p.value.erase(start - 1, 1);
			}

			return p.value;
		}

		m_log.warning(m_log.function(__func__, name), "Property cannot be found in properties file.");
		return std::string();
	}

} // namespace jackal

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Property_t
/// @ingroup utils
///
/// The jackal::Property_t is a simple struct that stores
/// the value and parameters of each property variable that is
/// loaded when the jackal::Properties class is utilised and 
/// opened. The struct retains locations and ordering of arguments
/// within the properties, which is used to quickly switch and change
/// values when utilising the jackal::Properties class variadic
/// templates.
///
/// No code sample is provided as the struct should never be used
/// externally of the jackal::Properties class.
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Properties
/// @ingroup utils
///
/// The jackal::Properties class is a Java influenced class for
/// loading and storing the values of an external locale properties
/// file. The locale file is used for strings and messages within the
/// application localised to the countries language. Similar to Java,
/// the jackal::Properties class supports properties with parameters, but
/// with a defined limit of 10 parameters per property. 
///
/// The Properties class can make use of the VirtualFileSystem pattern 
/// provided by the jackal::VirtualFileSystem singleton. The Properties 
/// class is only used internally by the engine and is not exposed to the
/// lua scripting interface.
///
/// C++ code example: 
/// @code
/// using namespace jackal;
///
/// // Create a properties file on the stack and load the properties.
/// // The properties are stored in a static unordered map so the
/// // file only has to be loaded once. 
/// Properties properties;
///
/// // Here the Properties class is provided with a virtual path to
/// // the property file. However this can also be handled internally
/// // by utilising the ConfigFile value of "Settings.locale".
/// properties.open("~locale/en_UK.properties");
///
/// // Retrieving a value with no arguments from the file.
/// std::string value1 = properties.get("menus.resource");
/// // Retrieving a value with arguments.
/// std::string value2 = properties.get("object.selection.name", "Test Object");
/// @endcode
///
////////////////////////////////////////////////////////////

#endif//__JACKAL_PROPERTIES_HPP__