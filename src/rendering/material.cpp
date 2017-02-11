#include <jackal/rendering/material.hpp>

namespace jackal
{
	Material::Material()
		: m_shader(), m_texture()
	{
	}

	const Shader& Material::getShader() const
	{
		return m_shader;
	}

	const Texture& Material::getTexture() const
	{
		return m_texture;
	}

	bool Material::load(const std::string& filename)
	{
		return true;
	}

} // namespace jackal