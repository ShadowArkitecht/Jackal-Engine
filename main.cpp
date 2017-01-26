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
// C++ includes
//====================
#include <iostream>

//====================
// Jackal includes
//====================
#include <jackal/utils/properties.hpp>
#include <jackal/core/virtual_file_system.hpp>

using namespace jackal;

int main(int argc, char** argv)
{
	auto& vfs = VirtualFileSystem::getInstance();
	vfs.mount("locale", "data/locale");

	Properties properties;
	properties.open("~locale/en_UK.properties");
	
	std::cout << properties.get("menu.resource") << std::endl;
	std::cout << properties.get("object.selection.name", "Test object") << std::endl;

	getchar();
	return 0;
}