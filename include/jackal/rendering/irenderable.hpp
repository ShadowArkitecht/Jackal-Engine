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

#ifndef __JACKAL_IRENDERABLE_HPP__
#define __JACKAL_IRENDERABLE_HPP__

//====================
// C++ includes
//====================
#include <vector>                       // Storing vertices and indices in vectors.

//====================
// Jackal includes
//====================
#include <jackal/rendering/vertex.hpp> // Position, UV, and normals of individual vertices..
#include <jackal/rendering/buffer.hpp> // Loading and generating buffers for OpenGL.

namespace jackal
{
	class IRenderable
	{
	private:
		//====================
		// Member variables
		//====================
		Buffer                m_vao;        ///< The OpenGL vertex array buffer.
		Buffer                m_vbo;        ///< The OpenGL vertex buffer object.
		Buffer                m_ibo;        ///< The OpenGL index buffer object.

		std::vector<Vertex_t> m_vertices;   ///< Vertices of the renderable object.
		std::vector<GLuint>   m_indices;    ///< Indices of the renderable object.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the IRenderable object.
		///
		/// The default constructor create the different buffers that will be
		/// utilised by the renderable object.
		///
		////////////////////////////////////////////////////////////
		explicit IRenderable();
		
		////////////////////////////////////////////////////////////
		/// @brief Constructor for the IRenderable with explicit vertices and indices.
		///
		/// This constructor can be called to explicitly add vertices to a 
		/// renderable object which will automatically be bound to the 
		/// OpenGL buffers.
		///
		/// @param vertices   The vertices to add to the IRenderable object.
		/// @param indices    The indices to add to the IRenderable object.
		///
		////////////////////////////////////////////////////////////
		explicit IRenderable(const std::vector<Vertex_t>& vertices, const std::vector<GLuint>& indices);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the IRenderable object.
		////////////////////////////////////////////////////////////
		virtual ~IRenderable() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Adds an individual vertex to the renderable object.
		///
		/// Vertices can be individually added to a renderable object
		/// or they can be added in a batch, this method can be invoked to
		/// add a single vertex. A vertex is used to represent a position 
		/// in 3D space. It will contain information with position, uv
		/// and vertex normals.
		///
		/// @param vertex   The vertex to add to the IRenderable object.
		///
		////////////////////////////////////////////////////////////
		void addVertex(const Vertex_t& vertex);

		////////////////////////////////////////////////////////////
		/// @brief Adds a group of vertices to the renderable object.
		///
		/// Vertices can be individually added to a renderable object
		/// or they can be added in a batch, this method can be invoked to
		/// add a batch of vertices. A vertex is used to represent a position 
		/// in 3D space. It will contain information with position, uv
		/// and vertex normals.
		///
		/// @param vertices   The vertices to add to the IRenderable object.
		///
		////////////////////////////////////////////////////////////
		void addVertices(const std::vector<Vertex_t>& vertices);

		////////////////////////////////////////////////////////////
		/// @brief Adds an individual index to the renderable object.
		///
		/// Indices can be individually added to a renderable object 
		/// or they can be added in a batch. This method can be invoked to
		/// add a single index. An index refers to the array offset of a
		/// vertex, it is used for sending less information to the GPU when
		/// rendering a mesh.
		///
		/// @param index    The index to add to the IRenderable object.
		///
		////////////////////////////////////////////////////////////
		void addIndex(GLuint index);

		////////////////////////////////////////////////////////////
		/// @brief Adds a group of indices to the renderable object.
		///
		/// Indices can be individually added to a renderable object
		/// or they can be added in a batch, this method can be invoked to
		/// add a batch of indices. An index refers to the array offset of a
		/// vertex, it is used for sending less information to the GPU when
		/// rendering a mesh.
		///
		/// @param vertices   The indices to add to the IRenderable object.
		///
		////////////////////////////////////////////////////////////
		void addIndices(const std::vector<GLuint>& indices);

		////////////////////////////////////////////////////////////
		/// @brief Binds the IRenderable object, ready for rendering.
		///
		/// The bind method simply encapsulates all of the behaviour needed
		/// to bind the buffers and allocate their memory, once the IRenderable
		/// object is bound, it can utilised to render objects the context.
		///
		////////////////////////////////////////////////////////////
		void bind();

		////////////////////////////////////////////////////////////
		/// @brief Pure virtual method for rendering the IRenderable object.
		///
		/// As each renderable may differ in the rendering behaviour, the
		/// method is provided as an abstract method so that it can be over-written
		/// by subsequent child classes. By default if this method is invoked within
		/// a child class, it will render a mesh utilising the indices defined within
		/// the object.
		///
		////////////////////////////////////////////////////////////
		virtual void render() = 0;
	};

} // namespace jackal

#endif//__JACKAL_IRENDERABLE_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::IRenderable
/// @ingroup rendering
///
/// The jackal::IRenderable is a simple interface class that 
/// provides the basic functionality needed to render shapes
/// within the OpenGL context. All objects that will render
/// within the application, will either inherit or reference
/// this base class. As each object within the application may
/// have different rendering behaviour, the render method is of
/// pure virtual design. This class does not provide the functionality
/// for instance rendering meshes.
///
/// Due to the internal use of the class, its methods and properties
/// are not exposed to the lua scripting interface. Coding examples
/// are provided in its subsequent child classes.
///
////////////////////////////////////////////////////////////