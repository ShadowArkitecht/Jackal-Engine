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
	float shininess;     ///< How shiny the specular effects will be on this material.
};

struct Light
{
	vec4 colour;      ///< The colour effect on the diffuse texture.
	vec4 specularity; ///< The specular effect of the light.
	float intensity;  ///< The intensity of the light within the scene.
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
/// @brief Calculates the effect of a light on a given pixel. 
///
/// When this function is invoked, it will utilises the parameters
/// defined within a light, such as its' colour and intensity to 
/// manipulate the fragment colour to give the appearance of 
/// lighting. This method is invoked by point, spot and directional
/// lights.
///
/// @param light          The light to retrieve the colour and intensity from.
/// @param direction      The direction the light is currently shining in.
/// @param world_normals  The normal of the vertex, in world co-ordinates.
///
/// @returns The effect and colouring of a light on a pixel.
///
////////////////////////////////////////////////////////////
vec4 jackal_calculate_light(Light light, vec3 direction, vec3 world_normals);

////////////////////////////////////////////////////////////
/// @brief Calculates the effect of a directional light on a given pixel.
///
/// When this function is invoked, it will use the variables
/// within the directional light to calculate the effect that it will have
/// upon each pixel within the fragment shader. This function is used to 
/// represent a steady stream of light, such as the sun.
///
/// @param dir_light     The directional light to retrieve the variables from.
/// @param world_normals The normal of the vertex, in world co-ordinates.
///
/// @returns The effect of a directional light on a given pixel.
///
////////////////////////////////////////////////////////////
vec4 jackal_calculate_directional_light(DirectionalLight dir_light, vec3 world_normals);

////////////////////////////////////////////////////////////
/// @brief Calculates the effect of the specularity map on a given pixel.
///
/// The specularity revolves around the reflection of lights upon a
/// pixel, it utilises the specular texture supplied by the Material
/// uniform to calculate whether any pixels should be reflecting light
/// sources.
///
/// @param material       The Material containing the specular texture.
/// @param dir_light      The direction of the light on the specular texture.
/// @param view_position  The position of the camera within the scene.
/// @param frag_position  The position in model co-ordinates.
/// @param world_normals  The normal of the vertex, in world co-ordinates.
///
/// @returns The effect of the specularity on a given pixel.
///
////////////////////////////////////////////////////////////
vec4 jackal_calculate_specularity(Material material, DirectionalLight dir_light, vec3 view_position, vec3 frag_position, vec3 world_normals);

//====================
// Uniform variables
//====================
uniform Material u_material;          ///< The Material object passed from the C++ code.
uniform DirectionalLight u_dir_light; ///< The directional light passed from the C++ code.
uniform vec3 u_view_position;         ///< The current view direction of the camera.

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
	vec4 diffuse = jackal_calculate_directional_light(u_dir_light, fs_in.normals) * diffuse_texture;
	vec4 specular = jackal_calculate_specularity(u_material, u_dir_light, u_view_position, fs_in.frag_position, fs_in.normals) * specular_texture;

	frag_colour = diffuse + specular; 
}

////////////////////////////////////////////////////////////
vec4 jackal_calculate_light(Light light, vec3 direction, vec3 world_normals)
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
vec4 jackal_calculate_directional_light(DirectionalLight dir_light, vec3 world_normals)
{
	return jackal_calculate_light(dir_light.light, dir_light.direction, world_normals);
}

////////////////////////////////////////////////////////////
vec4 jackal_calculate_specularity(Material material, DirectionalLight dir_light, vec3 view_position, vec3 frag_position, vec3 world_normals)
{
	vec3 normals = normalize(world_normals);

	vec3 view_direction = normalize(view_position - frag_position);
	vec3 reflect_direction = reflect(-dir_light.direction, normals);

	float specularity = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	
	vec4 result = dir_light.light.specularity * specularity;
	return vec4(result.rgb, 1.0);
}
