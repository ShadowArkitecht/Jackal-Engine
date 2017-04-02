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
// Structs
//====================
struct Material 
{
	sampler2D diffuse_texture; ///< The diffuse texture of the material.
	vec4 diffuse_colour;       ///< The colouring applied to the diffuse texture.
};

//====================
// Uniform variables
//====================
uniform Material u_material; ///< The Material object passed from the C++ code.

//====================
// Layout variables
//====================
in VS_OUT
{
	vec2 uv_coords;

} fs_in;

out vec4 frag_colour; ///< The final colour of the fragment.

//====================
// Functions
//====================
void main()
{
	vec4 diffuse_texture = texture2D(u_material.diffuse_texture, fs_in.uv_coords);
	vec3 diffuse = diffuse_texture.rgb * u_material.diffuse_colour.rgb;

	frag_colour = vec4(diffuse, 1.0); 
}