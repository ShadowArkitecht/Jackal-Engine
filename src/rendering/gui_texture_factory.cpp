#include <jackal/rendering/gui_texture_factory.hpp>
#include <jackal/rendering/gui_texture.hpp>

using namespace Awesomium;

namespace jackal
{
	GUITextureFactory::GUITextureFactory()
		: SurfaceFactory()
	{
	}

	Surface* GUITextureFactory::CreateSurface(WebView* pView, int width, int height)
	{
		return new GUITexture(Vector2i(width, height)); 
	} 

	void GUITextureFactory::DestroySurface(Surface* pSurface)
	{
		if (pSurface)
		{
			delete pSurface;
			pSurface = nullptr;
		}
	}
	
} // namespace jackal