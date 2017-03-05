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
// Static variables
//====================
template <typename T>
T* ResourceCache<T>::m_default = nullptr;

//====================
// Ctor and dtor
//====================
////////////////////////////////////////////////////////////
template <typename T>
ResourceCache<T>::ResourceCache() 
	: NonCopyable(), m_resources(), m_log("logs/engine_log.txt")
{
}

////////////////////////////////////////////////////////////
template <typename T>
ResourceCache<T>::~ResourceCache()
{
	this->empty();
}

//====================
// Getters and setters
//====================
////////////////////////////////////////////////////////////
template <typename T>
T* ResourceCache<T>::get(const std::string& name)
{
	auto itr = m_resources.find(name);
	// The resource has been found, retrieve it.
	if (itr != std::end(m_resources))
	{	
		return itr->second;
	}
	// The resource wasn't found, create a new one.
	T* pResource = new T();
	if (!pResource->load(name))
	{
		m_log.warning(m_log.function(__FUNCTION__, name), "Failed to load resource, returning default object.");
		return m_default;
	}

	// Add it to the map and return it.
	m_resources.insert(std::make_pair(name, pResource));
	return pResource;
}

////////////////////////////////////////////////////////////
template <typename T>
std::unordered_map<std::string, T*> ResourceCache<T>::getResources() const
{
	return m_resources;
}

//====================
// Methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
void ResourceCache<T>::empty()
{
	for (auto& resource : m_resources)
	{
		if (resource.second)
		{
			delete resource.second;
			resource.second = nullptr;
		}
	}

	m_resources.clear();
}