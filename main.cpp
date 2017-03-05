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
#include <jackal/core/camera.hpp>              // Creating the global camera.
#include <jackal/utils/resource_manager.hpp>   // Retrieve a shader object. 
#include <jackal/rendering/material.hpp>       // Binding and utilising a material.   
#include <jackal/rendering/model.hpp>

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
	// Raw files (glsl, images etc.).
	vfs.mount("data/shaders", "data/shaders");
	vfs.mount("data/textures", "data/textures");
	// JSON files.
	vfs.mount("assets/textures", "assets/textures");
	vfs.mount("assets/shaders", "assets/shaders");
	vfs.mount("assets/materials", "assets/materials");

	ConfigFile config;
	config.open("~config/main.jcfg");

	Properties properties;
	properties.open("~locale/", config);
	
	Window window;
	window.create(config);

	Camera camera;
	camera.create(config);

	auto model = ResourceManager::getInstance().get<Model>("data/models/box.obj");

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

	auto material = ResourceManager::getInstance().get<Material>("~assets/materials/basic-material.json");

	while (window.isRunning())
	{
		pCore->Update();

		window.clear();

		Material::bind(*material.get());

		material->process();

		model->render();

		Material::unbind();
		window.swap();

		window.pollEvents();

		ResourceManager::getInstance().reload();
	}

	SDL_Quit();

	pView->Destroy();
	Awesomium::WebCore::Shutdown();

	return 0;
}