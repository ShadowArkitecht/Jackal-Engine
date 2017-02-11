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
#include <jackal/rendering/shader.hpp>       // Shader class declaration.
#include <jackal/utils/log.hpp>              // Logging warnings and errors.
#include <jackal/utils/json_file_reader.hpp> // Loading and parsing the json file.
#include <jackal/utils/json/json.hpp>        // De-serializing a shader file.

//====================
// Additional includes
//====================
#include <SDL2/SDL.h>                        // Used to retrieve the ticks of the application.

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
			Json::Value root = reader.getRoot();
			Json::Value files = root["glsl-files"];
			
			for (const auto& gf : files)
			{
				this->attachShader(gf["glsl-file"].asString());
			}

			this->compile();

			Shader::bind(*this);

			Json::Value uniforms = root["const-uniforms"];
			for (const auto& uniform : uniforms)
			{
				m_uniform.setParameter(uniform);
			}

			Shader::unbind();
		}
		else
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to find or parse json shader.");
			return false;
		}

		return true;
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
	void Shader::process()
	{
		m_uniform.setParameter("u_time", static_cast<float>(SDL_GetTicks()));
		m_uniform.setParameter("u_texture", 0);
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