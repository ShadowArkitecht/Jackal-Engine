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

#ifndef __JACKAL_ICOMPONENT_HPP__
#define __JACKAL_ICOMPONENT_HPP__

//====================
// Jackal includes
//====================
#include <jackal/core/object.hpp>   // IComponent is a type of object.

//====================
// Additional includes
//====================
#include <jackal/utils/ext/sol.hpp> // Returning components as lua objects.

namespace jackal
{
	//====================
	// Jackal forward declarations
	//====================
	class GameObject;
	class Transform;

	class IComponent : public Object
	{
	private:
		//====================
		// Member variables
		//====================
		GameObject* m_pParent; ///< The parent GameObject instance of this component.

	private:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Removing the IComponent default constructor.
		///
		/// The default constructor is removed as each IComponent must
		/// be assigned a unique string literal name upon construction. This
		/// name is used to retrieve components from a GameObject within lua.
		///
		////////////////////////////////////////////////////////////
		explicit IComponent() = delete;

		////////////////////////////////////////////////////////////
		/// @brief Removes the copy constructor from the IComponent object.
		///
		/// The copy constructor is removed as each component should be unique
		/// to a specific object, they cannot share resources as each component
		/// stores a unique reference to its parent GameObject object.
		///
		/// @param other  The other IComponent object.
		///
		////////////////////////////////////////////////////////////
		explicit IComponent(const IComponent& other) = delete;

	protected:
		////////////////////////////////////////////////////////////
		/// @brief Initialises the component when generated from the object pool.
		///
		/// This method is invoked when the subsequent create method is 
		/// called on a child component object. It is used to initialise the
		/// variables of the class. This method by default, does not define
		/// any additional behavior.
		///
		/// @returns True if the class initialised successfully.
		///
		////////////////////////////////////////////////////////////
		virtual bool init();

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Constructor for the IComponent object.
		///
		/// This constructor is only invoked by the child component classes.
		/// It is used to set the unique name of each component that is within
		/// the application. This name can be utilised by lua scripts for retrieving
		/// components by name.
		///
		/// @param name  The name of the IComponent object.
		///
		////////////////////////////////////////////////////////////
		explicit IComponent(const std::string& name);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the IComponent object.
		////////////////////////////////////////////////////////////
		virtual ~IComponent() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the parent GameObject of this component.
		///
		/// When a component is created, it is assigned a parent GameObject
		/// instance. As each component is retrieved individually from a pool
		/// and no instances are shared, the parent is unique for each component.
		/// The component will only have a parent if it has been added to a GameObject.
		///
		/// @returns The parent GameObject instance of the component.
		///
		////////////////////////////////////////////////////////////
		GameObject* getParent() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the parent GameObject instance of this component.
		///
		/// When a component is created, it is assigned a parent GameObject
		/// instance. As each component is retrieved individually from a pool
		/// and no instances are shared, the parent is unique for each component.
		/// The component will only have a parent if it has been added to a GameObject.
		///
		/// @param The new GameObject instance parent.
		///
		////////////////////////////////////////////////////////////
		void setParent(GameObject* pParent);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the Transform of the GameObject parent.
		///
		/// This method is just a short-hand method for retrieving the 
		/// parent GameObject instance and getting its current transform.
		/// This method can be invoked to instantly get the transform of the
		/// parent GameObject.
		///
		/// @returns The transform of the parent GameObject.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform();

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Compares the tag of the parent GameObject against the argument.
		///
		/// Each GameObject can be assigned a tag, which can be used as
		/// an identifier of sorts for a group of game objects. This method
		/// can be invoked to compare whether the parent game object contains
		/// the tag passed in as the argument.
		///
		/// @param tag The tag to compare against.
		///
		/// @returns True if the argument tag and the parent GameObject tag match.
		///
		////////////////////////////////////////////////////////////
		bool compareTag(const std::string& tag) const;

		////////////////////////////////////////////////////////////
		/// @brief Binding the component to a lua object for scripting.
		///
		/// So that components can be referenced within scripts, they need
		/// to be exposed as lua objects for additional functionality. Each
		/// component may have seperate behavior for binding, therefore the method is
		/// provided as a pure virtual method.
		///
		/// @returns The component as a lua object.
		///
		////////////////////////////////////////////////////////////
		virtual sol::table lua_asObject() const = 0;
	};

} // namespace jackal

#endif//__JACKAL_ICOMPONENT_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::IComponent
/// @ingroup core
///
/// The jackal::IComponent is an abstract class that is the parent
/// of each component within the engine. It is used to store and retrieve
/// all components attached to a GameObject instance. It contains several
/// pure virtual methods that are overriden by each child class for
/// additional behaviour.
///
/// As components are commonly used as the front-end and abstraction
/// layers around more complex behaviour, it is exposed to the lua
/// scripting interface. Code examples are supplied in each component
/// child class.
///
////////////////////////////////////////////////////////////