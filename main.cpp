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
#define NOMINMAX         // An error is caused in luabind if this is not defined (undefs min and max macros).

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
#include <jackal/scripting/scripting_manager.hpp>
#include <jackal/scripting/script.hpp>

using namespace jackal;

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

	Mesh mesh;
	mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f, 1.0f), Vector2f::zero()));
	mesh.addVertex(Vertex_t(Vector3f( 0.5f, -0.5f, 1.0f), Vector2f(1.0f, 0.0f)));
	mesh.addVertex(Vertex_t(Vector3f( 0.5f,  0.5f, 1.0f), Vector2f(1.0f, 1.0f)));
	mesh.addVertex(Vertex_t(Vector3f(-0.5f,  0.5f, 1.0f), Vector2f(0.0f, 1.0f)));
	
	// Add the indices.
	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(0);
	mesh.addIndex(2);
	mesh.addIndex(3);

	mesh.create();

	auto material = ResourceManager::getInstance().get<Material>("~assets/materials/basic-material.json");
	ScriptingManager::getInstance().bind();

	Script script("test_class.lua");
	script.create();

	while (window.isRunning())
	{
		window.clear();

		Material::bind(*material.get());

		material->process();

		mesh.render();

		Material::unbind();
		window.swap();

		window.pollEvents();

		ResourceManager::getInstance().reload();
	}

	SDL_Quit();

	return 0;
}