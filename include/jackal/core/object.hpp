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

#ifndef __JACKAL_OBJECT_HPP__
#define __JACKAL_OBJECT_HPP__

//====================
// C++ includes
//====================
#include <string> // Storing the name of the Object.
#include <bitset> // The bitsets for each flag attached to this Object.

namespace jackal
{
	//====================
	// Enumerations
	//====================
	enum eHideFlags
	{
		NONE,           // No flags attached to the Object.
		DONT_SAVE,      // This object will not save when it is serialized.
		DONT_UNLOAD,    // The resource is not unloaded when a scene is changed.
		MAX_HIDE_FLAGS  // The maximum amount of flags that can be attached to an Object instance.
	};
	
	class Object
	{
	private:
		//====================
		// Member variables
		//====================
		std::string                 m_name;   ///< The name of the Object.
		bool                        m_active; ///< Whether the Object is currently active.
		std::bitset<MAX_HIDE_FLAGS> m_flags;  ///< The flags of the Object instance.
		
	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Object object.
		///
		/// The default constructor for the Object sets the member variables
		/// to default values. The name will be equal to a blank string and the
		/// object will be by default, active.
		///
		////////////////////////////////////////////////////////////
		explicit Object();
		
		////////////////////////////////////////////////////////////
		/// @brief Constructor for the Object instance. 
		///
		/// This constructor can be used to explicitly set the name
		/// of an Object instance upon construction.
		///
		/// @param name  The name of the Object instance.
		///
		////////////////////////////////////////////////////////////
		explicit Object(const std::string& name);
		
		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Object object.
		////////////////////////////////////////////////////////////
		virtual ~Object() = default;
		
		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the name of the Object.
		///
		/// The name of the Object can be used to retrieve objects by a
		/// name within a scene and is the name displayed within the 
		/// editors.
		///
		/// @returns The name of the Object.
		///
		////////////////////////////////////////////////////////////
		std::string getName() const;
		
		////////////////////////////////////////////////////////////
		/// @brief Sets the name of the Object.
		///
		/// The name of the Object can be used to retrieve objects by a
		/// name within a scene and is the name displayed within the 
		/// editors.
		///
		/// @param name   The name of the Object.
		///
		////////////////////////////////////////////////////////////
		void setName(const std::string& name);
		
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the activity of the Object.
		///
		/// If an Object is active within a scene, all of the update
		/// and rendering behaviour attached to this object will be 
		/// processed. If the Object is not active, the functionality
		/// will not be altered.
		///
		/// @returns The activity of the Object instance.
		///
		////////////////////////////////////////////////////////////
		bool isActive() const;
		
		////////////////////////////////////////////////////////////
		/// @brief Sets the new activity of the Object instance.
		///
		/// If an Object is active within a scene, all of the update
		/// and rendering behaviour attached to this object will be 
		/// processed. If the Object is not active, the functionality
		/// will not be altered.
		///
		/// @param active The new activity of the Object instance.
		///
		////////////////////////////////////////////////////////////
		void setActive(bool active);

		////////////////////////////////////////////////////////////
		/// @brief Tests whether a particular flag is active on this Object.
		///
		/// Flags can be utilised to control the specific behavior of
		/// this Object, such as whether this Object will be saved when
		/// application is serialized or if resources are retained throughout
		/// different scenes.
		///
		/// @param flag  The flag value to test against.
		///
		/// @returns True if the flag is set for the Object instance.
		///
		////////////////////////////////////////////////////////////
		bool flagSet(eHideFlags flag) const;
		
		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a flag on the object.
		///
		/// Flags can be utilised to control the specific behavior of
		/// this Object, such as whether this Object will be saved when
		/// application is serialized or if resources are retained throughout
		/// different scenes.
		///
		/// @param flag  The flag value to set.
		/// @param state The new state of the specified flag.
		///
		////////////////////////////////////////////////////////////
		void setFlag(eHideFlags flag, bool state);
	};
	
} // namespace jackal

#endif//__JACKAL_OBJECT_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class Object
/// @ingroup core
///
/// The jackal::Object is the base class for all objects that
/// will appear within a scene. It contains basic functionality
/// for storing the name and the activity of the Object instance.
/// eHideFlags can be used in conjunction with an Object instance
/// to control higher level saving and memory storage behaviour.
///
/// The Object class is never used explicitly, any manipulations are done
/// through its many child classes. Due to the common use of the Object class, 
/// its methods are exposed to the lua scripting interface.
///
////////////////////////////////////////////////////////////