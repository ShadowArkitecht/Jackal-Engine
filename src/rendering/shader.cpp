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
#include <jackal/rendering/shader.hpp> // Shader class declaration.
#include <jackal/utils/log.hpp>        // Logging warnings and errors.

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
		: m_program(), m_uniform(m_program)
	{
		m_program.create();
	}

	//====================
	// Methods
	//====================
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
	void Shader::process()
	{
		//TODO(BEN): These are temporary to test uniform variables.
		// Replace them with the eventual material class.
		m_uniform.setParameter("basic_colour", Vector3f(1.0f, 0.0f, 0.0f));
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