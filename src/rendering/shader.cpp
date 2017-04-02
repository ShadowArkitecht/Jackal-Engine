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
#include <jackal/rendering/shader.hpp>            // Shader class declaration.
#include <jackal/utils/log.hpp>                   // Logging warnings and errors.
#include <jackal/utils/constants.hpp>             // Using the constant log location.
#include <jackal/utils/json_file_reader.hpp>      // Loading and parsing the json file.
#include <jackal/utils/ext/json.hpp>              // De-serializing a shader file.
#include <jackal/rendering/material.hpp>          // The material to render the shader with.
#include <jackal/core/camera.hpp>                 // Rendering from the position of the Camera.
#include <jackal/utils/resource_manager.hpp>      // Used for retrieving a shader from the resource manager.
#include <jackal/math/transform.hpp>              // Used to retrieve the position, rotation and scale of an object.
#include <jackal/rendering/directional_light.hpp> // Test DirectionalLight behavior.

//====================
// Additional includes
//====================
#include <SDL2/SDL.h>                             // Used to retrieve the ticks of the application.

namespace jackal
{	
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt"); // Logging warnings and errors.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Shader::Shader()
		: Resource(), m_program(), m_uniform(m_program)
	{
		m_program.create();
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GLuint Shader::getID() const
	{
		return m_program.getID();
	}
	
	////////////////////////////////////////////////////////////
	std::vector<GLSLObject>& Shader::getShaders()
	{
		return m_program.getShaders();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Shader::load(const std::string& filename) // override
	{
		JSONFileReader reader;
		if (reader.read(filename))
		{
			nlohmann::json root = reader.getRoot();
			nlohmann::json files = root["glsl-files"];
			
			for (const auto& file : files)
			{
				this->attachShader(file.get<std::string>());
			}

			this->compile();

			nlohmann::json uniforms = root["constant-uniforms"];
			if (!uniforms.empty())
			{
				Shader::bind(*this);

				for (const auto& uniform : uniforms)
				{
					m_uniform.setParameter(uniform);
				}

				Shader::unbind();
			}
		}
		else
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to find or parse json shader.");
			return false;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	ResourceHandle<Shader> Shader::find(const std::string& name)
	{
		return ResourceManager::getInstance().get<Shader>(name);
	}

	////////////////////////////////////////////////////////////
	void Shader::attachShader(const std::string& filename)
	{
		m_program.attachShader(filename);
	}

	////////////////////////////////////////////////////////////
	void Shader::attachShader(const std::string& filename, eShaderType type)
	{
		m_program.attachShader(filename, type);
	}

	////////////////////////////////////////////////////////////
	bool Shader::compile()
	{
		if (!m_program.compile())
		{
			log.error(log.function(__FUNCTION__), "Failed to compile.");
		}

		log.debug(log.function(__FUNCTION__), "Successfully compiled.");
		return true;
	}

	////////////////////////////////////////////////////////////
	bool Shader::recompile()
	{
		return m_program.recompile();
	}

	////////////////////////////////////////////////////////////
	void Shader::process(const Transform& transform, const Material& material)
	{
		if (material.isLightingEnabled())
		{
			m_uniform.setParameter(Uniforms::MODEL, transform.getTransformation());

			DirectionalLight light;
			light.setColour(Colour::white());
			light.setSpecularity(Colour(1.0f, 0.0f, 0.0f, 1.0f));
			light.setIntensity(1.5f);
			light.setDirection(Vector3f::forward());

			m_uniform.setParameter(Uniforms::DIRECTIONAL_LIGHT_COLOUR, light.getColour());
			m_uniform.setParameter(Uniforms::DIRECTIONAL_LIGHT_SPECULARITY, light.getSpecularity());
			m_uniform.setParameter(Uniforms::DIRECTIONAL_LIGHT_INTENSITY, light.getIntensity());
			m_uniform.setParameter(Uniforms::DIRECTIONAL_LIGHT_DIRECTION, light.getDirection());
		}

		m_uniform.setParameter(Uniforms::MATERIAL_DIFFUSE_TEXTURE, eTextureType::DIFFUSE);
		m_uniform.setParameter(Uniforms::MATERIAL_SPECULAR_TEXTURE, eTextureType::SPECULAR);
		m_uniform.setParameter(Uniforms::MATERIAL_DIFFUSE_COLOUR, material.getColour());
		m_uniform.setParameter(Uniforms::MATERIAL_SHININESS, material.getShininess());

		Matrix4 mvp = transform.getTransformation() * Camera::getMain().getViewProjection();

		m_uniform.setParameter(Uniforms::MODEL_VIEW_PERSPECTIVE, mvp);
	}

	////////////////////////////////////////////////////////////
	void Shader::bind(const Shader& shader)	
	{
		Program::bind(shader.m_program);
	}

	////////////////////////////////////////////////////////////
	void Shader::unbind()
	{
		Program::unbind();
	}

} // namespace jackal 