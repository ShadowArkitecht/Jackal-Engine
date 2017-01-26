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

#ifndef __JACKAL_VIRTUAL_FILE_SYSTEM_HPP__
#define __JACKAL_VIRTUAL_FILE_SYSTEM_HPP__

//====================
// C++ includes
//====================
#include <unordered_map>               // Storing the virtual paths and their directories.
#include <string>                      // Paths are stored as strings.
#include <vector>                      // Each virtual path can have multiple directories.
 
//====================
// Jackal includes
//====================
#include <jackal/utils/singleton.hpp>  // VirtualFileSystem is a singleton class.

namespace jackal 
{
	class VirtualFileSystem final : public Singleton<VirtualFileSystem>
	{
		friend class Singleton<VirtualFileSystem>;

	private:
		//====================
		// Member variables
		//====================
		std::unordered_map<std::string, std::vector<std::string>> m_paths; ///< All of the virtual paths and their directories.

	private:
		//====================
		// Private ctor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default private constructor for the VirtualFileSystem object.
		///
		/// The default constructor calls the parent Singleton class and
		/// sets all of the virtual paths to a default value. The constructor
		/// is placed within a private scope in order to comply with the
		/// singleton design pattern.
		///
		////////////////////////////////////////////////////////////
		explicit VirtualFileSystem();

	public:
		//====================
		// Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the VirtualFileSystem object.
		////////////////////////////////////////////////////////////
		~VirtualFileSystem() = default;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Mounts a directory to a virtual path.
		///
		/// When a path is mounted, a directory on disk is mounted to a
		/// virtual path, when the path is invoked by any class that
		/// loads external sources, they can utilise the VirtualFileSystem
		/// to look in several different directories. This can be useful if
		/// assets are spread throughout many different directories.
		///
		/// @param path	        The name of the virtual path to mount to.
		/// @param directory    The physical location on disk.
		///
		////////////////////////////////////////////////////////////
		void mount(const std::string& path, const std::string& directory);

		////////////////////////////////////////////////////////////
		/// @brief Dismounts a virtual path and its directories.
		/// 
		/// When the virtual path is dismounted, all of the directories
		/// that the path is pointing to are cleared. If the virtual path
		/// was not found within the system, the paths remain unchanged.
		///
		/// @param path     The virtual path is dismount.
		///
		////////////////////////////////////////////////////////////
		void dismount(const std::string& path);

		////////////////////////////////////////////////////////////
		/// @brief Dismounts all of the virtual paths.
		///
		/// When this method is invoked, all of the virtual paths and their
		/// directories are cleared. This will set the VirtualFileSystem back
		/// to its' default state. This method should only be invoked if
		/// the virtual paths are no longer needed, as it can result in undefined
		/// behavior for classes that rely on its behavior.
		///
		////////////////////////////////////////////////////////////
		void dismountAll();

		////////////////////////////////////////////////////////////
		/// @brief Resolves the virtual path and retrieves the correct directory.
		///
		/// When the user wishes to utilises the virtual paths and retrieve a
		/// resource this method is invoked. It will search all of the directories
		/// mapped to the virtual path and check for the specified files existence, 
		/// if it is found, the directory is set to the result reference and true is
		/// returned. If the correct syntax is not used for this method, it will assume
		/// the user has passed in an absolute path and search the specified directory for
		/// the file. The syntax used to manipulate the virtual paths is to start
		/// the path with '~'.
		///
		/// @param path     The virtual path to search against.
		/// @param result   The result of the path searching.
		///
		/// @returns        True if the file was found within the VirtualFileSystem or externally.
		///
		////////////////////////////////////////////////////////////
		bool resolve(const std::string& path, std::string& result);
	};

} // namespace jackal 

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::VirtualFileSystem
/// @ingroup utils
///
/// The VirtualFileSystem is a singleton object that is used to map
/// actual directories and paths on disk to virtual paths. When an asset
/// within the engine is loaded, if specified, it can use the VirtualFileSystem
/// to load the resource from a variety of different mapped directories. The
/// user can map as many directories to a path as they please. Any method that
/// can utilise a virtual path, can also load the resource by its intended 
/// directory. The VirtualFileSystem inherits from the NonCopyable class and
/// can only be referenced, and not constructed through assignment or copy
/// construction.
///
/// To use a virtual path, the path must begin with the character
/// '~'. The VirtualFileSystem can also be used within the lua scripting interface
/// and is exposed for use. 
///
/// C++ Code example:
/// @code 
/// auto& vfs = VirtualFileSystem::getInstance();
///
/// vfs.mount("textures", "assets/textures"); // The virtual path and the actual directory.
/// 
/// // The tilda will denote that the texture will use the VirtualFileSystem.
/// // Without the tilda, the system assumes you are using an absolute path.
/// Texture* pTexture = Texture::create("~textures/image.png");
/// @endcode
///
/// The VirtualFileSystem can also be used within lua scripts, however it should be
/// noted that this should not be done by scripts that are constantly instantiated, it
/// is better suited for controller level scripting.
///
/// Lua Code example:
/// @code
/// local vfs = VirtualFileSystem.get_instance()
///
/// vfs:mount("textures", "assets/textures") -- The virtual path and the actual directory.
///
/// -- The tilda will denote that the texture will use the VirtualFileSystem.
/// -- Without the tilda, the system assumes you are using an absolute path.
/// local texture = Texture.create("~textures/image.png")
/// @endcode
///
////////////////////////////////////////////////////////////

#endif//__JACKAL_VIRTUAL_FILE_SYSTEM_HPP__