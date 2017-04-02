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

#ifndef __JACKAL_MODEL_HPP__
#define __JACKAL_MODEL_HPP__

//====================
// C++ includes
//====================
#include <vector>                             // Container for the meshes.

//====================
// Jackal includes
//====================
#include <jackal/utils/resource.hpp>          // Model is a type of resource.
#include <jackal/rendering/irenderable.hpp>   // Model is a renderable object.
#include <jackal/rendering/mesh.hpp>          // Each model can be constructed of several meshes.
#include <jackal/utils/resource_handle.hpp>   // Retrieving a handle to the Model object.

//====================
// Forward declarations
//====================
struct aiNode;
struct aiScene;
struct aiMesh;

namespace jackal
{
	class Model final : public IRenderable, public Resource
	{
	private:
		//====================
		// Member variables
		//====================
		std::vector<Mesh> m_meshes; ///< The individual meshes of the model.

	private:
		//====================
		// Private methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Loads and processes each node of the loaded scene.
		///
		/// A node represents a collection of meshes and child nodes 
		/// that make up the model that is being externally imported.
		/// When a node is loaded, it will recursively loop through each
		/// child node and mesh and convert them to a object that
		/// the jackal engine can understand.
		///
		/// @param pNode  The node to process.
		/// @param pScene The overall scene of the external file.
		///
		////////////////////////////////////////////////////////////
		void loadNode(aiNode* pNode, const aiScene* pScene);

		////////////////////////////////////////////////////////////
		/// @brief Converts a mesh into a jackal equilavent mesh.
		///
		/// When this method is invoked, the information contained within
		/// the mesh being stored by assimp is converted into a format
		/// that the Jackal Engine can understand and render to the 
		/// OpenGL context.
		///
		/// @param pMesh  The assimp mesh to convert.
		/// @param pScene The overall scene of the imported model. 
		///
		////////////////////////////////////////////////////////////
		void convert(aiMesh* pMesh, const aiScene* pScene);

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Model object.
		///
		/// The default constructor will invoke the parent constructors
		/// and set the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit Model();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Model object.
		////////////////////////////////////////////////////////////
		virtual ~Model() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Loads an external model and processes it into the correct format.
		///
		/// When the load method is invoked, it will utilise the provided
		/// filename and load the external model. If the model is successfully
		/// loaded, it will be converted to a format that the Jackal Engine
		/// can utilise and render. The filename can utilise the virtual
		/// file system.
		///
		/// @param filename The file location of the model to load.
		///
		/// @returns True if the model loaded successfully.
		///
		////////////////////////////////////////////////////////////
		bool load(const std::string& filename) override;

		////////////////////////////////////////////////////////////
		/// @brief Finds a handle to the specified Model object.
		///
		/// This method is a simple wrapper method for retrieving a handle
		/// to a specified Model resource from the resource manager. If the
		/// model is not found, a handle with a null resource is returned.
		///
		/// @param name  The file name of the Model resource to retrieve.
		///
		/// @returns A handle to the specified Model resource.
		///
		////////////////////////////////////////////////////////////
		static ResourceHandle<Model> find(const std::string& name);

		////////////////////////////////////////////////////////////
		/// @brief Renders the model to the OpenGL context.
		///
		/// When the model is rendered, it will loop through each mesh
		/// that the model is constructed of and render them to the 
		/// context.
		///
		////////////////////////////////////////////////////////////
		void render() override;
	};

} // namespace jackal

#endif//__JACKAL_MODEL_HPP__