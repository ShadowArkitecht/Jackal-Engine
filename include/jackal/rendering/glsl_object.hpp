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

#ifndef __JACKAL_GLSL_OBJECT_HPP__
#define __JACKAL_GLSL_OBJECT_HPP__

//====================
// C++ includes
//====================
#include <string>     // Loading external shaders by filename.

//====================
// Additional includes
//====================
#include <GL/glew.h>  // Compile and test the status of the loaded shader.

namespace jackal
{	
	//====================
	// Enumerations
	//====================
	enum class eShaderType
	{
		VERTEX,
		FRAGMENT,
		MAX
	};

	class GLSLObject final 
	{
	private:
		//====================
		// Member variables
		//====================
		GLuint      m_ID;       ///< The unique ID of the GLSL object.
		GLenum      m_type;     ///< The type of shader this object is.
		std::string m_filename; ///< The file location of the glsl shader.
		std::string m_source;   ///< The source (file contents) of the shader.
		bool        m_compiled; ///< Whether the object has already been compiled.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Recursively parses the shader from a source.
		///
		/// This method will recursively parse and store the source of
		/// the shader from the specified file directory. The method is
		/// recursive so that it can load and process any custom
		/// include statements that the shader may use. The parse method can
		/// utilise the VirtualFileSystem for getting the path of shaders.
		///
		/// @param filename   The file directory of the shader.
		///
		/// @returns          True upon successful parsing.
		///
		////////////////////////////////////////////////////////////
		bool parse(const std::string& filename);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the GLSLObject.
		///
		/// The default constructor will set all of the member variables
		/// to default values. The shader is not useable when first constructed.
		/// It must be created and compiled.
		///
		////////////////////////////////////////////////////////////
		explicit GLSLObject();

		////////////////////////////////////////////////////////////
		/// @brief Destructor for the GLSLObject.
		///
		/// When the destructor is called, it will implicitly call
		/// the destroy method, which de-allocates the GPU memory associated
		/// with the GLSLObject ID.
		///
		////////////////////////////////////////////////////////////
		virtual ~GLSLObject();
		
		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the ID of the GLSLObject.
		///
		/// The ID refers to the unique value assigned to each loaded in
		/// shader, the ID is needed for linking the shader to the subsequent
		/// program. 
		///
		/// @returns The unique ID of the shader.
		///
		////////////////////////////////////////////////////////////
		GLuint getID() const;

		////////////////////////////////////////////////////////////
		/// @brief Returns the file name of the glsl shader.
		///
		/// The filename represents the name of the file that was loaded
		/// in during parsing, the file name will either state the absolute
		/// or virtual path to the shader.
		///
		/// @returns  The file location of the glsl shader.
		///
		////////////////////////////////////////////////////////////
		std::string getFilename() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the compile state of the GLSL object.
		///
		/// When the shader is compiled, if it compiled successfully, 
		/// a variable is set to true.
		///
		/// @returns The compiled state of the GLSL object.
		///
		////////////////////////////////////////////////////////////
		bool isCompiled() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates the GLSLObject and loads the external file.
		///
		/// When the GLSLObject is created, it will check that the specified
		/// file has the correct extension and then parse the shader. If the
		/// shader fails to parse, warning and errors are logged to the external
		/// log file. This create will assign the correct type to the shader, depending
		/// on its extension.
		/// 
		/// @param filename    The external file directory of the shader.
		///
		/// @returns           True if the shader parsed successfully.
		///
		////////////////////////////////////////////////////////////
		bool create(const std::string& filename);

		////////////////////////////////////////////////////////////
		/// @brief Creates the GLSLObject and loads the external file.
		///
		/// When the GLSLObject is created, it will check that the specified
		/// file has the correct extension and then parse the shader. If the
		/// shader fails to parse, warning and errors are logged to the external
		/// log file.
		/// 
		/// @param filename    The external file directory of the shader.
		/// @param type        The shader type to parse.
		///
		/// @returns           True if the shader parsed successfully.
		///
		////////////////////////////////////////////////////////////
		bool create(const std::string& filename, eShaderType type);

		////////////////////////////////////////////////////////////
		/// @brief Destroys the created GLSLObject.
		///
		/// The only object that is retained by the GLSLObject is the 
		/// unique ID mapped to memory on the GPU. The destroy method
		/// will free these resources for additional use.
		///
		////////////////////////////////////////////////////////////
		void destroy();

		////////////////////////////////////////////////////////////
		/// @brief Compiles the loaded shader.
		///
		/// When the shader is compiled, it will process the information
		/// parsed in when created and check for any syntax errors or 
		/// problems. If no issues are found, the shader will parse successfully
		/// and a message will be sent to the external engine log file.
		///
		/// If the object has not invoked create, compilation will always
		/// fail due to a lack of information.
		///
		////////////////////////////////////////////////////////////
		void compile();
	};

} // namespace jackal 

#endif//__JACKAL_GLSL_OBJECT_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::GLSLObject
/// @ingroup rendering
///
/// The jackal::GLSLObject is responsible for laoding and compiling
/// external shader files for use within the application. The GLSLObject
/// is commonly used by the jackal::Program class for linking and use.
///
/// Various messages are sent to the log is creation or compilation
/// errors occur during creation and compilation of the GLSLObject. Due
/// to the shaders internal use, it is not exposed to the lua scripting
/// interface.
///
/// @code
/// using namespace jackal;
///
/// // Create a new GLSLObject and attempt to compile it.
/// GLSLObject object;
/// if (object.create("~shaders/basic_shader.vertex.glsl", eShaderType::VERTEX))
/// {
///		object.compile();
/// }
/// // Shader can now be used.
/// @endcode
///
////////////////////////////////////////////////////////////