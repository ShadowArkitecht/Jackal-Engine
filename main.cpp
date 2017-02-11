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

#define SDL_MAIN_HANDLED // Handle main for SDL, otherwise it will cause issues with Assimp.

//====================
// Jackal includes
//====================
#include <jackal/core/virtual_file_system.hpp> // Register the common virtual paths.
#include <jackal/core/config_file.hpp>         // Load the main configuration file. 
#include <jackal/utils/properties.hpp>         // Load the locale for the current application.
#include <jackal/core/window.hpp>              // Creating test window instance.
#include <jackal/rendering/buffer.hpp>         // Binding different buffers.
#include <jackal/rendering/vertex.hpp>         // Creating vertices for the buffers.
#include <jackal/utils/resource_manager.hpp>   // Retrieve a shader object. 

#include <jackal/rendering/gui_texture.hpp>
#include <jackal/rendering/gui_texture_factory.hpp>

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

using namespace jackal;
using namespace Awesomium;

int main(int argc, char** argv)
{
	SDL_SetMainReady();

	auto& vfs = VirtualFileSystem::getInstance();
	// utils
	vfs.mount("locale", "data/locale");
	vfs.mount("config", "data/config");
	vfs.mount("csv", "data/csv");
	// rendering
	vfs.mount("shaders", "data/shaders");
	vfs.mount("textures", "data/textures");

	ConfigFile config;
	config.open("~config/main.jcfg");

	Properties properties;
	properties.open("~locale/", config);
	
	Window window;
	window.create(config);

	Shader shader = ResourceManager::getInstance().get<Shader>("assets/shaders/basic-shader.json");	
	Buffer vao(eBufferType::ARRAY);
	vao.create();

	Buffer::bind(vao);

	Buffer vbo(eBufferType::VERTEX);
	vbo.create();

	Vertex_t v1; v1.position = Vector3f(-0.5f, -0.5f, 1.0f);
	v1.uv = Vector2f::zero();

	Vertex_t v2; v2.position = Vector3f( 0.5f, -0.5f, 1.0f);
	v2.uv = Vector2f(1.0f, 0.0f);

	Vertex_t v3; v3.position = Vector3f( 0.5f,  0.5f, 1.0f);
	v3.uv = Vector2f(1.0f, 1.0f);

	Vertex_t v4; v4.position = Vector3f(-0.5f,  0.5f, 1.0f);
	v4.uv = Vector2f(0.0f, 1.0f);

	std::vector<Vertex_t> verts;
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	verts.push_back(v4);
	
	Buffer::bind(vbo);
	vbo.allocate(verts.data(), verts.size());

	Buffer ibo(eBufferType::INDEX);
	ibo.create();

	std::vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	Buffer::bind(ibo);
	ibo.allocate(indices.data(), indices.size());

	Buffer::unbind(vao);

	Texture texture = ResourceManager::getInstance().get<Texture>("assets/textures/basic-texture.json");
	
	// Test Awesomium initialization.
	WebCore* pCore = WebCore::Initialize(WebConfig());
	WebView* pView = pCore->CreateWebView(300, 300);

	pCore->set_surface_factory(new GUITextureFactory());

	WebURL url(WSLit("file:///C:/Users/Benjamin/Documents/ui/index.html"));
	pView->LoadURL(url);
	
	while (pView->IsLoading())
	{
	 	pCore->Update();
	}
	
	GUITexture* pTexture = (GUITexture*)pView->surface();

	while (window.isRunning())
	{
		pCore->Update();

		window.clear();

		Shader::bind(shader);
		// Texture::bind(texture);
		GUITexture::bind(*pTexture);

		shader.process();

		Buffer::bind(vao);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
		Buffer::unbind(vao);

		//Texture::unbind();
		GUITexture::unbind();
		
		Shader::unbind();

		window.swap();

		window.pollEvents();

		ResourceManager::getInstance().reload();
	}

	SDL_Quit();

	pView->Destroy();
	Awesomium::WebCore::Shutdown();

	return 0;
}