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

#ifndef __JACKAL_PROGRAM_HPP__
#define __JACKAL_PROGRAM_HPP__ 

//====================
// C++ includes
//====================
#include <vector>                            // Container for different shader objects.

//====================
// Jackal includes
//====================
#include <jackal/rendering/glsl_object.hpp>  // Creating and compiling glsl objects.

namespace jackal 
{
	class Program final 
	{
	private:
		//====================
		// Member variables
		//====================
		GLuint                  m_ID;       ///< The unique ID of the Program object.
		std::vector<GLSLObject> m_shaders;  ///< All of the glsl shaders attached to the Program.
		bool                    m_compiled; ///< Whether the shaders have already been compiled.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Program object.
		///
		/// The default constructor sets all of the member variables
		/// to default values. The Program object is not use-able in this
		/// state.
		///
		////////////////////////////////////////////////////////////
		explicit Program();

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the Program object.
		///
		/// The destructor implicitly calls the destroy method that
		/// de-allocates the memory assigned to the GPU through the 
		/// ID.
		///
		////////////////////////////////////////////////////////////
		~Program();

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the unique ID of the Program object.
		///
		/// The ID refers to the unique identifier that is assigned to this
		/// Program object. It is assigned when the create method is invoked
		/// and refers to the behavior on the GPU side.
		///  
		/// @returns   The unique ID of the Program object.
		///
		////////////////////////////////////////////////////////////
		GLuint getID() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates the ID for the Program object.
		///
		/// When the Program object is created, it assigns the ID to 
		/// a value that can be used to refer to specific behavior on the
		/// GPU and attached shaders.
		///
		////////////////////////////////////////////////////////////
		void create();

		////////////////////////////////////////////////////////////
		/// @brief Destroys the ID of the Program object.
		///
		/// When the destroy method is invoked, if the ID has been assigned
		/// a value from the create method, it frees the memory on the GPU.
		///
		////////////////////////////////////////////////////////////
		void destroy();

		////////////////////////////////////////////////////////////
		/// @brief Creates and attaches a shader to the Program object.
		///
		/// When this method is invoked, a GLSLObject is created on the stack
		/// and the create method is invoked. The object is then retained by the 
		/// Program and subsequently compiled by the Program when they are linked and
		/// readied for use.
		///
		/// @param filename   The file location of the external shader.
		/// @param type       The shader type to create.
		///
		////////////////////////////////////////////////////////////
		void attachShader(const std::string& filename, eShaderType type);

		////////////////////////////////////////////////////////////
		/// @brief Compile the Program object.
		///
		/// When the Program is compiled, all of the attached shaders
		/// are compiled and linked to the Program ID. When the Program
		/// is bound, all of the functionality linked to it will be
		/// executed.
		///
		/// @returns    True if the shaders are successfully compiled and linked.
		///
		////////////////////////////////////////////////////////////
		bool compile();

		////////////////////////////////////////////////////////////
		/// @brief Bind the specified Program object.
		///
		/// When a Program object is bound, the next objects and meshes to render
		/// will utilise the Program's shader behaviours.
		///
		/// @param program    The Program object to bind.
		///
		////////////////////////////////////////////////////////////
		static void bind(const Program& program);

		////////////////////////////////////////////////////////////
		/// @brief Unbinds any currently bound programs.
		///
		/// When the Program is unbound, the objects will no longer
		/// utilise the programs shader behaviour.
		///
		////////////////////////////////////////////////////////////
		static void unbind();
	};

} // namespace jackal 

#endif//__JACKAL_PROGRAM_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Program
/// @ingroup rendering
///
/// The jackal::Program is an encapsulated class that is used
/// to create and link a variety of GLSLObjects. It is internally
/// used by the Shader classes for compiling and binding the behaviors
/// loaded from the external glsl files. 
///
/// The Program object also supplies logging of issues and errors that
/// may occur during linkage and compilation. Due to the internal use
/// of the class, it is not exposed to the lua scripting interface.
///
/// @code
/// using namespace jackal;
///
/// // Create the program object.
/// Program program;
/// program.create();  // Assigns the ID a value.
///
/// // Include two external shaders. The VirtualFileSystem can be used.
/// program.attachShader("~shaders/basic_shader.vertex.glsl", eShaderType::VERTEX);
/// program.attachShader("~shaders/basic_shader.fragment.glsl", eShaderType::FRAGMENT);
///
/// // Compile the program and its shaders.
/// program.compile();
///
/// // Bind the program and render an object.
/// Program::bind(program);
/// // render.
/// Program::unbind();
/// @endcode
///
////////////////////////////////////////////////////////////