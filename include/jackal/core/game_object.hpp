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

#ifndef __JACKAL_GAME_OBJECT_HPP__
#define __JACKAL_GAME_OBJECT_HPP__

//====================
// C++ includes
//====================
#include <bitset>                     // The system and bits that the game object is related to.
#include <string>                     // Retrieving components by name.

//====================
// Jackal includes
//====================
#include <jackal/core/object.hpp>     // GameObject is a type of object within a scene.
#include <jackal/math/transform.hpp>  // The tansform of the GameObject.
#include <jackal/utils/ext/sol.hpp>   // Retrieving components as a lua table.

namespace jackal
{
	//====================
	// Jackal forward declarations
	//====================
	class IComponent;

	class GameObject final : public Object
	{
	private:
		//====================
		// Member variables
		//====================
		Transform       m_transform;   ///< The position, rotation and scale of the game object.
		unsigned int    m_ID;          ///< The unique ID of the game object.
		std::bitset<32> m_typeBits;    ///< The components attached to the game object.
		std::bitset<32> m_systemBits;  ///< The systems related to the game object.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the GameObject instance.
		///
		/// The default constructor will set all of the member variables
		/// to default values. The GameObject is use-able within the application
		/// in this current state. The default positioning and rotation of a
		/// GameObject is [0, 0, 0] with an identity rotation.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the GameObject object.
		////////////////////////////////////////////////////////////
		~GameObject() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the transform of the game object.
		///
		/// The transform is used to represent the GameObject instance
		/// within a 3D scene. The transform contains the game object's
		/// position, rotation and scale, which can be manipulated directly
		/// by invoking this method.
		///
		/// @returns A reference to the transform object of the GameObject.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform();

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique ID of the GameObject.
		///
		/// The ID is the unique way of identifying this particular GameObject,
		/// it is used for registering components to a specific GameObject.
		///
		/// @returns The unique ID of the GameObject.
		///
		////////////////////////////////////////////////////////////
		unsigned int getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the type bits of the GameObject.
		///
		/// The type bits represent which components are currently registered
		/// to this GameObject. Only one component of each type can be 
		/// attached to a game object at any one time. (Such as only one audio source).
		/// If more components on an object is needed, it is best to register
		/// another game object as a child.
		///
		/// @returns The component type bits attached to this GameObject.
		///
		////////////////////////////////////////////////////////////
		const std::bitset<32>& getTypeBits() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the new component bits of the GameObject.
		///
		/// The type bits represent which components are currently registered
		/// to this GameObject. Only one component of each type can be 
		/// attached to a game object at any one time. (Such as only one audio source).
		/// If more components on an object is needed, it is best to register
		/// another game object as a child.
		///
		/// @param bits The new component type bits for the GameObject.
		///
		////////////////////////////////////////////////////////////
		void setTypeBits(const std::bitset<32>& bits);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the system bits of the GameObject.
		///
		/// The system bits represent which systems this GameObject will be
		/// processed under. Which systems the GameObject is updated by depends
		/// on which components are attached to the GameObject. Some systems (such as
		/// mesh rendering) are relatively simple, while others (such as physics) rely
		/// on a number of components and parameters to be true.
		///
		/// @returns The system bits attached to this GameObject.
		///
		////////////////////////////////////////////////////////////
		const std::bitset<32>& getSystemBits() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the new system bits of the GameObject.
		///
		/// The system bits represent which systems this GameObject will be
		/// processed under. Which systems the GameObject is updated by depends
		/// on which components are attached to the GameObject. Some systems (such as
		/// mesh rendering) are relatively simple, while others (such as physics) rely
		/// on a number of components and parameters to be true.
		///
		/// @param bits The new system bits for the GameObject.
		///
		////////////////////////////////////////////////////////////
		void setSystemBits(const std::bitset<32>& bits);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves a component by it's class type.
		///
		/// So that components can be accessed outside the scope of the 
		/// GameObject, this method can be invoked with the component class
		/// type in question and return a pointer to the relevant component.
		/// If the component was not found, the method will return a 
		/// nullptr.
		///
		/// @tparam T  The class type of the component to retrieve.
		///
		/// @returns   A pointer to the designated component.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		T* getComponent() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves a component from a GameObject as a lua table.
		///
		/// So that components can be manipulated within lua, components
		/// can be retrieved from within a script by passing in the string
		/// literal name of the component. If the componnt is found, it will 
		/// return a lua table representation of the component, if not, it will
		/// return a nil value.
		///
		/// @param name The string literal name of the component.
		///
		/// @returns A lua table representation of a component.
		///
		////////////////////////////////////////////////////////////
		sol::table lua_getComponent(const std::string& name) const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Adds a type bit to the GameObject instance.
		///
		/// When a type is registered with the GameObject, it will determine
		/// whether it meets the requirements to be run by particular 
		/// sub-systems.
		///
		/// @param bit The bit to add.
		///
		////////////////////////////////////////////////////////////
		void addTypeBit(const std::bitset<32>& bit);

		////////////////////////////////////////////////////////////
		/// @brief Removes a type bit from the entity.
		///
		/// When a type bit is removed, it will remove the GameObject
		/// from specific systems that it no longer meets the requirements
		/// for.
		///
		/// @param bit  The bit to remove.
		///
		////////////////////////////////////////////////////////////
		void removeTypeBit(const std::bitset<32>& bit);

		////////////////////////////////////////////////////////////
		/// @brief Adds a system bit to the GameObject.
		///
		/// The system bits determine which systems the GameObject will be 
		/// processed by.
		///
		/// @param bit  The system bit to add.
		///
		////////////////////////////////////////////////////////////
		void addSystemBit(const std::bitset<32>& bit);

		////////////////////////////////////////////////////////////
		/// @brief Adds a system bit to the GameObject.
		///
		/// The system bits determine which systems the GameObject will be 
		/// processed by.
		///
		/// @param bit  The system bit to remove.
		///
		////////////////////////////////////////////////////////////
		void removeSystemBit(const std::bitset<32>& bit);

		////////////////////////////////////////////////////////////
		/// @brief Adds a component to the GameObject instance.
		///
		/// A component is a class which contains specific functionality
		/// that will change the behavior and rendering of this specific
		/// GameObject. When this method is invoked, it will add and retain
		/// a component for this GameObject. 
		///
		/// @param pComponent The component to add to the GameObject.
		///
		////////////////////////////////////////////////////////////
		void addComponent(IComponent* pComponent);

		////////////////////////////////////////////////////////////
		/// @brief Removes a component from the GameObject instance.
		///
		/// A component is a class which contains specific functionality
		/// that will change the behavior and rendering of this specific
		/// GameObject. When this method is invoked, it will remove
		/// a component for this GameObject. 
		///
		/// @tparam T The component class-type to remove.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		void removeComponent();
	};

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	T* GameObject::getComponent() const
	{
		return nullptr;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	void GameObject::removeComponent()
	{
		// TODO:
	}

} // namespace jackal

#endif//__JACKAL_GAME_OBJECT_HPP__
