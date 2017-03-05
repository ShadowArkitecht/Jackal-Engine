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