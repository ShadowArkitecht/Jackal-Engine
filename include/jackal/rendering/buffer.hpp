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

#ifndef __JACKAL_BUFFER_HPP__
#define __JACKAL_BUFFER_HPP__

//====================
// Additional includes
//====================
#include <GL/glew.h>  // OpenGL functionality.

namespace jackal
{
	//====================
	// Enumerations
	//====================
	enum class eBufferType
	{
		VERTEX,
		INDEX,
		ARRAY
	};

	class Buffer 
	{
	private:
		//====================
		// Member variables
		//====================
		GLuint      m_ID;   ///< Unique identifier for the buffer object.
		eBufferType m_type; ///< The type of buffer being bound and populated.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Buffer object.
		///
		/// The default constructor sets all of the member variables to
		/// default values. The default type for a buffer is of type eBufferType::VERTEX.
		///
		////////////////////////////////////////////////////////////
		explicit Buffer();

		////////////////////////////////////////////////////////////
		/// @brief Constructor for the Buffer object.
		///
		/// This constructor is used to implicitly set the type of the
		/// of the type of Buffer that can be created and bound. 
		///
		/// @param type   The type of the Buffer to create and bind.
		///
		////////////////////////////////////////////////////////////
		explicit Buffer(eBufferType type);

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the Buffer object. 
		///
		/// The destructor implicitly calls the destroy method, which 
		/// de-allocates the buffer ID assigned to the Buffer object.
		///
		////////////////////////////////////////////////////////////
		~Buffer();

		//====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Checks for equality between two Buffer objects.
		/// 
		/// Buffer equality is determined by comparing the unique ID's 
		/// of the Buffer objects. If the ID's are equal (somehow), they
		/// are equal.
		///
		/// @param buffer    The Buffer object to compare against.
		///
		/// @returns         True if the objects are equal.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Buffer& buffer) const;

		////////////////////////////////////////////////////////////
		/// @brief Checks for non-equality between two Buffer objects.
		/// 
		/// Buffer equality is determined by comparing the unique ID's 
		/// of the Buffer objects. If the ID's are equal (somehow), they
		/// are equal.
		///
		/// @param buffer    The Buffer object to compare against.
		///
		/// @returns         True if the objects are not equal.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Buffer& buffer) const;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Returns the unique ID of the Buffer object.
		///
		/// The ID refers to the value that is assigned to the ID when
		/// it is first bound. If the object has not been bound, the ID
		/// will be equal to 0.
		///
		/// @returns  The ID of the Buffer object.
		///
		////////////////////////////////////////////////////////////
		GLuint getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the type of buffer.
		///
		/// The buffer type refers to the method in which the Buffer object
		/// will be using for creation and binding. The buffer type controls 
		/// the behavior when creating and binding.
		///
		/// @returns The type of the Buffer object.
		///
		////////////////////////////////////////////////////////////
		eBufferType getType() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves whether the current Buffer has been created.
		///
		/// Checks whether the current Buffer has been created, the creation
		/// is determined by checking the value of the ID, if the ID is equal to
		/// 0, the Buffer has not yet been created.
		///
		/// @returns The created state of the Buffer.
		///
		////////////////////////////////////////////////////////////
		bool isCreated() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates a new Buffer object.
		///
		/// When this method is invoked, it will create a new buffer ID
		/// depending on the specified flag set. Before any functionality
		/// of the Buffer can be used, create must be called to not result
		/// in un-wanted behavior.
		///
		////////////////////////////////////////////////////////////
		void create();

		////////////////////////////////////////////////////////////
		/// @brief Destroys the ID of the Buffer.
		///
		/// When the destroy method is invoked, it will delete the 
		/// memory allocated on the GPU for rendering and set the ID back
		/// to a default state. If any of the behavior for the Buffer is needed
		/// after this method is called, create must be called once more.
		///
		////////////////////////////////////////////////////////////
		void destroy();

		////////////////////////////////////////////////////////////
		/// @brief Allocates data to the Buffer.
		///
		/// In order for the buffer to render or process information correctly,
		/// the data and size of the data in question must be allocated for the
		/// correct behavior. It should be noted that Buffer objects assigned to
		/// the flag eBufferType::ARRAY do not need to be allocated.
		///
		/// @param pData  The raw data to bind to the Buffer.
		/// @param count  The amount of data to bind.
		///
		////////////////////////////////////////////////////////////
		void allocate(const void* pData, int count);

		////////////////////////////////////////////////////////////
		/// @brief Binds a Buffer object for use.
		///
		/// A buffer must be bound in order for the rendering capabilities
		/// to render correctly. Commonly only buffers that are assigned the
		/// flag eBufferType::ARRAY will need to be constantly bound each
		/// frame.
		///
		////////////////////////////////////////////////////////////
		static void bind(const Buffer& buffer);

		////////////////////////////////////////////////////////////
		/// @brief Unbinds a Buffers object.
		///
		/// At the end of each iteration or use, the buffers should be unbound
		/// so that it does not effect other objects or processes outside the
		/// Buffer objects scope. 
		///
		////////////////////////////////////////////////////////////
		static void unbind(const Buffer& buffer);
	};

} // namespace jackal

#endif//__JACKAL_BUFFER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Buffer
/// @ingroup rendering 
///
/// The jackal::Buffer object is the primary class that is used
/// bind the rendering behavior of different meshes and game objects.
/// The Buffer class is a basic abstraction class over OpenGL behavior,
/// to make it easier to manipulate states and different Buffer binding types.
///
/// The Buffer object can be used to bind behaviors of different types:
/// vertices, indices and vertex arrays. Due to the low level aspects of the
/// class, it is not exposed to the lua scripting interface.
///
/// @code
/// using namespace jackal;
///
/// // Create a new buffer object of type vertex.
/// Buffer vbo(eBufferType::VERTEX);
/// vbo.create();
///
/// // Binds the information of a vertex vector container.
/// vbo.allocate(vertices.data(), vertices.size());
///
/// // Bind the Buffer object and render a mesh.
/// vbo.bind();
/// // Render the mesh.
/// vbo.unbind(); 
/// @endcode
///
////////////////////////////////////////////////////////////