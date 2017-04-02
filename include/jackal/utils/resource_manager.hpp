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
#include <array>                            // Storing the time stamps for each Shader object.
#if _DEBUG
#include <mutex>                            // Locking when the Shader are being re-loaded.
#include <thread>                           // File reading and time-stamping is passed to a seperate thread.
#endif

//====================
// Jackal includes
//====================
#include <jackal/utils/singleton.hpp>       // ResourceManager is a singleton object.
#include <jackal/utils/resource_cache.hpp>  // Different caches for the all the resources. 
#include <jackal/utils/resource_handle.hpp> // A RAII is a handle to the resource object.
#include <jackal/rendering/material.hpp>    // Storing materials, shaders and textures within the manager.
#include <jackal/rendering/model.hpp>       // Storing models.
#include <jackal/scripting/script.hpp>      // Storing scripts.

namespace jackal
{
	class ResourceManager : public Singleton<ResourceManager>
	{
		friend class Singleton<ResourceManager>;

	private:
		//====================
		// Member variables
		//====================
		ResourceCache<Material>                    m_materials;      ///< The resource cache for all the materials.
		ResourceCache<Shader>                      m_shaders;        ///< The resource cache for all the shaders.
		ResourceCache<Texture>                     m_textures;       ///< The resource cache for all the textures.
		ResourceCache<Model>                       m_models;         ///< The resource cache for all the models.
		ResourceCache<Script>                      m_scripts;        ///< The resource cache for all the scripts.

#if _DEBUG
		using TimeArray = std::array<int64_t, static_cast<int>(eShaderType::MAX)>;

		std::unordered_map<std::string, TimeArray> m_timeStamps;     ///< The time stamps for all of the different shaders.
		std::vector<Shader*>                       m_changedShaders; ///< A list of all the changed shaders.
		bool                                       m_listening;      ///< Whether the seperate thread is listening for changes.
		std::mutex                                 m_mutex;          ///< Mutex locking for shader reloading.
		std::thread                                m_listener;       ///< Seperate thread for file change listening.
#endif
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

#if _DEBUG
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
#endif

	public:
		//====================
		// Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ResourceManager.
		////////////////////////////////////////////////////////////
		~ResourceManager() = default;

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
		ResourceHandle<T> get(const std::string& filename);

#if _DEBUG
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
#endif

		////////////////////////////////////////////////////////////
		/// @brief Destroys the ResourceManager and release the retained resources
		///
		/// This method is typically only invoked when the application is
		/// about to close, it clears all of the retained resources and
		/// joins the shader watching thread if currently within debug
		/// mode.
		///
		////////////////////////////////////////////////////////////
		void destroy();
	};

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Material object from the resource cache.
	///
	/// When this method is invoked, it will use one of the resource cache
	/// of materials to retrieve a value without constantly having to allocate
	/// new materials.
	///
	/// @param filename    The filename of the material to retrieve.
	///
	/// @returns           The material to retrieve from the caches.
	///
	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Material> ResourceManager::get(const std::string& filename);
	
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
	ResourceHandle<Shader> ResourceManager::get(const std::string& filename);
	
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
	ResourceHandle<Texture> ResourceManager::get(const std::string& filename);

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Model object from the resource cache.
	///
	/// When this method is invoked, it will use one of the resource cache
	/// of models to retrieve a value without constantly having to allocate
	/// new models.
	///
	/// @param filename    The filename of the model to retrieve.
	///
	/// @returns           The model to retrieve from the caches.
	///
	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Model> ResourceManager::get(const std::string& filename);

	////////////////////////////////////////////////////////////
	/// @brief Retrieves a Script object from the resource cache.
	///
	/// When this method is invoked, it will use one of the resource cache
	/// of scripts to retrieve a value without constantly having to allocate
	/// new scripts.
	///
	/// @param filename    The filename of the scripts to retrieve.
	///
	/// @returns           The script to retrieve from the caches.
	///
	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Script> ResourceManager::get(const std::string& filename);

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
