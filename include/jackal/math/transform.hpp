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

#ifndef __JACKAL_TRANSFORM_HPP__
#define __JACKAL_TRANSFORM_HPP__

//====================
// Jackal includes
//====================
#include <jackal/math/vector3.hpp> // The position of the Transform.
#include <jackal/math/matrix4.hpp> // Model matrix of the transform.

namespace jackal
{
	class Transform final 
	{
	private:
		//====================
		// Member variables
		//====================
		Vector3f m_position;   ///< The position of the Transform.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Transform object.
		///
		/// The default constructor will set the position to the centre
		/// of the scene, the rotation to an identity matrix and the scale
		/// to (1.0, 1.0, 1.0).
		///
		////////////////////////////////////////////////////////////
		explicit Transform();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Transform object.
		////////////////////////////////////////////////////////////
		~Transform() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the position of the Transform object.
		///
		/// The position controls the location of the Transform and the
		/// subsequent object within the 3D scene. Manipulating the position
		/// will change the location of the entity.
		///
		/// @returns The position of the Transform object.
		///
		////////////////////////////////////////////////////////////
		Vector3f getPosition() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the position of the Transform object.
		///
		/// The position controls the location of the Transform and the
		/// subsequent object within the 3D scene. Manipulating the position
		/// will change the location of the entity.
		///
		/// @param x The new x position of the Transform object.
		/// @param y The new y position of the Transform object.
		/// @param z The new z position of the Transform object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Sets the position of the Transform object.
		///
		/// The position controls the location of the Transform and the
		/// subsequent object within the 3D scene. Manipulating the position
		/// will change the location of the entity.
		///
		/// @param position The position of the Transform object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the model transformation of the object.
		///
		/// The model transformation is a matrix representing the local
		/// position, rotation and scale of the object within 3D space.
		/// Combined with the perspective and view matrices, it will display
		/// an object correctly within a 3D scene.
		///
		////////////////////////////////////////////////////////////
		Matrix4 getTransformation() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Translates the position of the Transform by the specified amounts.
		///
		/// The translate method is a simple method that will increment
		/// the position of the Transform object by the specified values.
		///
		/// @param x The x amount to translate the Transform by.
		/// @param y The y amount to translate the Transform by.
		/// @param z The z amount to translate the Transform by.
		///
		////////////////////////////////////////////////////////////
		void translate(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Translates the position of the Transform by the specified amounts.
		///
		/// The translate method is a simple method that will increment
		/// the position of the Transform object by the specified values.
		///
		/// @param translation The amount to translate the Transform by.
		///
		////////////////////////////////////////////////////////////
		void translate(const Vector3f& translation);
	};

} // namespace jackal

#endif//__JACKAL_TRANSFORM_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Transform
/// @ingroup math
///
/// The jackal::Transform is a simple wrapper class that encapsulates
/// all of the behaviour for translation, rotation and scale. The Transform
/// is attached to the Camera and all of the entities within the application.
///
/// The jackal::Transform includes methods for easily translating,
/// rotating and scaling the transform of the entity. Due to the common
/// use of the class, it is exposed for use with the lua scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a transform object.
/// Transform transform;
/// // Set the position and then translate the object.
/// transform.setPosition(0.0f, 0.0f, 10.0f);
/// transform.translate(Vector3f::one() * 5.0f * Time::getDeltaTime());
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create a transform object.
/// local transform = Transform()
/// -- Set the position and then translate the object.
/// transform.position = Vector3(0.0, 0.0, 10.0)
/// transform:translate(Vector3.one() * 5.0 * Time.get_deltatime())
/// @endcode
///
////////////////////////////////////////////////////////////