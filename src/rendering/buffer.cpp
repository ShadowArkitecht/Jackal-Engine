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
// C++ includes
//====================
#include <cstddef>						 // Calculating memory offset of vertices.

//====================
// Jackal includes
//====================
#include <jackal/rendering/buffer.hpp>   // Buffer class declaration.
#include <jackal/rendering/vertex.hpp>   // Vertex_t size use.

namespace jackal
{
	//====================
	// Local variables
	//====================
	const GLvoid* POS_OFFSET = reinterpret_cast<const GLvoid*>(offsetof(Vertex_t, position));

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Buffer::Buffer()
		: m_ID(0), m_type(eBufferType::VERTEX)
	{
	}

	////////////////////////////////////////////////////////////
	Buffer::Buffer(eBufferType type)
		: m_ID(0), m_type(type)
	{
	}

	////////////////////////////////////////////////////////////
	Buffer::~Buffer()
	{
		this->destroy();
	}

	//====================
	// Operators
	//====================
	////////////////////////////////////////////////////////////
	bool Buffer::operator==(const Buffer& buffer) const
	{
		return m_ID == buffer.m_ID;
	}

	////////////////////////////////////////////////////////////
	bool Buffer::operator!=(const Buffer& buffer) const
	{
		return !(*this == buffer);
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GLuint Buffer::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	eBufferType Buffer::getType() const
	{
		return m_type;
	}

	////////////////////////////////////////////////////////////
	bool Buffer::isCreated() const
	{
		return m_ID != 0;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Buffer::create()
	{
		switch (m_type)
		{
		case eBufferType::VERTEX:
			glGenBuffers(1, &m_ID);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), 0);
			break;

		case eBufferType::INDEX:
			glGenBuffers(1, &m_ID);
			break;

		case eBufferType::ARRAY:
			glGenVertexArrays(1, &m_ID);
			break;
		}
	}

	////////////////////////////////////////////////////////////
	void Buffer::destroy()
	{
		if (m_ID)
		{
			if (m_type == eBufferType::VERTEX || m_type == eBufferType::INDEX)
			{
				glDisableVertexAttribArray(0);

				glDeleteBuffers(1, &m_ID);
				m_ID = 0;
			}
			else
			{
				glDeleteVertexArrays(1, &m_ID);
				m_ID = 0;
			}
		}
	}

	////////////////////////////////////////////////////////////
	void Buffer::allocate(const void* pData, int count)
	{
		// vertex arrays don't need info allocated.
		switch (m_type)
		{
		case eBufferType::VERTEX:
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_t) * count, pData, GL_STATIC_DRAW);
			break;

		case eBufferType::INDEX:
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, pData, GL_STATIC_DRAW);
			break;
		}
	}

	////////////////////////////////////////////////////////////
	void Buffer::bind(const Buffer& buffer)
	{
		switch (buffer.getType())
		{
		case eBufferType::VERTEX:
			glBindBuffer(GL_ARRAY_BUFFER, buffer.getID());
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), 0);
			break;

		case eBufferType::INDEX:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.getID());
			break;

		case eBufferType::ARRAY:
			glBindVertexArray(buffer.getID());
			break;
		}
	}

	////////////////////////////////////////////////////////////
	void Buffer::unbind(const Buffer& buffer)
	{
		switch (buffer.getType())
		{
		case eBufferType::VERTEX:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;

		case eBufferType::INDEX:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			break;

		case eBufferType::ARRAY:
			glBindVertexArray(0);
			break;
		}
	}
}