#include <jackal/rendering/gui_texture.hpp>

using namespace Awesomium;

namespace jackal
{
	GUITexture::GUITexture(const Vector2i& size)
		: Texture(), Surface(), m_pBuffer(nullptr)
	{
		this->setSize(size);

		m_pBuffer = new unsigned char[this->getSize().x * this->getSize().y * 4];
		memset(m_pBuffer, 0, sizeof(unsigned char) * this->getSize().x * this->getSize().y * 4);
	}

	GUITexture::~GUITexture()
	{
		delete[] m_pBuffer;
	}

	void GUITexture::Paint(unsigned char* src_buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect& dest_rect)
	{
		int rowspan = this->getSize().x * 4;
		for (int row = 0; row < dest_rect.height; row++)
		{
			memcpy(m_pBuffer + (row + dest_rect.y) * rowspan + (dest_rect.x *4), 
				   src_buffer + (row + src_rect.y) * src_row_span + (src_rect.x * 4),
				   dest_rect.width * 4);
		}
	}

	void GUITexture::Scroll(int dx, int dy, const Awesomium::Rect& clip_rect)
	{
	}

	void GUITexture::bind(const GUITexture& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture.getID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, texture.m_pBuffer);
	}

	void GUITexture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} // namespace jackal