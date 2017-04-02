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
	sampler2D diffuse;   ///< The diffuse texture of the material.
	sampler2D specular;  ///< The specularity texture of the material.
	vec4 diffuse_colour; ///< The colouring applied to the diffuse texture.
};

struct Light
{
	vec4 colour;     ///< The colour effect on the diffuse texture.
	float intensity; ///< The intensity of the light within the scene.
};

struct DirectionalLight
{
	Light light;    ///< Base light object.
	vec3 direction; ///< The direction of the DirectionalLight object.
};

//====================
// Functions
//====================
////////////////////////////////////////////////////////////
vec4 jackal_calculateLight(Light light, vec3 direction, vec3 world_normals);

////////////////////////////////////////////////////////////
vec4 jackal_calculateDirectionalLight(DirectionalLight dir_light, vec3 world_normals);

//====================
// Uniform variables
//====================
uniform Material u_material;          ///< The Material object passed from the C++ code.
uniform DirectionalLight u_dir_light; ///< The directional light passed from the C++ code.

//====================
// Layout variables
//====================
in VS_OUT
{
	vec2 uv_coords;
	vec3 normals;
	vec3 frag_position;

} fs_in;

out vec4 frag_colour; ///< The final colour of the fragment.

//====================
// Functions
//====================
////////////////////////////////////////////////////////////
void main()
{
	// Loading the textures.
	vec4 diffuse_texture  = texture2D(u_material.diffuse, fs_in.uv_coords);
	vec4 specular_texture = texture2D(u_material.specular, fs_in.uv_coords);

	// Calculate the effects on the object.
	vec4 diffuse = jackal_calculateDirectionalLight(u_dir_light, fs_in.normals) * diffuse_texture;

	frag_colour = diffuse; 
}

////////////////////////////////////////////////////////////
vec4 jackal_calculateLight(Light light, vec3 direction, vec3 world_normals)
{
	vec3 normal = normalize(world_normals);
	vec3 dir = normalize(-direction);

	float saturation = max(dot(normal, dir), 0.0);

	vec4 colour = vec4(0.0);
	if (saturation > 0.0) 
	{
		colour = light.colour * light.intensity * saturation;
	}

	return vec4(colour.rgb, 1.0);
}

////////////////////////////////////////////////////////////
vec4 jackal_calculateDirectionalLight(DirectionalLight dir_light, vec3 world_normals)
{
	return jackal_calculateLight(dir_light.light, dir_light.direction, world_normals);
}