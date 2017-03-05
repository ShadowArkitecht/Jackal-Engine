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

#ifndef __JACKAL_RESOURCE_HANDLE_HPP__
#define __JACKAL_RESOURCE_HANDLE_HPP__

//====================
// C++ includes
//====================
#include <type_traits>               // Checking that the template inherits from the Resource class.

//====================
// Jackal includes
//====================
#include <jackal/utils/resource.hpp> // Handle has to contain a object that inherits from Resoure.

namespace jackal 
{
	template <typename T>
	class ResourceHandle final
	{
		static_assert(std::is_base_of<Resource, T>::value, "The template must be of base-type Resource.");

	private:
		//====================
		// Member variables
		//====================
		T* m_pResource; ///< The base resource object this handle wraps around. 

	private:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Deleted ResourceHandle default constructor.
		////////////////////////////////////////////////////////////
		explicit ResourceHandle() = delete;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Constructor for the ResourceHandle object.
		///
		/// When the ResourceHandle is constructed, it will take a reference
		/// to the naked reference that the object will be a handle to. This
		/// object is retained during the ResourceHandle objects lifetime.
		///
		/// @param pResource The resource of the handle.
		///
		////////////////////////////////////////////////////////////
		explicit ResourceHandle(T* pResource);

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the ResourceHandle.
		///
		/// When the destructor is invoked, it will release the resource
		/// attached to this handle, decrementing its reference count and
		/// queueing for potential deletion.
		///
		////////////////////////////////////////////////////////////
		~ResourceHandle();

		//====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Overloading the reference operator.
		///
		/// The operator is used to access methods and properties of
		/// the naked resource that this handle is wrapped around. 
		///
		/// @returns A pointer to the resource attached to this handle.
		///
		////////////////////////////////////////////////////////////
		T* operator->();

		////////////////////////////////////////////////////////////
		/// @brief Overloading the reference operator.
		///
		/// The operator is used to access methods and properties of
		/// the naked resource that this handle is wrapped around. 
		///
		/// @returns A pointer to the resource attached to this handle.
		///
		////////////////////////////////////////////////////////////
		const T* operator->() const;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the resource attached to this handle.
		/// 
		/// When this method is invoked, it will access the raw resource
		/// that this object is handling. Care should be taken when directly
		/// manipulating the source, if the handle goes out of scope, the 
		/// resource attached to this handle could potentially be 
		/// de-allocated. This method should only be used by methods that
		/// expect a raw resource as a parameter.
		///
		/// @returns The raw resource of this handle object.
		///
		////////////////////////////////////////////////////////////
		T* get() const;
	};

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	ResourceHandle<T>::ResourceHandle(T* pResource)
		: m_pResource(pResource)
	{
		if (m_pResource)
		{
			m_pResource->retain();
		}
	}

	////////////////////////////////////////////////////////////
	template <typename T>
	ResourceHandle<T>::~ResourceHandle()
	{
		if (m_pResource)
		{
			m_pResource->release();
		}
	}	

	//====================
	// Operators
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	T* ResourceHandle<T>::operator->()
	{
		return m_pResource;
	}

	////////////////////////////////////////////////////////////
	template <typename T>
	const T* ResourceHandle<T>::operator->() const
	{
		return m_pResource;
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	T* ResourceHandle<T>::get() const
	{
		return m_pResource;
	}

} // namespace jackal

#endif//__JACKAL_RESOURCE_HANDLE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
/// 
/// @class ResourceHandle
/// @ingroup utils
///
/// The jackal::ResourceHandle template object is a class that
/// is used to wrap around specific resources within the application,
/// such as materials and textures. The handle contains a reference
/// counted system, that can be used to track the lifetime of objects
/// without explicitly having the manually allocate and delete resource,
/// they will be automatically garbage collected when no handles
/// remain for the resource.
///
/// The ResourceHandle is a simple smart pointer concept that aids
/// in basic memory management. Due to the internal use of the class,
/// it is not exposed to the lua scripting interface.
///
/// C++ Code example.
/// @code 
/// using namespace jackal;
///
/// // Retrieve a handle from the ResourceManager.
/// ResourceHandle<Material> material = ResourceManager::getInstance().get<Material>("material.json");
/// // Manipulate the colour.
/// material->setColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
///
/// // The material will be released when out of scope.
/// @endcode
///
////////////////////////////////////////////////////////////