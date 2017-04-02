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

#ifndef __JACKAL_DIRECTIONAL_LIGHT_HPP__
#define __JACKAL_DIRECTIONAL_LIGHT_HPP__

//====================
// Jackal includes
//====================
#include <jackal/rendering/ilight.hpp> // DirectionalLight is a type of light.
#include <jackal/math/vector3.hpp>     // Stores the direction of the light.

namespace jackal
{
	class DirectionalLight final : public ILight
	{
	private:
		//====================
		// Member variables
		//====================
		Vector3f m_direction; ///< The direction the light will face.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Initialises the member variables of the DirectionalLight object.
		///
		/// This method is invoked by the subsequent create method, it is used
		/// to initialise all of the member variables to specified values. 
		/// If the creation or initialisation fails, the object will return a null
		/// value.
		///
		/// @param colour     The colour of the light.
		/// @param intensity  The intensity of the light upon the scene.
		/// @param direction  The direction of the light.
		///
		/// @returns True if the light initialises the variables correctly.
		///
		////////////////////////////////////////////////////////////
		bool init(const Colour& colour, float intensity, const Vector3f& direction);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the DirectionalLight object.
		////////////////////////////////////////////////////////////
		explicit DirectionalLight();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the DirectionalLight object.
		////////////////////////////////////////////////////////////
		~DirectionalLight() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the direction of the DirectionalLight object.
		///
		/// The direction controls which way the light of this object
		/// will shine within a scene. Manipulation of this direction can
		/// be used to simulate various effects, such as the sun.
		///
		/// @returns The current direction of the DirectionalLight.
		///
		////////////////////////////////////////////////////////////
		Vector3f getDirection() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the direction of the DirectionalLight object.
		///
		/// The direction controls which way the light of this object
		/// will shine within a scene. Manipulation of this direction can
		/// be used to simulate various effects, such as the sun.
		///
		/// @param direction The new direction of the liht.
		///
		////////////////////////////////////////////////////////////
		void setDirection(const Vector3f& direction);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Binding the directional light to a lua object for scripting.
		///
		/// So that directional lights can be referenced within scripts, they need
		/// to be exposed as lua objects for additional functionality. This allows
		/// this light to be manipulated within scripts for additional behavior.
		///
		/// @returns The component as a lua object.
		///
		////////////////////////////////////////////////////////////
		sol::table lua_asObject() const override;

		////////////////////////////////////////////////////////////
		/// @brief Creates a new DirectionalLight object and initialises it for use.
		///
		/// This method is a simple wrapper around retrieving a DirectionalLight
		/// object from the pools and initializing its member variables to the
		/// defined values. If the pool fails to retrieve a resource or the
		/// initialization fails, the method will return a null value.
		///
		/// @param colour     The colour of the light.
		/// @param intensity  The intensity of the light upon the scene.
		/// @param direction  The direction of the light.
		///
		/// @returns A DirectionalLight from the pool if initialisation was successful.
		///
		////////////////////////////////////////////////////////////
		static DirectionalLight* create(const Colour& colour, float intensity, const Vector3f& direction);
	};

} // namespace jackal

#endif//__JACKAL_DIRECTIONAL_LIGHT_HPP__
