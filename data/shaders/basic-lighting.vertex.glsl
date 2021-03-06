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
// Uniforms
//====================
uniform mat4 u_mvp;
uniform mat4 u_model;

//====================
// Interfaces
//====================
out VS_OUT
{
	vec2 uv_coords;
	vec3 normals;
	vec3 frag_position;

} vs_out;

//====================
// Functions
//====================
void main()
{
	vs_out.uv_coords = uv;	 
	vs_out.normals = mat3(transpose(inverse(u_model))) * normal;
	vs_out.frag_position = vec3(u_model * vec4(position, 1.0));
	
	gl_Position = u_mvp * vec4(position, 1.0);
}