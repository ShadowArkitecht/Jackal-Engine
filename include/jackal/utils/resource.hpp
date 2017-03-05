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

#ifndef __JACKAL_RESOURCE_HPP__
#define __JACKAL_RESOURCE_HPP__

//====================
// C++ includes
//====================
#include <string> // Loading a resource from a file directory.

namespace jackal
{
	class Resource
	{
	private:
		//====================
		// Member variables
		//====================
		unsigned int m_references; ///< The number of objects currently referring to this resource.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Resource object.
		////////////////////////////////////////////////////////////
		explicit Resource();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor of the Resource object.
		////////////////////////////////////////////////////////////
		virtual ~Resource() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the current reference count of the Resource.
		///
		/// The reference count refers to the number of objects that are
		/// currently referencing this resource, the resource will not be
		/// destroyed whilst it is still retained.
		///
		/// @returns The reference count of the Resource object.
		///
		////////////////////////////////////////////////////////////
		unsigned int getRefCount() const;

		////////////////////////////////////////////////////////////
		/// @brief Checks if the current Resource is being referenced.
		///
		/// A Resource is counted as referenced if its' reference count
		/// is greater than zero.
		///
		////////////////////////////////////////////////////////////
		bool isReferenced() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retains the Resource, preventing deletion.
		///
		/// When a object is retained, it will prevent the object from
		/// being de-allocated. Therefore this resource can be shared between
		/// different objects without having to worry about manual memory
		/// management.
		///
		////////////////////////////////////////////////////////////
		void retain();

		////////////////////////////////////////////////////////////
		/// @brief Releases a Resource, allowing for potential deletion.
		///
		/// When a Resource is released, it will eventually be checked to see
		/// if the object is still referenced, if the object is no longer referenced,
		/// it is cleared from the ResourceManager class. The Resource will have to be
		/// reloaded for continued use.
		///
		////////////////////////////////////////////////////////////
		void release();

		////////////////////////////////////////////////////////////
		/// @brief Loads a json resource from a file location.
		///
		/// This virtual method is overriden by the child classes and when
		/// invoked, will load an external json file and parse it. If the
		/// json file successfully parses, the object will be constructed by
		/// the json. If the json parsing fails, the method will return false
		/// and a message will be logged. The parsing can make use of the
		/// virtual file system.
		///
		/// @param filename    The filename of the json file to parse.
		///
		/// @returns           True if the json file parses successfully.
		///
		////////////////////////////////////////////////////////////
		virtual bool load(const std::string& filename) = 0;
	};

} // namespace jackal

#endif//__JACKAL_RESOURCE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Resource
/// @ingroup utils
///
/// The jackal::Resource class is a simple interface class that
/// is used by resources within the application to load their
/// behavior and functionality from external json files. Resources
/// include objects such as shaders, textures and materials. 
/// The load method is commonly invoked by the ResourceManager object
/// to load objects that have not yet been initialized.
///
/// Due to its internal use, the class is not exposed to the
/// lua scripting interface and a code example is not provided.
///
////////////////////////////////////////////////////////////
  