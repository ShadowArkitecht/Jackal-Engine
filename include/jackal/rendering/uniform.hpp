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

#ifndef __JACKAL_UNIFORM_HPP__
#define __JACKAL_UNIFORM_HPP__

//====================
// C++ includes
//====================
#include <utility>                             // Using forward values.
#include <string>                              // Passing uniforms by string literal name.

//====================
// Jackal includes
//====================
#include <jackal/math/vector2.hpp>             // Passing Vector2 objects as uniforms.
#include <jackal/math/vector3.hpp>             // Passing Vector3 objects as uniforms.
#include <jackal/math/vector4.hpp>             // Passing Vector4 objects as uniforms.
#include <jackal/math/matrix4.hpp>             // Passing Matrix4 objects as uniforms.
#include <jackal/math/colour.hpp>              // Passing Colour objects as uniforms.
#include <jackal/utils/ext/json.hpp>          // Setting uniforms by the value of Json values.

//====================
// Additional includes
//====================
#include <GL/glew.h>                           // Sending uniforms to glsl.

namespace jackal
{	
	//====================
	// Forward declarations
	//====================
	class Program;

	class Uniform final
	{
	private:
		//====================
		// Member variables
		//====================
		Program* m_pProgram; ///< The program that the uniforms are attached to.

	private:
		//====================
		// Private ctor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Deletes the default constructor, preventing use.
		////////////////////////////////////////////////////////////
		explicit Uniform() = delete;

		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the location of the uniform within the shader.
		///
		/// Each uniform within a shader is assigned a unique value, this
		/// method can be used to retrieve the location of the uniform within
		/// the shader.
		///
		/// @param uniform    The name of the uniform within the shader.
		///
		/// @returns          The location of the uniform within the shader.
		///
		////////////////////////////////////////////////////////////
		GLint getLocation(const std::string& uniform) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of an integer.
		///
		/// @param location The location of the uniform within the shader.
		/// @param variable The integer to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, int variable) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a float.
		///
		/// @param location The location of the uniform within the shader.
		/// @param variable The float to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, float variable) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a double.
		///
		/// @param location The location of the uniform within the shader.
		/// @param variable The double to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, double variable) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector2i object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector2i object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector2i& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector2f object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector2f object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector2f& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector2d object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector2d object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector2d& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector3i object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector3i object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector3i& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector3f object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector3f object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector3f& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector3d object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector3d object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector3d& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector4i object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector4i object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector4i& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector4f object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector4f object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector4f& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Vector4d object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param vector   The Vector4d object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Vector4d& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Colour object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param colour   The Colour object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Colour& colour) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the value of a uniform variable.
		///
		/// This method is used to set a uniform variable to the value
		/// of a Matrix4 object.
		///
		/// @param location The location of the uniform within the shader.
		/// @param matrix   The Matrix4 object to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void set(GLint location, const Matrix4& matrix) const;

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Accessible constructor for the Uniform object.
		///
		/// This is the only constructor available to the Uniform class,
		/// it initialises a Uniform object with the ID of the program it
		/// is going to be transferring uniform variables to.
		///
		/// @param program   The Program object to attach uniforms to.
		///
		////////////////////////////////////////////////////////////
		explicit Uniform(Program& program);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Uniform object.
		////////////////////////////////////////////////////////////
		~Uniform() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Sends a variable as a uniform to the attached shaders.
		///
		/// So communication can be achieved between C++ and GLSL, uniform
		/// variables can be transferred to give shaders additional behavior. 
		/// This method makes use of forwarding of variables in order to support
		/// many different variable types.
		///
		/// @param uniform   The name of the uniform in the GLSL shader.
		/// @param value     The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		void setParameter(const std::string& uniform, T value);

		////////////////////////////////////////////////////////////
		/// @brief Sends a Json value as a uniform to the attached shaders.
		///
		/// So communication can be achieved between C++ and GLSL, uniform
		/// variables can be transferred to give shaders additional behavior. 
		/// This method makes use of forwarding of variables in order to support
		/// many different variable types. This method is invoked by the Shader load
		/// method to apply constant uniforms.
		///
		/// @param uniform   The JSON value that contains the uniform.
		///
		////////////////////////////////////////////////////////////
		void setParameter(const nlohmann::json& uniform);
	};

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	void Uniform::setParameter(const std::string& uniform, T value)
	{
		this->set(this->getLocation(uniform), std::forward<T>(value));
	}

} // namespace jackal

#endif//__JACKAL_UNIFORM_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Uniform
/// @ingroup rendering
///
/// The jackal::Uniform class is a basic class that encapsulates
/// the behavior needed to send various different parameters and
/// values to shaders as uniform variables. It is internally used
/// by the Shader class to bind the various parameters and values 
/// of the Material object.
///
/// Due to its internal use, it is not exposed to the lua scripting 
/// interface.
///
/// @code
/// using namespace jackal;
///
/// // Create a new program object and attach shaders.
/// Program program;
/// program.create();
///
/// program.attachShader("~shaders/example_shader.vertex.glsl", eShaderType::VERTEX);
/// program.attachShader("~shaders/example_shader.fragment.glsl", eShaderType::FRAGMENT);
///
/// // Compile and link the shaders.
/// program.compile();
///
/// // Create a new Uniform object and link it to the program.
/// Uniform uniform(program);
///
/// // Send a fictional value as a uniform.
/// uniform.setParameter("test_variable", Vector3f::one());
/// @endcode
///
////////////////////////////////////////////////////////////