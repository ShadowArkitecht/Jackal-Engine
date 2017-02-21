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
#include <jackal/rendering/material.hpp>     // Material class declaration.
#include <jackal/utils/log.hpp>              // Logging warnings and errors.
#include <jackal/utils/json_file_reader.hpp> // Loading json file from directory.
#include <jackal/utils/resource_manager.hpp> // Loading textures and shaders from the resource manager.

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
		: m_ID(0), m_shader(), m_texture(), m_colour()
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
	const Shader& Material::getShader() const
	{
		return m_shader;
	}

	////////////////////////////////////////////////////////////
	const Texture& Material::getTexture() const
	{
		return m_texture;
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

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	bool Material::load(const std::string& filename)//override
	{
		JSONFileReader reader;
		if (reader.read(filename))
		{
			nlohmann::json root = reader.getRoot();

			m_shader = ResourceManager::getInstance().get<Shader>(root["shader"].get<std::string>());
			m_texture = ResourceManager::getInstance().get<Texture>(root["texture"].get<std::string>());

			nlohmann::json colour = root["colour"];
			m_colour = Colour(colour["r"].get<float>(), colour["g"].get<float>(), colour["b"].get<float>(), colour["a"].get<float>());

			m_ID |= m_shader.getID() << 24;
			m_ID |= m_texture.getID() << 16;

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
	void Material::process()
	{
		m_shader.process(*this);
	}

	////////////////////////////////////////////////////////////
	void Material::bind(const Material& material)
	{
		Shader::bind(material.m_shader);
		Texture::bind(material.m_texture);
	}

	////////////////////////////////////////////////////////////
	void Material::unbind()	
	{
		Shader::unbind();
		Texture::unbind();
	}

} // namespace jackal