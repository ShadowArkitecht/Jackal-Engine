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

#version 330 core

//====================
// Layout variables
//====================
layout (location = 0) in vec3 position; // The world position of the vertices. 
layout (location = 1) in vec3 normal;   // Vertex normals of the mesh.
layout (location = 2) in vec2 uv;       // UV co-ordinate of the mesh.

//====================
// Interfaces
//====================
out vec2 uv_coords;

//====================
// Functions
//====================
void main()
{
	uv_coords = vec2(uv.x, 1.0 - uv.y);	
	gl_Position = vec4(position, 1.0);
}