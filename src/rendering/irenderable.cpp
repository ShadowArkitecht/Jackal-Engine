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

//====================
// Jackal includes
//====================
#include <jackal/rendering/irenderable.hpp> // IRenderable class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	IRenderable::IRenderable()
		: m_vao(eBufferType::ARRAY), m_vbo(eBufferType::VERTEX), m_ibo(eBufferType::INDEX), m_vertices(), m_indices()
	{
	}

	////////////////////////////////////////////////////////////
	IRenderable::IRenderable(const std::vector<Vertex_t>& vertices, const std::vector<GLuint>& indices)
		: m_vao(eBufferType::ARRAY), m_vbo(eBufferType::VERTEX), m_ibo(eBufferType::INDEX), m_vertices(vertices), m_indices(indices)
	{
		this->create();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void IRenderable::addVertex(const Vertex_t& vertex)	
	{
		m_vertices.push_back(vertex);
	}

	////////////////////////////////////////////////////////////
	void IRenderable::addVertices(const std::vector<Vertex_t>& vertices)
	{
		m_vertices.insert(std::end(m_vertices), std::begin(vertices), std::end(vertices));
	}

	////////////////////////////////////////////////////////////
	void IRenderable::addIndex(GLuint index)
	{
		m_indices.push_back(index);
	}

	////////////////////////////////////////////////////////////
	void IRenderable::addIndices(const std::vector<GLuint>& indices)
	{
		m_indices.insert(std::end(m_indices), std::begin(indices), std::end(indices));
	}

	////////////////////////////////////////////////////////////
	void IRenderable::create()
	{
		m_vao.create();
		Buffer::bind(m_vao);

		m_vbo.create();
		Buffer::bind(m_vbo);

		m_vbo.allocate(m_vertices.data(), m_vertices.size());

		m_ibo.create();
		Buffer::bind(m_ibo);

		m_ibo.allocate(m_indices.data(), m_indices.size());

		Buffer::unbind(m_vao);
	}

	////////////////////////////////////////////////////////////
	void IRenderable::render() 
	{
		Buffer::bind(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
		Buffer::unbind(m_vao);
	}
	
} // namespace jackal