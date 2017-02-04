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
#include <jackal/rendering/glsl_object.hpp> // GLSL object class declaration.
#include <jackal/utils/log.hpp>             // Logging warnings and errors.
#include <jackal/utils/file_reader.hpp>     // Reading in the external file.
#include <jackal/utils/file_system.hpp>     // Checking the file extensions.
#include <jackal/utils/constants.hpp>       // Comparing against the file extensions.

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
	GLSLObject::GLSLObject()
		: m_ID(0), m_type(0), m_compiled(false)
	{
	}

	////////////////////////////////////////////////////////////
	GLSLObject::~GLSLObject()
	{
		this->destroy();
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GLuint GLSLObject::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	bool GLSLObject::isCompiled() const
	{
		return m_compiled;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool GLSLObject::parse(const std::string& filename)
	{
		FileReader reader;
		if (!reader.read(filename))
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to read shader.");
			return false;
		}

		for (auto line : reader.getLines())
		{
			m_source.append(line + '\n');
		}

		log.debug(log.function(__FUNCTION__, filename), "Parsed successfully.");
		return true;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool GLSLObject::create(const std::string& filename, eShaderType type)
	{
		FileSystem system;

		switch (type)
		{
		case eShaderType::VERTEX:
			m_type = GL_VERTEX_SHADER;
			if (!system.hasExtensions(filename, Constants::Extensions::VERTEX_SHADER, 2))
			{
				log.warning(log.function(__FUNCTION__, filename), "Incorrect file extension. Extension should be:", 
					Constants::Extensions::VERTEX_SHADER);

				return false;
			}
			break;

		case eShaderType::FRAGMENT:
			m_type = GL_FRAGMENT_SHADER;
			if (!system.hasExtensions(filename, Constants::Extensions::FRAGMENT_SHADER, 2))
			{
				log.warning(log.function(__FUNCTION__, filename), "Incorrect file extension. Extension should be:", 
					Constants::Extensions::FRAGMENT_SHADER);

				return false;
			}
			break;
		}

		if (!this->parse(filename))
		{
			return false;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	void GLSLObject::destroy()
	{
		if (m_ID)
		{
			glDeleteShader(m_ID);
			m_ID = 0;
		}
	}

	////////////////////////////////////////////////////////////
	void GLSLObject::compile()
	{
		// Create an ID with the defined type.
		GLuint ID = glCreateShader(m_type);
		// Get the source and pass it as the source for the shader.
		const GLchar* pSource = m_source.c_str();
		glShaderSource(ID, 1, (const GLchar**)&pSource, nullptr);
		// Compile the shader.
		glCompileShader(ID);
		// Get the result of the compilation.
		GLint status;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &status);
		// Shader compilation failed.
		if (status != GL_TRUE)
		{
			GLint logSize = 0;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
			// Get and log the error.
			std::vector<GLchar> errorLog(logSize);
			glGetShaderInfoLog(ID, logSize, &logSize, &errorLog[0]);

			glDeleteShader(ID);
			log.error(log.function(__FUNCTION__), "Failed to compile:", &errorLog[0]);
		}
		else
		{	
			m_ID = ID;
			m_compiled = true;
			
			log.debug(log.function(__FUNCTION__), "Compiled successfully.");
		}

		m_source.clear();
	}

} // namespace jackal 