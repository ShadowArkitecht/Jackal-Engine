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
#include <jackal/rendering/program.hpp> // Getting the unique ID of the Program.
#include <jackal/utils/json/json.hpp>   // Setting uniforms by a value in a json file.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Uniform::Uniform(Program& program)
		: m_program(program)
	{
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	GLint Uniform::getLocation(const std::string& uniform) const
	{
		return glGetUniformLocation(m_program.getID(), uniform.c_str());
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
	void Uniform::setParameter(const Json::Value& uniform)
	{
		Json::Value type = uniform["type"].asString();
		if (type == "vec3")
		{
			Json::Value values = uniform["values"];
			Vector3f vec3 = Vector3f(values["x"].asFloat(), values["y"].asFloat(), values["z"].asFloat());

			this->setParameter(uniform["name"].asString(), vec3);
		}
	}

} // namespace jackal