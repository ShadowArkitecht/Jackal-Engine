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

#ifndef __JACKAL_ISYSTEM_HPP__
#define __JACKAL_ISYSTEM_HPP__

//====================
// C++ includes
//====================
#include <vector>                                  // Storing the game objects registered with the system.

//====================
// Jackal includes
//====================
#include <jackal/utils/constants.hpp>              // Using the type definition for component bits.
#include <jackal/core/entity_component_system.hpp> // The "world" for the entity component system.

namespace jackal 
{
	//====================
	// Jackal forward declarations
	//====================
	class GameObject;

	template <typename...>
	struct TypeList {};

	class ISystem 
	{
	private:
		//====================
		// Member variables
		//====================
		const EntityComponentSystem& m_ecs;        ///< Reference to the entity component system.
		TypeSet                      m_systemBits; ///< The bits of the system.
		TypeSet                      m_typeBits;   ///< The different types the system supports.
		std::vector<GameObject*>     m_objects;    ///< Relevant entities.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Removes a game object from the current system.
		///
		/// When this method is invoked, it removes the relevant game object
		/// from the registered objects and removes the system bit from the 
		/// game object.
		///
		/// @param pObject	The GameObject instance to remove.
		///
		////////////////////////////////////////////////////////////
		void remove(GameObject* pObject);

		////////////////////////////////////////////////////////////
		/// @brief Adds a type flag to the list.
		///
		/// When a type flag is added, it registers another component type
		/// with the system. The system will be processed if all of the component
		/// conditions are met.
		///
		/// @param types The list of components.
		///
		////////////////////////////////////////////////////////////
		void addTypeFlag(const TypeList<>& types);

		////////////////////////////////////////////////////////////
		/// @brief Adds a type flag to the list.
		///
		/// When a type flag is added, it registers another component type
		/// with the system. The system will be processed if all of the component
		/// conditions are met.
		///
		/// @tparam T       The first type flag to add.
		/// @tparam Args    The other arguments to add.
		///
		////////////////////////////////////////////////////////////
		template<typename T, typename... Args>
		void addTypeFlag(TypeList<T, Args...>);

	protected:
		//====================
		// Protected methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Add component types to the type flags of the system.
		///
		/// As the engine utilises variadic templates for setting flags,
		/// this empty method is needed for parameter unwrapping.
		///
		/// @tparam Args The additional arguments of the system.
		///
		////////////////////////////////////////////////////////////
		template<typename... Args>
		void addComponentTypes();

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the ISystem object.
		///
		/// The default constructor will set all of the member variables
		/// to default values. It is also used to set the "world" for
		/// the entity component system, which contains all of the functionality
		/// needed within the component system.
		///
		/// @param ecs  The "world" entity component system.
		///
		////////////////////////////////////////////////////////////
		explicit ISystem(const EntityComponentSystem& ecs);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ISystem object.
		////////////////////////////////////////////////////////////
		virtual ~ISystem() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the system bits of the system.
		///
		/// The system bits determine which systems are relevant to the 
		/// entities, there is a limit of 32 systems.
		///
		/// @return	The system bits of the system.
		///
		////////////////////////////////////////////////////////////
		const TypeSet& getSystemBits() const;

		////////////////////////////////////////////////////////////
		/// @brief Set the system bits of the system.
		///
		/// The system bits determine which systems are relevant to the 
		/// game objects, there is a limit of 32 systems.
		///
		/// @param bit The new bits of the system.
		///
		////////////////////////////////////////////////////////////
		void setSystemBits(const TypeSet& bit);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Initialises the system and its components.
		///
		/// When initialize is called by the SystemController, it calls
		/// initialize on each system attached to the controller.
		///
		////////////////////////////////////////////////////////////
		virtual void initialize();

		////////////////////////////////////////////////////////////
		/// @brief Triggers a change within the system.
		///
		/// When the system is changed, it checks to see if each game object
		/// within the system is still relevant to the component criteria.
		/// If the entity is no longer relevant, it is removed.
		///
		/// @param pObject	The entity to check for changes.
		///
		////////////////////////////////////////////////////////////
		void change(GameObject* pObject);

		////////////////////////////////////////////////////////////
		/// @brief Method for updating all the game objects.
		///
		/// This method is called by the system controller when all of
		/// the relevant game objects need to be updated by the system.
		///
		/// @param objects The game objects to updated with the system.
		///
		////////////////////////////////////////////////////////////
		void update();

		////////////////////////////////////////////////////////////
		/// @brief Pure virtual method for processin a game object.
		///
		/// This method's behavior is overriden by the child sub-systems. 
		/// It is invoked for each individual relevant game object
		/// currently attached to the system. Each process is called within the
		/// ISystem::update method, which is invoked by the SystemController
		/// class.
		///
		/// @param pObject The GameObject instance currently being processed.
		///
		////////////////////////////////////////////////////////////
		virtual void process(GameObject* pObject) = 0;
	};

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	template<typename T, typename... Args>
	void ISystem::addTypeFlag(TypeList<T, Args...>) 
	{
		m_typeBits |= m_pECS->getEntityController().getTypeIDController().getBit<T>();
		this->addTypeFlag(TypeList<Args...>());
	}

	////////////////////////////////////////////////////////////
	template<typename...Args>
	void ISystem::addComponentTypes() 
	{
		this->addTypeFlag(TypeList<Args...>());
	}

} // namespace jackal

#endif//__JACKAL_ENTITY_SYSTEM_HPP__
