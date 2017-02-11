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

#ifndef __JACKAL_RESOURCE_MANAGER_HPP__
#define __JACKAL_RESOURCE_MANAGER_HPP__

//====================
// C++ includes
//====================
#include <array>                           // Storing the time stamps for each Shader object.
#include <unordered_map>                   // Hash-Table for the shaders and their time-stamps.
#include <mutex>                           // Locking when the Shader are being re-loaded.
#include <thread>                          // File reading and time-stamping is passed to a seperate thread.

//====================
// Jackal includes
//====================
#include <jackal/utils/singleton.hpp>      // ResourceManager is a singleton object.
#include <jackal/utils/resource_cache.hpp> // Different caches for the all the resources. 
#include <jackal/rendering/shader.hpp>     // Storing the Shader objects within the manager.
#include <jackal/rendering/texture.hpp>    // Storing the Texture objects within the manager.

namespace jackal
{
	class ResourceManager : public Singleton<ResourceManager>
	{
		friend class Singleton<ResourceManager>;

	private:
		//====================
		// Member variables
		//====================
		using TimeArray = std::array<int64_t, static_cast<int>(eShaderType::MAX)>;

		ResourceCache<Shader>                      m_shaders;        ///< The resource cache for all the shaders.
		ResourceCache<Texture>                     m_textures;       ///< The resource cache for all the textures.

		std::unordered_map<std::string, TimeArray> m_timeStamps;     ///< The time stamps for all of the different shaders.
		std::vector<Shader*>                       m_changedShaders; ///< A list of all the changed shaders.
		bool                                       m_listening;      ///< Whether the seperate thread is listening for changes.
		std::mutex                                 m_mutex;          ///< Mutex locking for shader reloading.
		std::thread                                m_listener;       ///< Seperate thread for file change listening.

	private:
		//====================
		// Private ctor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ResourceManager.
		///
		/// The default constructor sets all of the member variables to
		/// default values and registers the thread listener thread with the
		/// fileChangeListener() method.
		///
		////////////////////////////////////////////////////////////
		explicit ResourceManager();

		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Detects changes to the different registered shaders.
		///
		/// This method is registered to a seperate thread and utilises
		/// experimental C++17 behavior. It will check the time-stamp of
		/// each registered glsl object within the application for changes made.
		/// If any of the files have been changed, the shader will be re-compiled
		/// with the new source data.
		///
		////////////////////////////////////////////////////////////
		void fileChangeListener();

	public:
		//====================
		// Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Destructor for the ResourceManager.
		///
		/// The destructor for the ResourceManager destroys all of the
		/// resources that are still being retained by the manager.
		/// It also joins the file listener thread back to the main thread.
		///
		////////////////////////////////////////////////////////////
		~ResourceManager();

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves an object from the relevant resource cache.
		///
		/// When this method is invoked, it will use one of the defined
		/// template specializations to retrieve a resource of the specified
		/// type from the caches. 
		///
		/// @param filename    The filename of the resource to retrieve.
		///
		/// @returns           The resource to retrieve from the caches.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		const T& get(const std::string& filename);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Reloads the needed shaders for additional use.
		///
		/// This method is invoked every frame, the shaders are only updated
		/// if the external glsl shaders are altered. This allows for shaders
		/// to be altered whilst the application is still functioning.
		///
		////////////////////////////////////////////////////////////
		void reload();
	};

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Shader object from the resource cache.
	///
	/// When this method is invoked, it will use one of the resource cache
	/// of shaders to retrieve a value without constantly having to allocate
	/// new shaders.
	///
	/// @param filename    The filename of the shader to retrieve.
	///
	/// @returns           The shader to retrieve from the caches.
	///
	////////////////////////////////////////////////////////////
	template <>
	const Shader& ResourceManager::get(const std::string& filename);
	
	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Texture object from the resource cache.
	///
	/// When this method is invoked, it will use one of the resource cache
	/// of textures to retrieve a value without constantly having to allocate
	/// new textures.
	///
	/// @param filename    The filename of the texture to retrieve.
	///
	/// @returns           The texture to retrieve from the caches.
	///
	////////////////////////////////////////////////////////////
	template <>
	const Texture& ResourceManager::get(const std::string& filename);

} // namespace jackal

#endif//__JACKAL_RESOURCE_MANAGER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::ResourceManager
/// @ingroup utils
///
/// The jackal::ResourceManager is a high-level class that
/// is used to retrieve and store all of the different resources
/// utilised by the application. These resources includes shaders,
/// textures and materials. The ResourceManager contains a number
/// of cache classes for all the mentioned resources.
///
/// The ResoureManager is also used to track the time stamps of shaders, 
/// this is utilised to constantly hot-swap and reload shaders when the
/// file is changed. This allows for shaders to be edited during runtime.
///
/// @code 
/// using namespace jackal;
///
/// // Get a shader from the ResourceManager.
/// Shader* pShader = ResourceManager::getInstance().get<Shader>("assets/shaders/basic.json");
///
/// // Bind the shader and render meshes.
/// Shader::bind(*pShader);
/// // Render meshes.
/// Shader::unbind();
///
/// @endcode
///
////////////////////////////////////////////////////////////
