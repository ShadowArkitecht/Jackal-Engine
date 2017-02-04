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

#ifndef __JACKAL_SHADER_HPP__
#define __JACKAL_SHADER_HPP__ 

//====================
// Jackal includes
//====================
#include <jackal/rendering/program.hpp> // The Program to attach shader files to.
#include <jackal/rendering/uniform.hpp> // Adding uniforms to the shaders.

namespace jackal
{
	class Shader // TODO: Extend from resource and store it.
	{
	private:
		//====================
		// Member variables
		//====================
		Program m_program; ///< The Program to attach shaders to and compile.
		Uniform m_uniform; ///< Uniform class for communication between C++ and GLSL.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Shader object.
		///
		/// The default constructor sets all of the member variables to
		/// default values and creates a unique ID for the Program object.
		///
		////////////////////////////////////////////////////////////
		explicit Shader();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Shader object.
		////////////////////////////////////////////////////////////
		~Shader() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Attaches a glsl shader to the Program object.
		///
		/// When this method is invoked, it will utilise the Program objects
		/// attachShader method and create and attach the shader to the
		/// Program for use.
		///
		/// @param filename    The filename of the shader.
		/// @param type        The type of shader to attach.
		///
		////////////////////////////////////////////////////////////
		void attachShader(const std::string& filename, eShaderType type);

		////////////////////////////////////////////////////////////
		/// @brief Compiles the shader object, ready for use.
		///
		/// This method abstracts the behavior from the Program object
		/// and invokes the subsequent objects compile method. The Program
		/// will only compile if it not already been compiled.
		///
		/// @returns True if the shader compiled successfully.
		///
		////////////////////////////////////////////////////////////		
		bool compile();

		////////////////////////////////////////////////////////////
		/// @brief Processes the uniforms attached to the shader.
		///
		/// When this method is invoked, it will update all of the subsequent
		/// uniform variables contained within the glsl objects and change their
		/// values.
		///
		////////////////////////////////////////////////////////////
		void process();

		////////////////////////////////////////////////////////////
		/// @brief Binds a shader to the OpenGL stack and utilises its behavior.
		///
		/// When a shader is bound, any object that is subsequently rendered
		/// will utilise the behavior defined in the glsl objects.
		///
		/// @param shader    The shader to bind to top the OpenGL stack.
		///
		////////////////////////////////////////////////////////////
		static void bind(const Shader& shader);

		////////////////////////////////////////////////////////////
		/// @brief Unbinds the shader object.
		///
		/// When the shader is unbound, any objects that render after this
		/// statement will not utilise the behavior defined in the GLSL
		/// shaders.
		///
		////////////////////////////////////////////////////////////
		static void unbind();
	};

} // namespace jackal 

#endif//__JACKAL_SHADER_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Shader
/// @ingroup rendering
///
/// The jackal::Shader class is an object that is used to render
/// and update the uniform variables contained within glsl shaders
/// to apply the behavior to subsequent meshes that render.
///
/// Due to the internal use of the shaders, they are not exposed
/// to the lua scripting inteface. To alter the appearance of objects
/// with the shader, calls to the Material instance should be made through
/// lua.
///
/// @code
/// using namespace jackal;
///
/// // Create a shader object.
/// Shader shader;
/// 
/// // Attach glsl objects.
/// shader.attachShader("~shaders/test_shader.vertex.glsl", eShaderType::VERTEX);
/// shader.attachShader("~shaders/test_shader.fragment.glsl", eShaderType::FRAGMENT);
///
/// // Compile it for use.
/// shader.compile();
///
/// // Bind the shader...
/// Shader::bind(shader);
/// @endcode
///
////////////////////////////////////////////////////////////