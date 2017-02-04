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
#include <jackal/rendering/program.hpp> // Program class declaration.
#include <jackal/utils/log.hpp>         // Logging warnings and errors.

namespace jackal
{	
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt"); // Log warnings and errors.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Program::Program()
		: m_ID(), m_shaders(), m_compiled(false)
	{
	}

	////////////////////////////////////////////////////////////
	Program::~Program()
	{
		this->destroy();
	}	

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GLuint Program::getID() const
	{
		return m_ID;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Program::create()
	{
		m_ID = glCreateProgram();
	}

	////////////////////////////////////////////////////////////
	void Program::destroy()
	{
		if (m_ID)
		{
			glDeleteProgram(m_ID);
		}
	}

	////////////////////////////////////////////////////////////
	void Program::attachShader(const std::string& filename, eShaderType type)
	{
		GLSLObject object;
		// Check the object created and parsed successfully before adding it to the shader list.
		if (object.create(filename, type))
		{
			m_shaders.push_back(object);
		}
		else
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to attach.");
		}
	}

	////////////////////////////////////////////////////////////
	bool Program::compile()
	{
		if (!m_compiled)
		{
			for (auto& shader : m_shaders)
			{
				if (!shader.isCompiled())
				{
					shader.compile();
				}
				glAttachShader(m_ID, shader.getID());
			}

			// Link the shaders and check the link state.
			glLinkProgram(m_ID);

			GLint linked;
			glGetProgramiv(m_ID, GL_LINK_STATUS, &linked);

			if (linked != GL_TRUE)
			{
				GLint logLength;
				glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);

				std::vector<char> errorLog(logLength);
				glGetProgramInfoLog(m_ID, logLength, &logLength, &errorLog[0]);

				log.error(log.function(__FUNCTION__), "Failed:", &errorLog[0]);
				this->destroy();

				m_shaders.clear();
				return false;
			}

			for (auto& shader : m_shaders)
			{
				glDetachShader(m_ID, shader.getID());
			}

			log.debug(log.function(__FUNCTION__), "Linked successfully.");
			m_compiled = true;

			return true;
		}

		log.warning(log.function(__FUNCTION__), "Already compiled.");
		return true;
	}

	////////////////////////////////////////////////////////////
	void Program::bind(const Program& program)
	{
		glUseProgram(program.getID());
	}

	////////////////////////////////////////////////////////////
	void Program::unbind()	
	{
		glUseProgram(0);
	}

} // namespace jackal 