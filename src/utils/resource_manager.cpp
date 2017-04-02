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

//====================
// C++ includes
//====================
#include <filesystem>                         // C++17 file system reading.

//====================
// Jackal includes
//====================
#include <jackal/utils/resource_manager.hpp>  // ResourceManager class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
#if _DEBUG
	ResourceManager::ResourceManager()
		: Singleton<ResourceManager>(), m_materials(), m_shaders(), m_textures(), m_models(), m_scripts(),
			m_timeStamps(), m_changedShaders(), m_listening(true), m_mutex(), 
				m_listener(&ResourceManager::fileChangeListener, this)
	{
	}
#else
	ResourceManager::ResourceManager()
		: Singleton<ResourceManager>(), m_materials(), m_shaders(), m_textures(), m_models(), m_scripts()
	{
	}
#endif

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Material> ResourceManager::get(const std::string& filename)
	{
		return ResourceHandle<Material>(m_materials.get(filename));
	}

	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Shader> ResourceManager::get(const std::string& filename)
	{
		return ResourceHandle<Shader>(m_shaders.get(filename));
	}

	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Texture> ResourceManager::get(const std::string& filename)
	{
		return ResourceHandle<Texture>(m_textures.get(filename));
	}

	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Model> ResourceManager::get(const std::string& filename)
	{
		return ResourceHandle<Model>(m_models.get(filename));
	}

	////////////////////////////////////////////////////////////
	template <>
	ResourceHandle<Script> ResourceManager::get(const std::string& filename)
	{
		return ResourceHandle<Script>(m_scripts.get(filename));
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
#if _DEBUG
	void ResourceManager::fileChangeListener()
	{
		namespace fs = std::experimental::filesystem;
		using namespace std::chrono_literals;

		while (m_listening)
		{
			for (const auto& shader : m_shaders.getResources())
			{
				TimeArray& array = m_timeStamps[shader.first];
				auto& objects = shader.second->getShaders();

				int index = 0;
				for (const auto& object : objects)
				{
					auto time = fs::last_write_time(fs::path(object.getFilename())).time_since_epoch().count();
					int64_t timeStamp = array[index];

					if (timeStamp != 0 && timeStamp < time)
					{
						m_changedShaders.push_back(shader.second);
					}
					array[index] = time;
					index++;
				}
			}

			std::this_thread::sleep_for(1s);
		}
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void ResourceManager::reload()
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		for (auto& shader : m_changedShaders)
		{
			shader->recompile();
		}

		m_changedShaders.clear();
	}
#endif

	////////////////////////////////////////////////////////////
	void ResourceManager::destroy()
	{
		m_materials.empty();
		m_shaders.empty();
		m_textures.empty();
		m_models.empty();
		m_scripts.empty();

#if _DEBUG
		m_listening = false;
		m_listener.join();
#endif
	}
}