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
#include <jackal/core/virtual_file_system.hpp>    // Register the common virtual paths.
#include <jackal/core/config_file.hpp>            // Load the main configuration file. 
#include <jackal/utils/properties.hpp>            // Load the locale for the current application.
#include <jackal/core/window.hpp>                 // Creating test window instance.
#include <jackal/core/camera.hpp>                 // Creating the global camera.
#include <jackal/utils/resource_manager.hpp>      // Retrieve a shader object. 
#include <jackal/rendering/material.hpp>          // Binding and utilising a material.   
#include <jackal/scripting/scripting_manager.hpp>
#include <jackal/scripting/scriptable.hpp>

#include <jackal/rendering/model.hpp>

using namespace jackal;

int main(int argc, char** argv)
{
	auto& vfs = VirtualFileSystem::getInstance();
	// utils
	vfs.mount("locale", "data/locale");
	vfs.mount("config", "data/config");
	vfs.mount("csv", "data/csv");
	// Raw files (glsl, images etc.).
	vfs.mount("data/shaders", "data/shaders");
	vfs.mount("data/textures", "data/textures");
	vfs.mount("data/models", "models");
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
	// Back.
	mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f( 0.0f,  0.0f, -1.0f),  Vector2f(0.0f,  0.0f)));
    mesh.addVertex(Vertex_t(Vector3f( 0.5f, -0.5f, -0.5f), Vector3f( 0.0f,  0.0f, -1.0f),  Vector2f(1.0f,  0.0f)));
    mesh.addVertex(Vertex_t(Vector3f( 0.5f,  0.5f, -0.5f), Vector3f( 0.0f,  0.0f, -1.0f),  Vector2f(1.0f,  1.0f)));
    mesh.addVertex(Vertex_t(Vector3f(-0.5f,  0.5f, -0.5f), Vector3f( 0.0f,  0.0f, -1.0f),  Vector2f(0.0f,  1.0f)));
	// Front.
	mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 0.0f)));
	mesh.addVertex(Vertex_t(Vector3f( 0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 0.0f)));
	mesh.addVertex(Vertex_t(Vector3f( 0.5f, 0.5f, -0.5f),  Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f)));
	mesh.addVertex(Vertex_t(Vector3f(-0.5f, 0.5f, -0.5f),  Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 1.0f)));
	// Left.
    mesh.addVertex(Vertex_t(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  0.0f)));
    mesh.addVertex(Vertex_t(Vector3f(-0.5f,  0.5f, -0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  1.0f)));
    mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(0.0f,  1.0f)));
    mesh.addVertex(Vertex_t(Vector3f(-0.5f, -0.5f,  0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  0.0f)));
	// Right
	mesh.addVertex(Vertex_t(Vector3f(0.5f,  0.5f,  0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  0.0f)));
    mesh.addVertex(Vertex_t(Vector3f(0.5f,  0.5f, -0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  1.0f)));
    mesh.addVertex(Vertex_t(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(0.0f,  1.0f)));
    mesh.addVertex(Vertex_t(Vector3f(0.5f, -0.5f,  0.5f), Vector3f(-1.0f,  0.0f,  0.0f),  Vector2f(1.0f,  0.0f)));

	for (int i = 0; i < 2; i++)
	{
		int offset = i * 6;
		mesh.addIndex(0 + offset);
		mesh.addIndex(1 + offset);
		mesh.addIndex(2 + offset);
		mesh.addIndex(0 + offset);
		mesh.addIndex(2 + offset);
		mesh.addIndex(3 + offset);
	}

	mesh.create();

	auto model = Model::find("data/models/box.obj");
	auto material = Material::find("~assets/materials/basic-lighting-material.json");
	
	ScriptingManager::getInstance().bind();

	Transform t1;

	Scriptable* s = Scriptable::create("test_class.lua");
	s->onCreate();

	delete s;

	Camera::getMain().getTransform().setPosition(0.0f, 0.0f, -2.0f);

	while (window.isRunning())
	{
		window.clear();

		Material::bind(*material.get());

		material->process(t1);
		mesh.render();

		Material::unbind();
		window.swap();

		window.pollEvents();

		ResourceManager::getInstance().reload();
	}

	ResourceManager::getInstance().destroy();
	SDL_Quit();

	return 0;
}