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
#include <jackal/rendering/texture.hpp>          // Texture class declaration.
#include <jackal/utils/log.hpp>                  // Logging warnings and errors.
#include <jackal/utils/constants.hpp>            // Using the constant log location.
#include <jackal/core/virtual_file_system.hpp>   // Searching paths with the virtual file system.
#include <jackal/utils/json_file_reader.hpp>     // Parsing the json file and utilising the result.

//====================
// Additional includes
//====================
#include <SDL2/SDL_image.h>                      // Loading an image from a directory.

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
	Texture::Texture()
		: Resource(), m_ID(0), m_size(), m_mode(eWrapMode::CLAMP), m_filter(eFilter::LINEAR)
	{
		this->create();
	}

	////////////////////////////////////////////////////////////
	Texture::~Texture()
	{
		if (m_ID)
		{
			glDeleteTextures(1, &m_ID);
		}
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	GLuint Texture::getID() const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	Vector2i Texture::getSize() const
	{
		return m_size;
	}

	////////////////////////////////////////////////////////////
	eWrapMode Texture::getWrapMode() const
	{
		return m_mode;
	}

	////////////////////////////////////////////////////////////
	eFilter Texture::getFilter() const
	{
		return m_filter;
	}

	//====================
	// Protected getters and setters
	//====================
	////////////////////////////////////////////////////////////
	void Texture::setSize(const Vector2i& size)
	{
		m_size = size;
	}

	//====================
	// Private methods
	//====================
	////////////////////////////////////////////////////////////
	bool Texture::loadFromFile(const std::string& filename, eWrapMode mode, eFilter filter)
	{
		std::string path;
		if (!VirtualFileSystem::getInstance().resolve(filename, path))
		{
			log.error(log.function(__FUNCTION__, filename), "Failed. Could not find external image.");
			return false;
		}

		SDL_Surface* pSurface = IMG_Load(path.c_str());
		if (!pSurface)
		{
			log.error(log.function(__FUNCTION__, filename), "Failed to load image.");
			return false;
		}

		m_size.x = pSurface->w;
		m_size.y = pSurface->h;
		m_mode = mode;
		m_filter = filter;

		// basic auto-detection of type.
		GLenum format = pSurface->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

		GLenum wrapMode = static_cast<GLenum>(m_mode);
		GLenum filtering = static_cast<GLenum>(m_filter);

		Texture::bind(*this);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		Texture::unbind();

		SDL_FreeSurface(pSurface);

		return true;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Texture::create()
	{
		glGenTextures(1, &m_ID);
	}

	////////////////////////////////////////////////////////////
	bool Texture::load(const std::string& filename)//override
	{
		JSONFileReader reader;
		if (reader.read(filename))
		{
			Json::Value root = reader.getRoot();
			Json::Value desc = root["description"];

			std::string wrapMode = desc["wrap-mode"].asString();
			std::string filtering = desc["filter"].asString();

			eWrapMode mode;
			if (wrapMode == "clamp")
			{
				mode = eWrapMode::CLAMP;
			} 
			else if (wrapMode == "repeat")
			{
				mode = eWrapMode::REPEAT;
			} 
			else
			{
				mode = eWrapMode::CLAMP;
				log.warning(log.function(__FUNCTION__, filename), "Unknown wrap-mode declared. Defaulting to CLAMP");
			}

			eFilter filter;
			if (filtering == "linear")
			{
				filter = eFilter::LINEAR;
			}
			else if (filtering == "nearest")
			{
				filter = eFilter::NEAREST;
			}
			else
			{
				filter = eFilter::LINEAR;
				log.warning(log.function(__FUNCTION__, filename), "Unknown filtering declared. Defaulting to LINEAR");
			}

			if (!this->loadFromFile(root["image"].asString(), mode, filter))
			{
				return false;
			}
		}
		else
		{
			log.warning(log.function(__FUNCTION__, filename), "Failed to read json file.");
			return false;
		}

		return true;
	}
	
	////////////////////////////////////////////////////////////
	void Texture::bind(const Texture& texture, GLint location/*= 0*/)
	{
		glBindTexture(GL_TEXTURE_2D + location, texture.getID());
	}

	////////////////////////////////////////////////////////////
	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} // namespace jackal