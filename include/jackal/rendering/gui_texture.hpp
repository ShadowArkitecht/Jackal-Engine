#ifndef __JACKAL_GUI_TEXTURE_HPP__
#define __JACKAL_GUI_TEXTURE_HPP__

#include <jackal/rendering/texture.hpp>
#include <GL/glew.h>
#include <Awesomium/Surface.h>

namespace jackal
{
	class GUITexture : public Texture, public Awesomium::Surface
	{
	private:
		unsigned char*  m_pBuffer;

	public:
		explicit GUITexture(const Vector2i& size);
		~GUITexture();

		void Paint(unsigned char* buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect& dest_rect) override;
		void Scroll(int dx, int dy, const Awesomium::Rect& clip_rect) override;

		static void bind(const GUITexture& texture);
		static void unbind();
	};

} // namespace jackal

#endif//__JACKAL_GUI_TEXTURE_HPP__