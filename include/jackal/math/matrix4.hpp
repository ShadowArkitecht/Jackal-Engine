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
#include <jackal/math/vector3.hpp> // Used for positioning.
#include <jackal/math/vector4.hpp> // Retrieving and setting rows and columns.

namespace jackal
{
	class Matrix4 final
	{
	public:
		//====================
		// Member variables
		//====================
		float m[4][4]; ///< Individual elements of the matrix.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Matrix4 object.
		/// 
		/// The default constructor for the Matrix4 object will initialise
		/// all of the elements to the identity matrix, which is a default matrix
		/// that will apply no translations of rotations.
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
		/// @param matrix The matrix to be multiply the Matrix4 object with.
		///
		/// @returns A Matrix4 object with the result of the multiplication.
		///
		////////////////////////////////////////////////////////////
		Matrix4 operator*(const Matrix4& matrix) const;

		////////////////////////////////////////////////////////////
		/// @brief Performs a member-wise multiplication of two matrices.
		///
		/// Multiplication is applied between two different matrices with
		/// the result being assigned to this Matrix4. It is important
		/// to remember that matrices are non-communative.
		///
		/// @param matrix The matrix to be multiply the Matrix4 object with.
		///
		/// @returns A reference to this Matrix4 object after multiplication.
		///
		////////////////////////////////////////////////////////////
		const Matrix4& operator*=(const Matrix4& matrix);
		
		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the row of the Matrix4 at the specified index.
		/// 
		/// Each matrix is made up 4x4 elements of floats, this method will retrieve
		/// a row of elements and construct them into a Vector4f. If the index specified
		/// is greater than 3, an empty Vector4f will be returned.
		///
		/// @param index     The row index.
		///
		/// @retval Vector4f A Vector4 containing the information of the Matrix4 row.
		///
		////////////////////////////////////////////////////////////
		Vector4f getRow(unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the row of the Matrix4 at the specified index.
		/// 
		/// Each element can be changed individually, however this method
		/// can be used for conveniently altering an entire row.
		///
		/// @param index The row index.
		/// @param m1    The first new element of the row.
		/// @param m2    The second new element of the row.
		/// @param m3    The third new element of the row.
		/// @param m4    The fourth new element of the row.
		///
		////////////////////////////////////////////////////////////
		void setRow(unsigned int index, float m1, float m2, float m3, float m4);

		////////////////////////////////////////////////////////////
		/// @brief Sets the row of the Matrix4 at the specified index.
		/// 
		/// Each element can be changed individually, however this method
		/// can be used for conveniently altering an entire row.
		///
		/// @param index The row index.
		/// @param row   The new row to insert.
		///
		////////////////////////////////////////////////////////////		
		void setRow(unsigned int index, const Vector4f& row);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the column of the Matrix4 at the specified index.
		/// 
		/// Each matrix is made up 4x4 elements of floats, this method will retrieve
		/// a column of elements and construct them into a Vector4f. If the index specified
		/// is greater than 3, an empty Vector4f will be returned.
		///
		/// @param index     The column index.
		///
		/// @retval Vector4f A Vector4 containing the information of the Matrix4 row.
		///
		////////////////////////////////////////////////////////////
		Vector4f getColumn(unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the column of the Matrix4 at the specified index.
		/// 
		/// Each element can be changed individually, however this method
		/// can be used for conveniently altering an entire column.
		///
		/// @param index The column index.
		/// @param m1    The first new element of the column.
		/// @param m2    The second new element of the column.
		/// @param m3    The third new element of the column.
		/// @param m4    The fourth new element of the column.
		///
		////////////////////////////////////////////////////////////
		void setColumn(unsigned int index, float m1, float m2, float m3, float m4);

		////////////////////////////////////////////////////////////
		/// @brief Sets the column of the Matrix4 at the specified index.
		/// 
		/// Each element can be changed individually, however this method
		/// can be used for conveniently altering an entire column.
		///
		/// @param index  The column index.
		/// @param column The new column to insert.
		///
		////////////////////////////////////////////////////////////		
		void setColumn(unsigned int index, const Vector4f& column);

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the roll rotation matrix.
		///
		/// The roll rotation matrix is used to manipulate and rotate
		/// matrix on the "x" axis of the matrix. When multiplied against
		/// another matrix, it will give the appearance of an object rotating.
		///
		/// @param degrees   The number of degrees to rotate the matrix by.
		///
		/// @returns The roll rotation matrix.
		///
		////////////////////////////////////////////////////////////		
		static Matrix4 roll(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the pitch rotation matrix.
		///
		/// The pitch rotation matrix is used to manipulate and rotate
		/// matrix on the "y" axis of the matrix. When multiplied against
		/// another matrix, it will give the appearance of an object rotating.
		///
		/// @param degrees   The number of degrees to rotate the matrix by.
		///
		/// @returns The pitch rotation matrix.
		///
		////////////////////////////////////////////////////////////		
		static Matrix4 pitch(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the yaw rotation matrix.
		///
		/// The yaw rotation matrix is used to manipulate and rotate
		/// matrix on the "z" axis of the matrix. When multiplied against
		/// another matrix, it will give the appearance of an object rotating.
		///
		/// @param degrees   The number of degrees to rotate the matrix by.
		///
		/// @returns The yaw rotation matrix.
		///
		////////////////////////////////////////////////////////////		
		static Matrix4 yaw(float degrees);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves and constructs a translation matrix.
		///
		/// A translation matrix is a simple matrix where the translation
		/// column of the matrix has been altered with the passed in values.
		/// When a matrix is multiplied by the translation matrix, it will
		/// give the illusion of movement.
		///
		/// @param x  The new x translation of the matrix.
		/// @param y  The new y translation of the matrix.
		/// @param z  The new z translation of the matrix.
		///
		/// @returns  The translation matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 translation(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves and constructs a translation matrix.
		///
		/// A translation matrix is a simple matrix where the translation
		/// column of the matrix has been altered with the passed in values.
		/// When a matrix is multiplied by the translation matrix, it will
		/// give the illusion of movement.
		///
		/// @param position The new translation of the matrix.
		///
		/// @returns  The translation matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 translation(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// @brief Rotates a matrix by the specified x, y and z values.
		///
		/// This method is a convenience method that combines the yaw, pitch
		/// and roll rotation matrices and utilises them to rotate the matrix
		/// by the specified amount on the axis'.
		///
		/// @param x The x amount to rotate the matrix by.
		/// @param y The y amount to rotate the matrix by.
		/// @param z The z amount to rotate the matrix by.
		///
		/// @returns The rotated matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Rotates a matrix by the specified rotation vector.
		///
		/// This method is a convenience method that combines the yaw, pitch
		/// and roll rotation matrices and utilises them to rotate the matrix
		/// by the specified amount on the axis'.
		///
		/// @param rotation The vector to rotate the matrix by.
		///
		/// @returns The rotated matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(const Vector3f& rotation);

		////////////////////////////////////////////////////////////
		/// @brief Scale a matrix by the specified x, y and z values.
		///
		/// A scale matrix is a simple matrix that when multiplied against,
		/// will scale a matrix by the amount specified on the different axis'.
		/// This method is used to scale non-uniformly.
		///
		/// @param x The amount to scale on the x axis.
		/// @param y The amount to scale on the y axis.
		/// @param z The amount to scale on the z axis.
		///
		/// @returns The scale matrix.
		/// 
		////////////////////////////////////////////////////////////
		static Matrix4 scale(float x, float y, float z);

		////////////////////////////////////////////////////////////
		/// @brief Scale a matrix by the specified vector.
		///
		/// A scale matrix is a simple matrix that when multiplied against,
		/// will scale a matrix by the amount specified on the different axis'.
		/// This method is used to scale non-uniformly.
		///
		/// @param The vector to scale the matrix by.
		///
		/// @returns The scale matrix.
		/// 
		////////////////////////////////////////////////////////////
		static Matrix4 scale(const Vector3f& scale);

		////////////////////////////////////////////////////////////
		/// @brief Scale a matrix uniformly by the specified amount.
		///
		/// A scale matrix is a simple matrix that when multiplied against,
		/// will scale a matrix by the amount specified on the different axis'.
		/// This method is used to scale all axis by a uniform value.
		///
		/// @param The uniform scale value.
		///
		/// @returns The uniform scale matrix.
		/// 
		////////////////////////////////////////////////////////////
		static Matrix4 scale(float u);

		////////////////////////////////////////////////////////////
		/// @brief Constructs an orthographic matrix.
		///
		/// An orthographic matrix differs from a perspective matrix
		/// in that everything projected into a scene appears on the same
		/// z-plane, objects lack any sense of depth of field. An orthographic
		/// matrix is useful for projecting elements onto a screen in absolute
		/// co-ordinates (such as a UI).
		///
		/// @param left   The left most section of the projection.
		/// @param right  The right most section of the projection.
		/// @param top    The top most section of the projection.
		/// @param bottom The bottom most section of the projection.
		/// @param near   Near clipping plane.
		/// @param far    Far clipping plane.
		///
		/// @returns An orthographic matrix.
		///
		////////////////////////////////////////////////////////////	
		static Matrix4 orthographic(float left, float right, float top, float bottom, float near, float far);
		
		////////////////////////////////////////////////////////////
		/// @brief Constructs a perspective matrix.
		///
		/// A perspective matrix is a type of projection matrix that
		/// makes the objects within a scene appear as it they are in local 
		/// perspective. The perspective can be more commonly described
		/// as the natural way a world is viewed. With objects further away
		/// appearing smaller.
		///
		/// @param fov   The field of view (how much can be seen at one time).
		/// @param ratio The aspect ratio of the current window.
		/// @param near  The near clipping plane.
		/// @param far   The far clipping plane.
		///
		/// @returns The perspective matrix.
		///
		//////////////////////////////////////////////////////////// 		
		static Matrix4 perspective(float fov, float ratio, float near, float far);

		////////////////////////////////////////////////////////////
		/// @brief Constructs a basic view matrix.
		///
		/// The view matrix can be regarded as the "view" or "camera"
		/// into the game world, combined with a translation matrix it can
		/// give the appearance of movement around a game world. The view must
		/// be combined with a perspective or orthographic matrix for
		/// correct projection.
		///
		/// @param forward The direction to point the view in.
		/// @param up      The current up vector of the view.
		///
		/// @returns       The Matrix4 object constructed as a view matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 view(const Vector3f& forward, const Vector3f& up);

		//====================
		// Properties
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves a Matrix4 object as an identity matrix.
		///
		/// The identity matrix is the default state of a Matrix4 object,
		/// if any translations or rotations are applied to this matrix,
		/// end result will be unchanged.
		///
		/// @returns The identity matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 identity();

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the Matrix4 object as a zero-ed matrix.
		///
		/// A zero-ed matrix is a matrix constructed of nothing but
		/// zero values. It serves no practible purpose.
		///
		/// @returns A matrix with all elements set to 0.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 zero();
	};

} // namespace jackal

#endif//__JACKAL_MATRIX4_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Matrix4
/// @ingroup math
///
/// The jackal::Matrix4 is the underlying rotational matrix that
/// the Jackal Engine utilises. The matrices are used to rotate
/// objects within GLSL shaders and for communication with OpenGL.
/// 
/// The matrices are never directed accessed by the user, instead
/// all rotation within the application utilises Quaternions, which
/// are converted into matrices before shader application. Although the
/// matrices do not need to be directly used, they are exposed to the
/// lua scripting interface for additional behaviour.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create a matrix object.
/// jackal::Matrix4 matrix;
///
/// // Set the matrix to equal a translation, rotation and scale.
/// matrix *= Matrix4::scale(Vector3f::one());
/// // Rotates the matrix 50 degrees on the y axis.
/// matrix *= Matrix4::rotation(Vector3f(0.0f, 50.0f, 0.0f));
///
/// matrix *= Matrix4::translation(Vector3f(0.0f, 0.0f, 7.0f);
/// @endcode
///
/// Lua Code example:
/// @code 
/// -- Create a matrix object.
/// local matrix = Matrix4()
///
/// -- Set the matrix to equal a translation, rotation and scale.
/// matrix = matrix * Matrix4::scale(Vector3.one())
/// -- Rotates the matrix 50 degrees on the y axis.
/// matrix = matrix * Matrix4.rotation(Vector3(0.0, 50.0, 0.0))
///
/// matrix = matrix * Matrix4.translation(Vector3(0.0, 0.0, 7.0))
/// @endcode
///
////////////////////////////////////////////////////////////