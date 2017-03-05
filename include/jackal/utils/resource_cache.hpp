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

#ifndef __JACKAL_RESOURCE_CACHE_HPP__
#define __JACKAL_RESOURCE_CACHE_HPP__

//====================
// C++ includes
//====================
#include <unordered_map>                 // Storage type for all the different resources.
#include <string>                        // Key for the map of the resources. 

//====================
// Jackal includes
//====================
#include <jackal/utils/non_copyable.hpp> // ResourceCache is a non-copyable object.
#include <jackal/utils/log.hpp>          // Logging warning and errors.
#include <jackal/utils/constants.hpp>    // Constant log location.

namespace jackal
{
	template <typename T>
	class ResourceCache final : NonCopyable
	{
	private:
		//====================
		// Member variables
		//====================
		std::unordered_map<std::string, T*> m_resources; ///< The resources stored by the cache.
		static T*                           m_default;   ///< The default resource of the cache, returned if errors.
		DebugLog                            m_log;       ///< Logging any warnings or errors to the external log.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the ResourceCache object.
		/// 
		/// The default constructor for the ResourceCache object will initialise
		/// all of the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit ResourceCache();

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the ResourceCache object.
		///
		/// The destructor for the ResourceCache object will de-allocate 
		/// all of the resource currently retained by the cache. 
		///
		////////////////////////////////////////////////////////////
		~ResourceCache();

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a resource from the ResourceCache.
		///
		/// When an object is retrieved from the cache, it will first check
		/// if it is retained by the cache. If the object is not found, 
		/// the overidden Resource load method is called, if the load method
		/// fails, a message is logged to the external engine log and the default
		/// object of the cache is returned.
		///
		/// @param name   The key name of the resource to retrieve.
		///
		/// @returns      The Resource associated with the key.
		///
		////////////////////////////////////////////////////////////
		T* get(const std::string& name);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the resources of the cache.
		///
		/// The cache stores all of the resources within a map, this is
		/// used to retrieve resources by a hashed key value. This method
		/// will return all of the resources within the cache. 
		///
		/// @returns  The resources mapped to the cash.
		///
		////////////////////////////////////////////////////////////
		std::unordered_map<std::string, T*> getResources() const;

		////////////////////////////////////////////////////////////
		/// @brief Empties the ResourceCache.
		/// 
		/// When the empty method is invoked, it will clear and de-allocate
		/// all of the resource currently being retained by the cache, this
		/// method is commonly used if the flag for the Scene is flagged as 
		/// deleteOnLoad.
		///
		////////////////////////////////////////////////////////////
		void empty();
	};

	//====================
	// Jackal includes
	//====================
	#include <jackal/utils/resource_cache.inl> // Class inline definition.

} // namespace jackal

#endif//__JACKAL_RESOURCE_CACHE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::ResourceCache
/// @ingroup utils
///
/// The jackal::ResourceCache is template class that is used
/// to retain objects that inherit from the Resource class. It is
/// commonly used to control the lifetime of objects and prevent
/// constant initialization of objects that may be similar or the
/// same. 
///
/// A resource is retrieved by invoking the ResourceCache::get, if the
/// resource was not found but could not load, a default resource is 
/// returned to prevent undefined behavior. Due to the internal use
/// of the class, it is not exposed to the lua scripting interface.
///
/// @code
/// using namespace jackal;
///
/// // Create a ResourceCache object of type Shader.
/// ResourceCache<Shader> shaders;
///
/// // Retrieve an object from the cache by using the location of a json file.
/// Shader* pShader = shaders.get("assets/shaders/basic.json");
///
/// // Use the shader.
/// Shader::bind(*pShader);
/// // Render objects.
/// Shader::unbind();
/// @endcode
///
////////////////////////////////////////////////////////////