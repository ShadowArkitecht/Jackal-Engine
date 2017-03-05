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

#ifndef __JACKAL_VERTEX_HPP__
#define __JACKAL_VERTEX_HPP__

//====================
// Jackal includes
//====================
#include <jackal/math/vector3.hpp> // The position of the vertex.
#include <jackal/math/vector2.hpp> // The uv co-ordinates of the vertex.

namespace jackal
{
	struct Vertex_t final
	{
		//====================
		// Member variables
		//====================
		Vector3f position;  ///< The position of the vertex in 3D space. 
		Vector3f normal;    ///< The vertex normal.
		Vector2f uv;        ///< The uv co-ordinate of the vertex.

		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Vertex_t object.
		///
		/// The default constructor will set the position, normals and
		/// uv's to blank vectors, with elements equalling 0.
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t()
			: position(), normal(), uv()
		{
		}

		////////////////////////////////////////////////////////////
		/// @brief Constructor for specifying the vertex position and uv.
		///
		/// This constructor can be used for explicitly setting the position
		/// and the uv co-ordinate of the vertex. The vertex normal is set to
		/// ( 0, 0, 0 ).
		///
		/// @param position  The position of the vertex.
		/// @param uv        The uv co-ordinate of the vertex.
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t(const Vector3f& position, const Vector2f& uv)
			: position(position), normal(), uv(uv)
		{
		}

		////////////////////////////////////////////////////////////
		/// @brief Constructor for specifying the vertex position, uv and vertex normal.
		///
		/// This constructor can be used for explicitly setting the position,
		/// vertex normal and the uv co-ordinate of the vertex.
		///
		/// @param position  The position of the vertex.
		/// @param normal    The vertex normal.
		/// @param uv        The uv co-ordinate of the vertex.
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t(const Vector3f& position, const Vector3f& normal, const Vector2f& uv)
			: position(position), normal(normal), uv(uv)
		{
		}
	};

} // namespace jackal

#endif//__JACKAL_VERTEX_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Vertex_t
/// @ingroup rendering
///
/// The jackal::Vertex_t is a basic struct that is basis of every
/// mesh within the application. It defines the meshes position, normals
/// and UV co-ordinates. Due to its simplicity and internal use, an example
/// is not provided and it is not exposed to the lua scripting
/// interface.
///
////////////////////////////////////////////////////////////