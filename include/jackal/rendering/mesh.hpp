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

#ifndef __JACKAL_MESH_HPP__
#define __JACKAL_MESH_HPP__

//====================
// Jackal includes
//====================
#include <jackal/rendering/irenderable.hpp> // Mesh is a renderable object.

namespace jackal
{
	class Mesh : public IRenderable
	{
	public:
		//====================
		// Jackal includes
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Mesh object.
		///
		/// The default constructor will call the parent IRenderable object
		/// constructor and sets the buffers to default values.
		///
		////////////////////////////////////////////////////////////
		explicit Mesh();

		////////////////////////////////////////////////////////////
		/// @brief Constructor for the Mesh object.
		///
		/// This constructor for the Mesh object will allow the vertices
		/// and indices to be passed in upon object construction. The
		/// buffers will then be sub-sequently bound and ready for use.
		///
		/// @param vertices The vertices of the mesh.
		/// @param indices  The indices of the mesh.
		///
		////////////////////////////////////////////////////////////
		explicit Mesh(const std::vector<Vertex_t>& vertices, const std::vector<GLuint>& indices);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Mesh object.
		////////////////////////////////////////////////////////////
		~Mesh() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Renders the mesh to the OpenGL context.
		///
		/// The render method is the same as the default IRenderable
		/// render method. It will utilise the indices supplied to render
		/// the mesh to the context.
		///
		////////////////////////////////////////////////////////////
		void render() override;
	};

} // namespace jackal

#endif//__JACKAL_MESH_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Mesh
/// @ingroup rendering
///
/// The jackal::Mesh is a simple class that can be used to explicitly
/// defining renderable shapes within the application with explicit
/// vertices and indices. The Mesh class can be used for defining custom
/// shapes that convenience methods are not declared for.
///
/// The Mesh class is used commonly by the chunk generation methods
/// for creating procedurally generated terrain. Due to the open use
/// of the class, it is exposed to the lua scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a mesh class and define vertices
/// Mesh mesh;
/// mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f, 1.0f), Vector2f::zero()));
/// mesh.addVertex(Vertex_t(Vector3f( 0.5f, -0.5f, 1.0f), Vector2f(1.0f, 0.0f)));
/// mesh.addVertex(Vertex_t(Vector3f( 0.5f,  0.5f, 1.0f), Vector2f(1.0f, 1.0f)));
/// mesh.addVertex(Vertex_t(Vector3f(-0.5f,  0.5f, 1.0f), Vector2f(0.0f, 1.0f)));
///
/// // Add the indices.
/// mesh.addIndex(0);
/// mesh.addIndex(1);
/// mesh.addIndex(2);
/// mesh.addIndex(0);
/// mesh.addIndex(2);
/// mesh.addIndex(3);
///
/// // Create a mesh renderer to attach and render to an entity.
/// MeshRenderer* renderer = MeshRenderer::create(mesh);
///
/// // Create the entity
/// GameObject* go = GameObject::create();
/// go->addComponent(renderer);
///
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create a mesh class and define vertices
/// local mesh = Mesh()
/// mesh:addVertex(Vertex(Vector3(-0.5, -0.5, 1.0), Vector2::zero()))
/// mesh:addVertex(Vertex(Vector3( 0.5, -0.5, 1.0), Vector2(1.0, 0.0)))
/// mesh:addVertex(Vertex(Vector3( 0.5,  0.5, 1.0), Vector2(1.0, 1.0)))
/// mesh:addVertex(Vertex(Vector3(-0.5,  0.5, 1.0), Vector2(0.0, 1.0)))
///
/// -- Add the indices.
/// mesh:addIndex(0)
/// mesh:addIndex(1)
/// mesh:addIndex(2)
/// mesh:addIndex(0)
/// mesh:addIndex(2)
/// mesh:addIndex(3)
///
/// -- Create a mesh renderer to attach and render to an entity.
/// local renderer = MeshRenderer.create(mesh);
///
/// -- Create the entity
/// local go = GameObject.create();
/// go:addComponent(renderer);
///
/// @endcode
///
////////////////////////////////////////////////////////////