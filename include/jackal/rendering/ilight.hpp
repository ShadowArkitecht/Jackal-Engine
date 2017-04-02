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

#ifndef __JACKAL_ILIGHT_HPP__
#define __JACKAL_ILIGHT_HPP__

//====================
// Jackal includes
//====================
#include <jackal/core/icomponent.hpp> // ILight interface is a type of component.
#include <jackal/math/colour.hpp>     // Stores the colour of the ILight.

namespace jackal
{
	class ILight : public IComponent
	{
	private:
		//====================
		// Member variables
		//====================
		Colour m_colour;      ///< The base colour of the ILight interface.
		Colour m_specularity; ///< The specular effect of the ILight.
		float  m_intensity;   ///< The intensity of the ILight.

	protected:
		//====================
		// Protected methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Initialises the member variables of the ILight interface.
		///
		/// This method is called internally by the subsequent child classes
		/// create method. It is used to initialise the member variables of the
		/// class if the creation was successful.
		///
		/// @param colour    The colour of the light.
		/// @param intensity How intense the light is within the scene.
		///
		////////////////////////////////////////////////////////////
		virtual bool init(const Colour& colour, float intensity);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Constructor for the ILight object.
		///
		/// The constructor is only called implicitly by the child light
		/// classes and is used to set the name of the component, so that
		/// it can be retrieved by name within the scripting interface.
		///
		/// @param name  The name of ILight object.
		///
		////////////////////////////////////////////////////////////
		explicit ILight(const std::string& name);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the ILight object.
		////////////////////////////////////////////////////////////
		virtual ~ILight() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the colour of the ILight interface.
		///
		/// The colour controls the colouring effects this light will have
		/// upon relevant objects within the scene. By default the light
		/// is set to pure white (1.0, 1.0, 1.0, 1.0).
		///
		/// @returns The current colour of the ILight interface.
		///
		////////////////////////////////////////////////////////////
		const Colour& getColour() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the colour of the ILight interface.
		///
		/// The colour controls the colouring effects this light will have
		/// upon relevant objects within the scene. By default the light
		/// is set to pure white (1.0, 1.0, 1.0, 1.0).
		///
		/// @param colour The new colour of the ILight interface.
		///
		////////////////////////////////////////////////////////////
		void setColour(const Colour& colour);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the specularity of the ILight interface.
		///
		/// The specularity of the light controls how reflective a surface
		/// is when being hit by this light source. The higher the specularity,
		/// the more relfective a surface will be.
		///
		/// @returns The specularity effect of the ILight interface.
		///
		////////////////////////////////////////////////////////////
		const Colour& getSpecularity() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the specularity of the ILight interface.
		///
		/// The specularity of the light controls how reflective a surface
		/// is when being hit by this light source. The higher the specularity,
		/// the more relfective a surface will be.
		///
		/// @param specularity  The new specularity effect of the ILight interface.
		///
		////////////////////////////////////////////////////////////
		void setSpecularity(const Colour& specularity);

		////////////////////////////////////////////////////////////
		/// @brief Sets the colour of the ILight interface.
		///
		/// The colour controls the colouring effects this light will have
		/// upon relevant objects within the scene. By default the light
		/// is set to pure white (1.0, 1.0, 1.0, 1.0).
		///
		/// @param r The new red colour of the ILight interface.
		/// @param g The new green colour of the ILight interface.
		/// @param b The new blue colour of the ILight interface.
		/// @param a The new alpha colour of the ILight interface. (Default is 1.0).
		///
		////////////////////////////////////////////////////////////
		void setColour(float r, float g, float b, float a = 1.0f);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the intensity of the ILight interface.
		///
		/// The intensity controls how powerful the effects of this light
		/// will be to the relevant lights within a scene. The higher the 
		/// intensity, the brighter a light will be.
		///
		/// @returns The current intensity of the ILight.
		///
		////////////////////////////////////////////////////////////
		float getIntensity() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the intensity of the ILight interface.
		///
		/// The intensity controls how powerful the effects of this light
		/// will be to the relevant lights within a scene. The higher the 
		/// intensity, the brighter a light will be.
		///
		/// @param intensity The new intensity of the ILight.
		///
		////////////////////////////////////////////////////////////
		void setIntensity(float intensity);
	};

} // namespace jackal

#endif//__JACKAL_ILIGHT_HPP__