#ifndef __JACKAL_MATERIAL_HPP__
#define __JACKAL_MATERIAL_HPP__ 

#include <jackal/utils/resource.hpp>
#include <jackal/rendering/texture.hpp>
#include <jackal/rendering/shader.hpp>

namespace jackal
{
	class Material : public Resource
	{
	private:
		Shader  m_shader;
		Texture m_texture;

	public:
		explicit Material();
		~Material() = default;

		const Shader& getShader() const;
		const Texture& getTexture() const;

		bool load(const std::string& filename);
	};

} // namespace jackal

#endif//__JACKAL_MATERIAL_HPP__