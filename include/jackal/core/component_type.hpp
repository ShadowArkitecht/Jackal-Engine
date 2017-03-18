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

#ifndef __JACKAL_COMPONENT_TYPE_HPP__
#define __JACKAL_COMPONENT_TYPE_HPP__

//====================
// C++ includes
//====================
#include <bitset> // The unique bit of the component type.

namespace jackal
{
	class ComponentType final
	{
	private:
		//====================
		// Member variables
		//====================
		unsigned int           m_ID;      ///< The unique ID of the ComponentType.
		std::bitset<32>        m_bit;     ///< The unique bit of the ComponentType.
		static unsigned int    m_nextID;  ///< The next unique ID in the sequence.
		static std::bitset<32> m_nextBit; ///< The next unique bit in the sequence.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the ComponentType object.
		///
		/// When the constructor is called, the component type is assigned
		/// a unique ID and bit from the next in the sequence. This ensures
		/// that each component contains unique values.
		///
		////////////////////////////////////////////////////////////
		explicit ComponentType();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ComponentType object.
		////////////////////////////////////////////////////////////
		~ComponentType() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique ID of the ComponentType object.
		///
		/// The unique ID refers to the ID of the ComponentType. When a
		/// ComponentType is created, it is assigned a ID that is different
		/// than all other types. This ID can be used to retrieve specific
		/// types.
		///
		/// @returns The unique ID of the ComponentType.
		///
		////////////////////////////////////////////////////////////
		unsigned int getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique bit of the ComponentType object.
		///
		/// The unique bit refers to the bit of the ComponentType. When a
		/// ComponentType is created, it is assigned a bit that is different
		/// than all other bit. This bit can be used to retrieve specific
		/// types.
		///
		/// @returns The unique bit of the ComponentType.
		///
		////////////////////////////////////////////////////////////
		const std::bitset<32>& getBit() const;
	};

} // namespace jackal

#endif//__JACKAL_COMPONENT_TYPE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class ComponentType
/// @ingroup core
///
/// The jackal::ComponentType is simple class that is used
/// internally by each component within the application to assign
/// unique ID's and bits. These ID's and bits are used by the
/// component sub-systems to register the relevant entities to
/// the correct systems for additional behaviour and functionality.
///
/// Due to its internal use, it is not exposed to the lua scripting
/// interface and no code example is provided.
///
////////////////////////////////////////////////////////////