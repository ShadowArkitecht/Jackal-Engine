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

#ifndef __JACKAL_WINDOW_HPP__
#define __JACKAL_WINDOW_HPP__

//====================
// C++ includes
//==================== 
#include <string>                             // Storing the window title.

//====================
// Jackal includes
//==================== 
#include <jackal/math/vector2.hpp>            // Storing window size and position.
#include <jackal/utils/context_settings.hpp>  // Storing settings of OpenGL.

//====================
// Additional includes
//==================== 
#include <SDL2/SDL.h>                         // Creating and manipulating SDL window.

namespace jackal
{
	//====================
	// Forward declarations
	//==================== 
	class ConfigFile;

	class Window final
	{
	private:
		//====================
		// Member variables
		//==================== 
		static Window*    m_pMain;      ///< Global instance of the current window.
		SDL_Window*       m_pWindow;    ///< Internal SDL window object.
		SDL_GLContext     m_context;    ///< Internal SDL GL context.
		std::string       m_title;      ///< The title of the window which appears in the title-bar.
		Vector2i          m_position;   ///< Position of the window on-screen.
		Vector2i          m_size;       ///< Width and height of the window.
		ContextSettings_t m_settings;   ///< Various settings used by OpenGL.
		bool              m_running;    ///< Whether the window is currently running.

	public:
		//====================
		// Ctor and dtor
		//==================== 
		////////////////////////////////////////////////////////////
		/// @brief Default constructor of the Window object.
		///
		/// The default constructor sets all of the member variables to default values.
		/// The constructor does not create the visible window itself, the
		/// subsequent create method is used to initialise the window and its
		/// context.
		///
		////////////////////////////////////////////////////////////
		explicit Window();

		////////////////////////////////////////////////////////////
		/// @brief Destructor of the Window object.
		///
		/// The destructor will free the resources currently being used by the
		/// Window object. This includes releasing the SDL2 functionality and
		/// SDL2 GL context.
		///
		////////////////////////////////////////////////////////////
		~Window();

		//====================
		// Getters and setters
		//==================== 
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the main Window reference object.
		///
		/// When the Window is first created, a main Window reference is set.
		/// This main Window can be used outside the scope of this Window for
		/// convenience, instead of having to pass the Window as a parameter to
		/// several methods.
		///
		/// @returns     A static reference to the main Window.
		///
		////////////////////////////////////////////////////////////
		static Window& getMain();

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the title of the Window.
		///
		/// The title refers to the string that appears at the top of this
		/// current Window object. The title is originally set when the create method
		/// is called.
		///
		/// @returns   The current title of the Window object.
		///
		////////////////////////////////////////////////////////////
		std::string getTitle() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets a new title of the Window.
		///
		/// The title refers to the string that appears at the top of this
		/// current window. This method can be called to change the title during
		/// runtime.
		///
		/// @param title    The new title of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setTitle(const std::string& title);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the position of the Window within the screen.
		///
		/// The position refers to the position of the Window within the desktop
		/// environment. This position only applies if the Window is not
		/// currently in full-screen.
		///
		/// @returns    The current position of the Window.
		///
		////////////////////////////////////////////////////////////
		Vector2i getPosition() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets a new position of the Window on the screen.
		///
		/// The position refers to the position of the Window within the desktop
		/// environment. This method will set the position of the Window to a
		/// new point. The position only applies if the Window is not currently
		/// in full-screen.
		///
		/// @param position     The new position of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(const Vector2i& position);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the current width and height of the Window object.
		///
		/// The size refers to the width and height of the current Window.
		/// The size only effect the size of the Window when it is not in
		/// full-screen mode.
		///
		/// @returns    The current size of the Window.
		///
		////////////////////////////////////////////////////////////
		Vector2i getSize() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets a new width and height of the Window object.
		///
		/// The size refers to the width and height of the current Window.
		/// The size only effect the size of the Window when it is not in
		/// full-screen mode. This method can be used to change the Window size
		/// during run-time.
		///
		/// @param size    The new size of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setSize(const Vector2i& size);

		////////////////////////////////////////////////////////////
        /// @brief Retrieves the Context Settings of the current Window.
        ///
        /// The context settings are the global settings of the OpenGL context
        /// that this window will be complying with when it is created. The
        /// context can only be altered upon Windw initialisation. By default
        /// the OpenGL version is 3.3.
        ///
        /// @returns     The OpenGL settings of the Window.
        ///
		////////////////////////////////////////////////////////////
		const ContextSettings_t& getSettings() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the current running state of the Window.
		///
		/// When the Window is created, it is automatically set to running upon
		/// success. This method should be utilised within a loop so that the
		/// game will continue to run whilst the window is still operating.
		///
		/// @returns    The current running state of the Window.
		///
		////////////////////////////////////////////////////////////
		bool isRunning() const;

		//====================
		// Methods
		//==================== 
		////////////////////////////////////////////////////////////
		/// @brief Creates the Window object.
		///
		/// The constructor of the window does not create the Window object.
		/// This method is used to construct the Window and provide additional
		/// error checking to make sure that the Window is created without
		/// potential problems. If a problem is encountered, a error message
		/// will be printed to the console widow.
		///
		/// @param title         The title of the Window.
		/// @param position      The position of the Window on the desktop.
		/// @param size          The width and height  of the Window.
		/// @param settings      The contextual OpenGL settings of the Window.
		///
		/// @returns             True upon successful initialisation.
		///
		////////////////////////////////////////////////////////////
		bool create(const std::string& title, const Vector2i& position, const Vector2i& size, const ContextSettings_t& settings);

		////////////////////////////////////////////////////////////
		/// @brief Creates the Window object.
		///
		/// The constructor of the window does not create the Window object.
		/// This method is used to construct the Window and provide additional
		/// error checking to make sure that the Window is created without
		/// potential problems. If a problem is encountered, a error message
		/// will be printed to the console widow.
		///
		/// @param config        The parameters of the Window retrieved from the config file.
		///
		/// @returns             True upon successful initialisation.
		///
		////////////////////////////////////////////////////////////
		bool create(const ConfigFile& config);

		////////////////////////////////////////////////////////////
		/// @brief Polls the keyboard and mouse input of the application.
		///
		/// So that input can be used within the application, it has to be
		/// polled every frame so that the input can be read each frame of
		/// the engine. This method will also poll the close window method, and
		/// end the engine when the 'x' button is clicked.
		///
		////////////////////////////////////////////////////////////
        void pollEvents();

        ////////////////////////////////////////////////////////////
        /// @brief Closes the current Window object.
        ///
        /// When invoked, this method will close the current Window object and 
        /// stop it from running. This method should be called when the user 
        /// wishes to exit the application and is called automatically when the
        /// 'x' of the window is clicked.
        ///
		////////////////////////////////////////////////////////////
        void close();

		////////////////////////////////////////////////////////////
		/// @brief Clears the buffer of the Window.
		///
		/// This method should be called at the beginning of every render frame.
		/// This prevents artifacting from previous scenes and clears the buffer
		/// for addtional use.
		///
		////////////////////////////////////////////////////////////
        void clear() const;

		////////////////////////////////////////////////////////////
		/// @brief Swaps the buffer of the Window.
		///
		/// OpenGL utilises double buffers in order to smoothly render each
		/// scene without any artifacting of render glitches. The swap method
		/// should be called at the end of the current rendering frame.
		///
		////////////////////////////////////////////////////////////
        void swap() const;
	};

} // namespace jackal 

#endif//__JACKAL_WINDOW_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Window
/// @ingroup core
///
/// jackal::Window is one of the main important classes of the
/// Jackal Engine. It defines an SDL Window that can be painted
/// and rendered upon by subsequent classes in the graphics
/// module.
///
/// jackal::Window is only responsible for the rendering of
/// objects, although it does poll inputs from the keyboard and mouse,
/// it does not directly interact with their functionality. The window
/// is the first instance that is initialised within the application and
/// provides an access point to all the modules of the Jackal Engine.
///
/// Additional windows should not be constructed, as it can corrupt the
/// OpenGL context and cause undefined behavior. Specific elements of the
/// Window object are exposed to the lua scripting interface for use.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Loads in a configuration file for window creation.
/// ConfigFile file;
/// file.open("~config/main.jcfg");
///
/// // Creates a new Window.
/// Window window;
/// window.create(config);
///
/// // Basic Main window loop.
/// while (window.isRunning())
/// {
///		Window.clear()
///		// Rendering of objects should go here.
///		Window.swap();
/// }
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Window instances cannot be created in lua, only the main window can be referenced.
/// local window = Window.get_main()
///
/// -- Store and print variables of the window.
/// local size = window.size
/// print(size)
///
/// -- Change the name of the window
/// window.title = "New window!"
/// @endcode
///
////////////////////////////////////////////////////////////