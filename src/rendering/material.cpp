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
// Jackal methods
//====================
#include <jackal/rendering/material.hpp>          // Material class declaration.
#include <jackal/utils/log.hpp>                   // Logging warnings and errors.
#include <jackal/utils/json_file_reader.hpp>      // Loading json file from directory.
#include <jackal/utils/resource_manager.hpp>      // Loading textures and shaders from the resource manager.

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
	Material::Material()
		: m_ID(0), m_shader(nullptr), m_textures(), m_colour(), m_lighting(true), m_shininess(0.0f)
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	int64_t Material::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	const Colour& Material::getColour() const
	{
		return m_colour;
	}

	////////////////////////////////////////////////////////////
	void Material::setColour(const Colour& colour)
	{
		m_colour = colour;
	}

	////////////////////////////////////////////////////////////
	float Material::getShininess() const
	{
		return m_shininess;
	}

	////////////////////////////////////////////////////////////
	void Material::setShininess(float shininess)
	{
		m_shininess = shininess;
	}

	////////////////////////////////////////////////////////////
	bool Material::isLightingEnabled() const
	{
		return m_lighting;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Material::load(const std::string& filename)//override
	{
		using namespace nlohmann;

		JSONFileReader reader;
		if (reader.read(filename))
		{
			json root = reader.getRoot();

			this->setName(root.value("name", filename));

			m_lighting  = root.value("lighting-enabled", true);
			m_colour    = root.value("diffuse-colour", Colour::white());
			m_shininess = root.value("shininess", 0.0f);

			json textures = root["textures"];
			m_textures.at(eTextureType::DIFFUSE) = Texture::find(textures["diffuse"].get<std::string>());
			m_textures.at(eTextureType::SPECULAR) = Texture::find(textures["specular"].get<std::string>());
	
			m_shader = Shader::find(root["shader"].get<std::string>());

			m_ID |= m_shader->getID() << 24;
			m_ID |= m_textures.at(eTextureType::DIFFUSE)->getID() << 16;
			m_ID |= m_textures.at(eTextureType::SPECULAR)->getID() << 8;

			return true;
		}
		else
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to parse json file.");
			return false;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	ResourceHandle<Material> Material::find(const std::string& name)
	{
		return ResourceManager::getInstance().get<Material>(name);
	}

	////////////////////////////////////////////////////////////
	void Material::process(const Transform& transform)
	{
		m_shader->process(transform, *this);
	}

	////////////////////////////////////////////////////////////
	void Material::bind(const Material& material)
	{
		Shader::bind(*material.m_shader.get());
		for (std::size_t i = 0; i < material.m_textures.size(); i++)
		{
			Texture* pTex = material.m_textures.at(i).get();
			if (pTex)
			{
				Texture::bind(*pTex, i);
			}
		}
	}

	////////////////////////////////////////////////////////////
	void Material::unbind()	
	{
		Shader::unbind();
		Texture::unbind();
	}

} // namespace jackal