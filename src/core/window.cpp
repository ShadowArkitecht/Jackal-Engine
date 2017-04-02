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
#include <jackal/core/window.hpp>      // Window class declaration. 
#include <jackal/utils/log.hpp>        // Logging warnings and errors.
#include <jackal/utils/constants.hpp>  // Constant log location.
#include <jackal/core/config_file.hpp> // ConfigFile variable retrieval.

//====================
// Additional includes
//==================== 
#include <GL/glew.h>                   // Initialising GLEW context.
#include <SDL2/SDL_image.h>            // Initializing SDL image.

namespace jackal
{
	//====================
	// Local variables
	//==================== 
	static DebugLog log("logs/engine_log.txt"); // Logging warnings and errors.

	//====================
	// Static variables
	//==================== 
	Window* Window::m_pMain = nullptr;

	//====================
	// Ctor and dtor
	//==================== 
	////////////////////////////////////////////////////////////
	Window::Window()
		: m_pWindow(nullptr), m_context(), m_title(), m_position(), m_size(),
			m_settings(), m_running(false)
	{
	}

	////////////////////////////////////////////////////////////
	Window::~Window()
	{
        if (m_context)
        {
            SDL_GL_DeleteContext(m_context);
        }

        if (m_pWindow)
        {
            SDL_DestroyWindow(m_pWindow);
            m_pWindow = nullptr;
        }
	}

	//====================
	// Getters and setters
	//==================== 
	////////////////////////////////////////////////////////////
	Window& Window::getMain()
	{
		return *m_pMain;
	}

	////////////////////////////////////////////////////////////
	std::string Window::getTitle() const
	{
		return m_title;
	}

	////////////////////////////////////////////////////////////
	void Window::setTitle(const std::string& title)
	{
		SDL_SetWindowTitle(m_pWindow, title.c_str());
		m_title = title;
	}

	////////////////////////////////////////////////////////////
	Vector2i Window::getPosition() const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	void Window::setPosition(const Vector2i& position)
	{
		SDL_SetWindowPosition(m_pWindow, position.x, position.y);
		m_position = position;
	}

	////////////////////////////////////////////////////////////
	Vector2i Window::getSize() const
	{
		return m_size;
	}

	////////////////////////////////////////////////////////////
	void Window::setSize(const Vector2i& size)
	{
		SDL_SetWindowSize(m_pWindow, size.x, size.y);
		m_size = size;
	}

	////////////////////////////////////////////////////////////
	const ContextSettings_t& Window::getSettings() const 
	{
		return m_settings;
	}

	////////////////////////////////////////////////////////////
	bool Window::isRunning() const
	{
		return m_running;
	}

	//====================
	// Methods
	//==================== 
	////////////////////////////////////////////////////////////
	bool Window::create(const std::string& title, const Vector2i& position, const Vector2i& size, const ContextSettings_t& settings)
	{
		m_title = title;
		m_position = position;
		m_size = size;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
		{
			log.error(log.function(__FUNCTION__, title, position, size), "SDL failed to initialize:", SDL_GetError());
			return false;
		}

		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		{
			log.error(log.function(__FUNCTION__, title, position, size), "SDL image failed to initialize:", IMG_GetError());
			return false;
		}

		m_pWindow = SDL_CreateWindow(m_title.c_str(),
			                         m_position.x,
			                         m_position.y,
			                         m_size.x,
			                         m_size.y,
			                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (!m_pWindow)
		{
			log.error(log.function(title, position, size), "Failed to create window:", SDL_GetError());
			return false;
		}

		m_context = SDL_GL_CreateContext(m_pWindow);

		SDL_GL_SetSwapInterval(1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, m_settings.depthBits);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, m_settings.stencilBits);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_settings.majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_settings.minorVersion);

		m_running = true;
		if (!m_pMain)
		{
            glewExperimental = GL_TRUE; 
			GLenum error = glewInit();

			if (error != GLEW_OK)
			{
				log.error(log.function(__FUNCTION__, title, position, size), "GLEW failed to initialize:", glewGetErrorString(error));
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            log.debug(log.function(__FUNCTION__, title, position, size), "Main window set.");
			m_pMain = this;
		}

		glEnable(GL_DEPTH_TEST);

		log.debug(log.function(__FUNCTION__, title, position, size), "Created successfully.");
		return true;
	}

	////////////////////////////////////////////////////////////
	bool Window::create(const ConfigFile& config)
	{
		ContextSettings_t settings;
		settings.depthBits = config.get<unsigned int>("ContextSettings.depth_bits");
		settings.stencilBits = config.get<unsigned int>("ContextSettings.stencil_bits");
		settings.majorVersion = config.get<unsigned int>("ContextSettings.major_version");
		settings.minorVersion = config.get<unsigned int>("ContextSettings.minor_version");

		return this->create(config.get<std::string>("Window.title"),
		                    config.get<Vector2i>("Window.position"),
		                    config.get<Vector2i>("Window.size"),
		                    settings);	
	}

    ////////////////////////////////////////////////////////////
    void Window::pollEvents()
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                this->close();
            }

            // TODO(BEN): Poll input events.
        }
    }

    ////////////////////////////////////////////////////////////
    void Window::close() 
    {
        m_running = false;
    }

    ////////////////////////////////////////////////////////////
    void Window::clear() const
    {
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ////////////////////////////////////////////////////////////
    void Window::swap() const
    {
        SDL_GL_SwapWindow(m_pWindow);
    }

} // namespace jackal