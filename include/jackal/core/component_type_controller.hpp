///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Jackal Engine
// 2016 - Benjamin Carter (bencarterdev@outlook.com)
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

#ifndef __JACKAL_COMPONENT_TYPE_CONTROLLER_HPP__
#define __JACKAL_COMPONENT_TYPE_CONTROLLER_HPP__

//====================
// Jackal includes
//====================
#include <unordered_map>                  // Mapping each component by a unique hash code.
#include <typeinfo>                       // Retrieving the type of the component passed in.

//====================
// C++ includes
//====================
#include <jackal/core/component_type.hpp> // Inserting ComponentType objects into the map.
#include <jackal/core/icomponent.hpp>     // Each component is mapped to a specific type.

namespace jackal
{
	class ComponentTypeController final
	{
	private:
		//====================
		// Member variables
		//====================
		mutable std::unordered_map<unsigned int, ComponentType> m_types; ///< Each type of component.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the ComponentTypeController object.
		///
		/// The default constructor initialises all of the member
		/// variables to default values and creates a blank unordered map.
		///
		////////////////////////////////////////////////////////////
		explicit ComponentTypeController();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ComponentTypeController object.
		////////////////////////////////////////////////////////////
		~ComponentTypeController() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the ComponentType object by the typeid.
		///
		/// Each type of the ComponentType is unique, if it does not
		/// currently exist within the type map, it is created and 
		/// inserted.
		///
		/// @returns Retrieves the unique ComponentType object of the type.
		///
		////////////////////////////////////////////////////////////
		const ComponentType& getType(const std::type_info& type) const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the ComponentType object by the class type.
		///
		/// Each type of the ComponentType is unique, if it does not
		/// currently exist within the type map, it is created and 
		/// inserted. This method will insert a entry by the component.
		///
		/// @returns Retrieves the unique ComponentType object of the component class.
		////////////////////////////////////////////////////////////
		template <typename T>
		const ComponentType& getType() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the component bitset mapped to a component.
		///
		/// Each component within the engine is mapped to a corresponding
		/// component type id object. This method will return the bit 
		/// assigned the component interface.
		///
		/// @returns    The component bit mapped to the component.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		const std::bitset<32>& getBit() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the component ID mapped to a component.
		///
		/// Each component within the engine is mapped to a corresponding
		/// component type id object. This method will return the ID 
		/// assigned the component interface.
		///
		/// @returns    The component ID mapped to the component.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		unsigned int getID() const;
	};

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	const ComponentType& ComponentTypeController::getType() const
	{
		static_assert(std::is_base_of<IComponent, T>::value, "The template does not inherit from the IComponent class.");
		return this->getType(typeid(T));
	}

	////////////////////////////////////////////////////////////
	template <typename T>
	const std::bitset<32>& ComponentTypeController::getBit() const
	{
		static_assert(std::is_base_of<IComponent, T>::value, "The template does not inherit from the IComponent class.");
		return this->getType(typeid(T)).getBit();
	}

	////////////////////////////////////////////////////////////
	template <typename T>
	unsigned int ComponentTypeController::getID() const
	{
		static_assert(std::is_base_of<IComponent, T>::value, "The template does not inherit from the IComponent class.");
		return this->getType(typeid(T)).getID();
	}

} // namespace jackal

#endif//__JACKAL_COMPONENT_TYPE_CONTROLLER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::ComponentTypeController
/// @ingroup core
///
/// The jackal::ComponentTypeController is a class that is used
/// internally by the entity component system for mapping each 
/// component within the application to a unique type. These types
/// are used for mapping the components attached to entities to the
/// correct sub-systems, for additional behaviour and functionality.
///
/// Due to the internal use of the controller, it is not exposed
/// to the lua scripting interface and no code example is provided.
///
////////////////////////////////////////////////////////////