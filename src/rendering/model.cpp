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
#include <jackal/rendering/model.hpp>           // Model class declaration.
#include <jackal/utils/log.hpp>                 // Logs warnings and errors.
#include <jackal/core/virtual_file_system.hpp>  // Loading files using the virtual file system.
#include <jackal/utils/resource_manager.hpp>    // Retrieving a Model resource from the manager.

//====================
// Additional includes
//====================
#include <assimp/Importer.hpp>                  // Importing the model from an external source.
#include <assimp/scene.h>                       // Loading the model into a scene object.
#include <assimp/postprocess.h>                 // Post-processing. Flipping uv's.

namespace jackal
{
	//====================
	// Local variables
	//====================
	static DebugLog log("logs/engine_log.txt");

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Model::Model()
		: IRenderable(), Resource(), m_meshes()
	{
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	void Model::loadNode(aiNode* pNode, const aiScene* pScene)
	{
		for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
		{
			this->convert(pScene->mMeshes[pNode->mMeshes[i]], pScene);
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++)
		{
			this->loadNode(pNode->mChildren[i], pScene);
		}
	}

	////////////////////////////////////////////////////////////
	void Model::convert(aiMesh* pMesh, const aiScene* pScene)
	{
		std::vector<Vertex_t> vertices;
		std::vector<GLuint> indices;

		for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
		{
			Vertex_t vertex;
			vertex.position.x = pMesh->mVertices[i].x;
			vertex.position.y = pMesh->mVertices[i].y;
			vertex.position.z = pMesh->mVertices[i].z;

			if (pMesh->mTextureCoords[0])
			{
				vertex.uv.x = pMesh->mTextureCoords[0][i].x;
				vertex.uv.y = pMesh->mTextureCoords[0][i].y;
			}

			if (pMesh->mNormals)
			{
				vertex.normal.x = pMesh->mNormals[i].x;
				vertex.normal.y = pMesh->mNormals[i].y;
				vertex.normal.z = pMesh->mNormals[i].z;
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
		{
			aiFace face = pMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		
		m_meshes.emplace_back(vertices, indices);
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Model::load(const std::string& filename) // override
	{
		std::string path;
		if (!VirtualFileSystem::getInstance().resolve(filename, path))
		{
			log.warning(log.function(__FUNCTION__, filename), "Failed to load. Incorrect path.");
			return false;
		}

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!pScene || pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
		{
			log.warning(log.function(__FUNCTION__, filename), "Failed to import model:", importer.GetErrorString());
			return false;
		}

		this->loadNode(pScene->mRootNode, pScene);
		log.debug(log.function(__FUNCTION__, filename), "Imported successfully.");

		return true;
	}

	////////////////////////////////////////////////////////////
	ResourceHandle<Model> Model::find(const std::string& name)
	{
		return ResourceManager::getInstance().get<Model>(name);
	}

	////////////////////////////////////////////////////////////
	void Model::render()
	{
		for (auto& mesh : m_meshes)
		{
			mesh.render();
		}
	}

} // namespace jackal