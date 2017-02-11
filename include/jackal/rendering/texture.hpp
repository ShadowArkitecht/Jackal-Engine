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

#ifndef __JACKAL_TEXTURE_HPP__
#define __JACKAL_TEXTURE_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/resource.hpp> // Texture loads data from disk.
#include <jackal/math/vector2.hpp>   // Storing the size of the texture as a vector.

//====================
// Additional includes
//====================
#include <GL/glew.h>                 // Loading textures from memory.

namespace jackal
{
	//====================
	// Enumerations
	//====================
	enum class eWrapMode
	{
		CLAMP = GL_CLAMP,
		REPEAT = GL_REPEAT 
	};

	enum class eFilter
	{
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST
	};

	class Texture : public Resource
	{
	private:
		//====================
		// Member variables
		//====================
		GLuint    m_ID;     ///< The unique ID of the texture.
		Vector2i  m_size;   ///< The width and height of the texture.
		eWrapMode m_mode;   ///< How the texture wraps onto the rendering mesh.
		eFilter   m_filter; ///< How the image will filter on the texture.

	protected:
		//====================
		// Protected getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Sets the size of the Texture object.
		///
		/// The size of the texture can only be altered internally, once
		/// an image or html element has been loaded, the size should never
		/// be altered.
		///
		/// @param size   The size to set the texture to.
		///
		////////////////////////////////////////////////////////////
		void setSize(const Vector2i& size);

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Loads and formats an image from memory.
		///
		/// This method will load in an image from the specified file
		/// directory and format it into a format that OpenGL can understand
		/// and utilise. If the image fails to be found or cannot convert,
		/// the method will return false and log an error message. This
		/// method can make used of the virtual file system
		///
		/// @param filename   The file name of the image to load.
		/// @param wrapMode   How the texture will be applied to the mesh.
		/// @param filter     The image filtering applied to the texture.
		///
		/// @returns          True if the image loaded and formatted successfully.
		///
		////////////////////////////////////////////////////////////
		bool loadFromFile(const std::string& filename, eWrapMode wrapMode, eFilter filter);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Texture object.
		///
		/// The default constructor will set all of the member variables
		/// to default values and generate an ID for the texture.
		///
		////////////////////////////////////////////////////////////
		explicit Texture();

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the Texture object.
		///
		/// When the texture object is destroyed, it will de-allocate the
		/// GPU memory that is associated with the ID of this texture.
		///
		////////////////////////////////////////////////////////////
		virtual ~Texture();

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique ID of the Texture object.
		///
		/// The ID refers to the mapped GPU resource of this texture and
		/// is used to retrieve its specific behavior for rendering. Each
		/// texture is assigned a unique value upon construction.
		///
		/// @returns The unique ID of the Texture object.
		///
		////////////////////////////////////////////////////////////
		GLuint getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the width and height of the Texture object.
		///
		/// The width and height refer to the size (in pixels) of the 
		/// original image file passed in.
		///
		/// @returns The size of the texture image.
		////////////////////////////////////////////////////////////
		Vector2i getSize() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the wrap mode of the texture.
		///
		/// The wrap mode refers to how the texture will be applied to
		/// the next mesh to render, whether the texture will clamp to the
		/// edges of the mesh, or if the texture will repeat.
		///
		/// @returns The wrap mode of the texture.
		///
		////////////////////////////////////////////////////////////
		eWrapMode getWrapMode() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the filter applied to this texture.
		///
		/// The filtering controls the blending of the individual 
		/// pixels within the image. If the filtering is linear, it will
		/// smooth transitions between pixels. If the filtering is nearest,
		/// it will use pixel closest to the specified position.
		///
		/// @returns the filtering type applied to the Texture.
		///
		////////////////////////////////////////////////////////////
		eFilter getFilter() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates a new ID for the texture object.
		///
		/// When this method is invoked, it will create a new ID for the
		/// texture. This ID is used to refer to its specific behavior
		/// when rendering. Each ID assigned to a texture is unique.
		///
		////////////////////////////////////////////////////////////
		void create();

		////////////////////////////////////////////////////////////
		/// @brief Loads the data for a Texture object.
		///
		/// The data for a texture is commonly stored within a json file,
		/// when this method is invoked, it will parse the json and set
		/// the appropriate values and parameters.
		///
		/// @param filename  The file location of the json file.
		///
		/// @returns         True if the file successfully parsed and initialised.
		///
		////////////////////////////////////////////////////////////
		bool load(const std::string& filename) override;

		////////////////////////////////////////////////////////////
		/// @brief Binds a Texture object for use.
		///
		/// When a Texture object is bound, it will utilise the rendering
		/// behavior defined for the texture within the next rendering loop.
		///
		/// @param texture   The texture to bind.
		/// @param location  Which location to bind the texture to.
		///
		////////////////////////////////////////////////////////////
		static void bind(const Texture& texture, GLint location = 0);

		////////////////////////////////////////////////////////////
		/// @brief Unbinds the behavior of the Texture.
		///
		/// When a Texture object is unbound, the next rendering loop
		/// will no longer utilise the texture information contained within
		/// the currently bound object.
		///
		////////////////////////////////////////////////////////////
		static void unbind();
	};

} // namespace jackal

#endif//__JACKAL_TEXTURE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Texture
/// @ingroup rendering
///
/// The jackal::Texture class is a simple abstraction layer around
/// the functionality of creating and binding opengl textures. It
/// can be bound to objects and materials in order to achieve
/// specific rendering behavior.
///
/// Textures can also be loaded in from an external json file, as a
/// Texture inherits from a Resource. All its important parameters can
/// be set as data. Due to the internal use of textures, their functionality is
/// not exposed to the lua scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a new texture and load its data from a json file.
/// Texture texture;
/// texture.load("~textures/basic-texture.json");
///
/// // Bind the texture and use the image loaded in.
/// Texture::bind(texture);
/// // Render
/// Texture::unbind();
/// @endcode
///
////////////////////////////////////////////////////////////