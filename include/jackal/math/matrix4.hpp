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

#ifndef __JACKAL_MATRIX4_HPP__
#define __JACKAL_MATRIX4_HPP__

//====================
// Jackal includes
//====================
#include <jackal/math/vector3.hpp> // Using vectors for setting translations and rotation.
#include <jackal/math/vector4.hpp> // Setting rows and columns.

namespace jackal
{
	class Matrix4 final
	{
	public:
		//====================
		// Member variables
		//====================
		float m[16]; ///< Individual elements of the matrix object.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Matrix4 Object.
		///
		/// When the default constructor of Matrix4 is used to instantiate
		/// the object, it is set to the identity matrix.
		///
		/// [ 1, 0, 0, 0 ]
		/// [ 0, 1, 0, 0 ]
		/// [ 0, 0, 1, 0 ]
		/// [ 0, 0, 0, 1 ]
		///
		////////////////////////////////////////////////////////////
		explicit Matrix4();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Matrix4 object.
		////////////////////////////////////////////////////////////
		~Matrix4() = default;

		//====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Performs a member-wise multiplication of two matrices.
		///
		/// Multiplication is applied between two different matrices with
		/// the result being assigned to a new Matrix4 object. It is important
		/// to remember that matrices are non-communative.
		///
		/// @param matrix    The matrix to be multiply against.
		///
		/// @returns         A Matrix4 result of the multiplication.
		///
		////////////////////////////////////////////////////////////
		Matrix4 operator*(const Matrix4& matrix) const;

		////////////////////////////////////////////////////////////
		/// @brief Performs a member-wise multiplication of two matrices.
		///
		/// Multiplication is applied between two different matrices with
		/// the result being assigned to this Matrix4. It is important
		/// to remember that matrices are non-communative. This method will
		/// return a reference to the current object.
		///
		/// @param matrix       The matrix to be multiply against.
		///
		/// @returns            A reference to this Matrix4 object.
		///
		////////////////////////////////////////////////////////////
		const Matrix4& operator*=(const Matrix4& matrix);

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the column of the Matrix4 at the specified index.
		///
		/// When a column is retrieved from the matrix, it will return the result
		/// as a 4 dimensional vector object.
		///
		/// @param index    The column index.
		///
		/// @returns        A Vector4 containing the information of the Matrix4 column.
		///
		////////////////////////////////////////////////////////////
		Vector4f getCol(unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the column of the Matrix4 at the specified index.
		///
		/// @param index    The column index.
		/// @param col      The Vector4f to set the column to.
		///
		////////////////////////////////////////////////////////////
		void setCol(unsigned int index, const Vector4f& col);

		////////////////////////////////////////////////////////////
		/// @brief Sets the column of the Matrix4 at the specified index.
		///
		/// @param index    The column index.
		/// @param m1       The first element of the column.
		/// @param m2       The second element of the column.
		/// @param m3       The third element of the column.
		/// @param m4       The fourth element of the column.
		///
		////////////////////////////////////////////////////////////
		void setCol(unsigned int index, float m1, float m2, float m3, float m4);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the row of the Matrix4 at the specified index.
		///
		/// When a row is retrieved from the matrix, it will return the result
		/// as a 4 dimensional vector object.
		///
		/// @param index    The row index.
		///
		/// @returns        A Vector4 containing the information of the Matrix4 row.
		///
		////////////////////////////////////////////////////////////
		Vector4f getRow(unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the row of the Matrix4 at the specified index.
		///
		/// @param index    The row index.
		/// @param row      The Vector4f to set the row to.
		///
		////////////////////////////////////////////////////////////
		void setRow(unsigned int index, const Vector4f& row);

		////////////////////////////////////////////////////////////
		/// @brief Sets the row of the Matrix4 at the specified index.
		///
		/// @param index    The row index.
		/// @param m1       The first element of the row.
		/// @param m2       The second element of the row.
		/// @param m3       The third element of the row.
		/// @param m4       The fourth element of the row.
		///
		////////////////////////////////////////////////////////////
		void setRow(unsigned int index, float m1, float m2, float m3, float m4);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Constructs a translation Matrix4 object.
		///
		/// Constructs an identity matrix and then sets the translation column
		/// to the position parameter. When a matrix is multiplied by the
		/// translation matrix, it will alter the object's position in 2D space.
		///
		/// [ 1 0 0 position.x ]
		/// [ 0 1 0 position.y ]
		/// [ 0 0 1 position.z ]
		/// [ 0 0 0 1          ]
		///
		/// @param position The position to set the translation matrix to.
		/// @returns        A translation matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 translation(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a translation Matrix4 object.
		///
		/// Constructs an identity matrix and then sets the translation column
		/// to the position parameter. When a matrix is multiplied by the
		/// translation matrix, it will alter the object's position in 2D space.
		///
		/// [ 1 0 0 x ]
		/// [ 0 1 0 y ]
		/// [ 0 0 1 z ]
		/// [ 0 0 0 1 ]
		///
		/// @param x The x position to set the translation matrix to.
		/// @param y The y position to set the translation matrix to.
		/// @param z The z position to set the translation matrix to.
		///
		/// @returns A translation matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 translation(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a roll rotation matrix.
		///
		/// Constructs a roll rotation matrix with the applied number of degrees.
		/// When a matrix is multiplied by the roll rotation matrix, it will alter
		/// the object's rotation on the local x axis.
		///
		/// [ 1 0          0           0 ]
		/// [ 0 cos(theta) -sin(theta) 0 ]
		/// [ 0 sin(theta)  cos(theta) 0 ]
		/// [ 0 0          0           1 ]
		///
		/// \param degrees		The degrees to apply to the rotation matrix.
		///
		/// \retval Matrix4		The roll rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 roll(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a pitch rotation matrix
		///
		/// Constructs a pitch rotation matrix with the applied number of degrees.
		/// When a matrix is multiplied by the pitch rotation matrix, it will alter
		/// the object's rotation on the local y axis.
		///
		/// [  cos(theta)  0 sin(theta) 0 ]
		/// [  0           1 0          0 ]
		/// [ -sin(theta)  0 cos(theta) 0 ]
		/// [  0           0 0          1 ]
		///
		/// @param degrees The degrees to apply to the rotation matrix.
		/// @returns       The pitch rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 pitch(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a yaw rotation matrix.
		///
		/// Constructs a yaw rotation matrix with the applied number of degrees.
		///	When a matrix is multiplied by the yaw rotation matrix, it will alter
		/// the object's rotation on the local z axis.
		///
		/// [ cos(theta) -sinf(theta) 0 0 ]
		/// [ sin(theta)  cosf(theta) 0 0 ]
		/// [ 0           0           1 0 ]
		/// [ 0           0           0 1 ]
		///
		/// @param degrees The degrees to apply to the rotation matrix.
		///
		/// @returns       The yaw rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 yaw(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Sets the x, y, and z rotation of a Matrix4 object.
		///
		/// Convenience method for quickly setting the x, y and z rotation of a
		/// Matrix4 object. The corresponding components of the rotation Vector set 
		/// the roll, yaw and pitch rotational degrees respectively.
		///
		/// @param rotation     The rotation to apply to the Matrix4 object.
		///
		/// @returns            The rotated matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(const Vector3f& rotation);

		////////////////////////////////////////////////////////////
		/// @brief Sets the x, y, and z rotation of a Matrix4 object.
		///
		/// Convenience method for quickly setting the x, y and z rotation of a
		/// Matrix4 object. The corresponding components of the rotation Vector set 
		/// the roll, yaw and pitch rotational degrees respectively.
		///
		/// @param x   The x rotation to apply to the Matrix4 object.
		/// @param y   The y rotation to apply to the Matrix4 object.
		/// @param z   The z rotation to apply to the Matrix4 object.
		///
		/// @returns   The rotated matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a scale Matrix4 object.
		///
		/// Creates a indentity matrix and then scales the matrix on
		/// the x, y and z axis by using the members from the corresponding
		/// scale Vector parameter.
		///
		/// [ scale.x 0       0       0 ]
		/// [ 0       scale.y 0       0 ]
		/// [ 0       0       scale.z 0 ]
		/// [ 0       0       0       1 ]
		///
		/// @param scale The vector to scale the matrix by.
		///
		/// @returns     A Matrix4 scale object.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 scale(const Vector3f& scale);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a scale Matrix4 object.
		///
		/// Creates a indentity matrix and then scales the matrix on
		/// the x, y and z axis by using the members from the corresponding
		/// parameters.
		///
		/// [ x 0 0 0 ]
		/// [ 0 y 0 0 ]
		/// [ 0 0 z 0 ]
		/// [ 0 0 0 1 ]
		///
		/// @param x    The x value to scale the matrix by.
		/// @param y    The y value to scale the matrix by.
		/// @param z    The z value to scale the matrix by.
		///
		/// @returns    A Matrix4 scale object.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 scale(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a scale Matrix4 object.
		///
		/// Creates a indentity matrix and then scales the matrix on
		/// the x, y and z axis by a uniform scale value.
		///
		/// [ scale 0     0     0 ]
		/// [ 0     scale 0     0 ]
		/// [ 0     0     scale 0 ]
		/// [ 0     0     0     1 ]
		///
		/// @param scale The uniform value to scale the matrix by.
		///
		/// @returns     A Matrix4 scale object.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 scale(float scale);

		//====================
		// Properties
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates and returns an identity matrix.
		///
		/// An identity matrix is the default state for a Matrix4 object.
		/// If a matrix is multiplied by an identity matrix, it will remain
		/// the same.
		///
		/// @returns The identity matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 identity();
	};

} // namespace jackal

#endif//__JACKAL_MATRIX4_HPP__

////////////////////////////////////////////////////////////
/// @class jackal::Matrix4
/// @ingroup math
///
/// The jackal::Matrix4 is the underlying rotational matrices that
/// the Jackal Engine utilises. The matrices are used to rotate
/// objects within the GLSL shaders and for communication with OpenGL.
/// 
/// The matrices are never directed accessed by the user, instead
/// all rotation within the application utilises Quaternions, which
/// are converted into matrices before glsl application.
///
/// Although not externally used, its behavior is still exposed
/// to the lua scripting interface for additional use.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a matrix object.
/// Matrix4 matrix;
///
/// // Set the matrix to equal a random translation, rotation and scale.
/// matrix *= Matrix4::scale(Vector3f::one());
/// // Rotates the matrix 50 degrees on the y axis.
/// matrix *= Matrix4::rotation(0.0f, 50.0f, 0.0f);
/// // Translate the matrix.
/// matrix *= Matrix4f::translation(0.0f, 0.0f, 7.0f);
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create a matrix object
/// local matrix = Matrix4()
///
///  -- Set the matrix to equal a random translaction, rotation and scale.
/// matrix = matrix * Matrix4.scale(Vector3.one())
/// -- Rotates the matrix 50 degrees on the y axis.
/// matrix = matrix * Matrix4.rotation(0.0, 50.0, 0.0)
/// -- Translate the matrix.
/// matrix = matrix * Matrix4.translation(0.0, 0.0, 7.0)
/// @endcode
///
////////////////////////////////////////////////////////////