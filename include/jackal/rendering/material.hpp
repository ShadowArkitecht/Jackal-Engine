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

#ifndef __JACKAL_MATERIAL_HPP__
#define __JACKAL_MATERIAL_HPP__ 

//====================
// Jackal methods
//====================
#include <jackal/utils/resource.hpp>     // Material is a type of resource.
#include <jackal/rendering/shader.hpp>   // Load in and retain a shader.
#include <jackal/rendering/texture.hpp>  // Load in and retain a texture.
#include <jackal/math/colour.hpp>        // Default colour applied to the Material.

namespace jackal
{
	class Material : public Resource
	{
	private:
		//====================
		// Member variables
		//====================
		int64_t m_ID;      ///< The unique ID of the material, generated from shader and textures.
		Shader  m_shader;  ///< The shader attached to the material.
		Texture m_texture; ///< The texture attached to the material.
		Colour  m_colour;  ///< Overlay colour applied to the material.

	public:
		//====================
		// Ctor and dtor
		//====================
		/// @brief Default constructor for the Material object.
		///
		/// The default constructor initialises all of the member
		/// variables to default values. The material is useable in this
		/// state but will not render any behavior. 
		///
		////////////////////////////////////////////////////////////
		explicit Material();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Material object.
		///
		/// The destructor is default as the Material does not retain
		/// any textures or shaders, their lifetime is managed by the
		/// resource manager object.
		///
		////////////////////////////////////////////////////////////
		~Material() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique ID of the material.
		///
		/// The unique ID of the material is a culmination of the ID's
		/// of the shader and the texture. The ID is predominantly used
		/// to batch rendering calls together to prevent changes in textures
		/// or shaders.
		///
		/// @returns The unique ID of the material.
		///
		////////////////////////////////////////////////////////////
		int64_t getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the shader attached to this material.
		///
		/// The material contains definitions for one shader and textures.
		/// A material can only contain one shader. This method will retrieve
		/// the shader attached to the material.
		///
		/// @returns The shader attached to this material.
		///
		////////////////////////////////////////////////////////////
		const Shader& getShader() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the texture associated with this material.
		///
		/// Currently the material only supports single textures. This
		/// method will retrieve the texture associated with the material.
		///
		/// @returns The texture attached to this material.
		///
		////////////////////////////////////////////////////////////
		const Texture& getTexture() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the colour associated wtih this material
		///
		/// The colour controls an overlay colour that will be applied to
		/// all meshes that reference this material. If the texture of the
		/// material should not be altered when rendering, the colour should
		/// be set to (1.0, 1.0, 1.0, 1.0).
		///
		/// @returns The colour associated with this material.
		///
		////////////////////////////////////////////////////////////
		const Colour& getColour() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the colour of this material.
		///
		/// The colour controls an overlay colour that will be applied to
		/// all meshes that reference this material. If the texture of the
		/// material should not be altered when rendering, the colour should
		/// be set to (1.0, 1.0, 1.0, 1.0).
		///
		/// @param colour   The new colour of the material.
		///
		////////////////////////////////////////////////////////////
		void setColour(const Colour& colour);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Loads in the data of the Material from an external json file.
		///
		/// So that the data is seperate from the application, the definition for
		/// a material can be loaded in from an external json file. The Material
		/// parsing will also utilising the parsing of shaders and textures from other
		/// json sources. 
		///
		/// If the parsing of the material fails, a messages will be logged to the
		/// external log and the application will continue.
		///
		/// @param filename  The file directory of the data file.
		///
		/// @returns True if the data managed to parse successfully.
		/// 
		////////////////////////////////////////////////////////////
		bool load(const std::string& filename) override;

		////////////////////////////////////////////////////////////
		/// @brief Processes the material and updates the shader.
		///
		/// The process method is just a simple wrapper method around the
		/// Shader::process method, which will be invoked with a reference
		/// to this material.
		///
		////////////////////////////////////////////////////////////
		void process();

		////////////////////////////////////////////////////////////
		/// @brief Binds a material for use.
		///
		/// When a material a bound, it will bind the shader and texture
		/// object associated with this material and ready the next render
		/// pass with their defined behavior.
		///
		/// @param material The material object to bind.
		///
		////////////////////////////////////////////////////////////
		static void bind(const Material& material);

		////////////////////////////////////////////////////////////
		/// @brief Unbind the material object.
		///
		/// When the material object is unbound, it unbinds the shader
		/// and texture associated with this material.
		///
		////////////////////////////////////////////////////////////
		static void unbind();
	};

} // namespace jackal

#endif//__JACKAL_MATERIAL_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Material
/// @ingroup rendering
///
/// The jackal::Material is a class that is utilised to connect
/// different shaders and textures together into a single class
/// that can be assigned to different objects to alter their rendering
/// behavior. The Material is just a simple convenience class to
/// easily change the rendering behavior and appearance of different
/// meshes.
///
/// Specific elements of the material are exposed to the lua
/// scripting interface for alteration.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a new Material object and load it.
/// Material material;
/// material.load("assets/materials/basic-material.json");
///
/// // Change the colour.
/// material.setColour(Colour(1.0f, 0.0f, 0.0f));
///
/// // Bind the material.
/// Material::bind(material);
/// // Render.
/// Material::unbind();
/// @endcode
///
////////////////////////////////////////////////////////////
