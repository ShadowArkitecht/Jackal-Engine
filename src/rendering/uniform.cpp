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
#include <jackal/rendering/uniform.hpp> // Uniform class declaration.
#include <jackal/utils/log.hpp>         // Logging any json parsing errors.
#include <jackal/rendering/program.hpp> // Getting the unique ID of the Program.
#include <jackal/utils/ext/json.hpp>    // Setting uniforms by a value in a json file.

namespace jackal
{
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt"); // Logging warnings and errors.

	const std::string Uniforms::MODEL_VIEW_PERSPECTIVE = "u_mvp";
	const std::string Uniforms::MODEL                  = "u_model";
	// Material
	const std::string Uniforms::MATERIAL_DIFFUSE_TEXTURE  = "u_material.diffuse";
	const std::string Uniforms::MATERIAL_SPECULAR_TEXTURE = "u_material.specular";
	const std::string Uniforms::MATERIAL_DIFFUSE_COLOUR   = "u_material.diffuse_colour";
	const std::string Uniforms::MATERIAL_SHININESS        = "u_material.shininess";
	// DirectionalLight
	const std::string Uniforms::DIRECTIONAL_LIGHT_COLOUR      = "u_dir_light.light.colour";
	const std::string Uniforms::DIRECTIONAL_LIGHT_SPECULARITY = "u_dir_light.light.specularity";
	const std::string Uniforms::DIRECTIONAL_LIGHT_INTENSITY   = "u_dir_light.light.intensity";
	const std::string Uniforms::DIRECTIONAL_LIGHT_DIRECTION   = "u_dir_light.direction";

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Uniform::Uniform(Program& program)
		: m_pProgram(&program)
	{
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	GLint Uniform::getLocation(const std::string& uniform) const
	{
		return glGetUniformLocation(m_pProgram->getID(), uniform.c_str());
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, int variable) const
	{
		glUniform1i(location, variable);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, float variable) const
	{
		glUniform1f(location, variable);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, double variable) const
	{
		glUniform1d(location, variable);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector2i& vector) const
	{
		glUniform2i(location, vector.x, vector.y);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector2f& vector) const
	{
		glUniform2f(location, vector.x, vector.y);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector2d& vector) const
	{
		glUniform2d(location, vector.x, vector.y);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector3i& vector) const
	{
		glUniform3i(location, vector.x, vector.y, vector.z);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector3f& vector) const
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector3d& vector) const
	{
		glUniform3d(location, vector.x, vector.y, vector.z);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector4i& vector) const
	{
		glUniform4i(location, vector.x, vector.y, vector.z, vector.w);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector4f& vector) const
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Vector4d& vector) const
	{
		glUniform4d(location, vector.x, vector.y, vector.z, vector.w);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Colour& colour) const
	{
		glUniform4f(location, colour.r, colour.g, colour.b, colour.a);
	}

	////////////////////////////////////////////////////////////
	void Uniform::set(GLint location, const Matrix4& matrix) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.m[0][0]);
	}
	
	////////////////////////////////////////////////////////////
	void Uniform::setParameter(const nlohmann::json& uniform)
	{
		std::string type = uniform["type"].get<std::string>();
		nlohmann::json values = uniform["values"];

		if (type.substr(0, 4) == "vec2") // The uniform is a type of vec2
		{
			if (type.length() == 4)
			{
				this->setParameter(uniform["name"].get<std::string>(), values.get<Vector2f>());
			}
			else if (type.length() == 5)
			{
				switch (type[5])
				{
				case 'i':
					this->setParameter(uniform["name"].get<std::string>(), values.get<Vector2i>());
					break;					

				case 'd':
					this->setParameter(uniform["name"].get<std::string>(), values.get<Vector2d>());
					break;					
				}
			}
			else
			{
				log.warning(log.function(__FUNCTION__, uniform["name"].get<std::string>()), "Failed to parse vec2 value.");
				return;
			}
		}
	}

} // namespace jackal