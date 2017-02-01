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

#ifndef __JACKAL_VECTOR3_HPP__
#define __JACKAL_VECTOR3_HPP__

//====================
// C++ includes
//====================
#include <cmath>		// Needed for square root and trigonometry.
#include <algorithm>	// Finding minimum and maximum values.
#include <iostream>     // operator<< overloading.

namespace jackal
{
	template <typename T>
	class Vector3 final
	{
	public:
		//====================
		// Member Variables
		//====================
		T x;	///< The x (right) value.
		T y;	///< The y (up) value.
		T z;	///< The z (forward) value.

	public:
		//====================
		// Ctor and Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Vector3 object.
		///
		/// When the default constructor for the Vector3 object is called, 
		/// it sets the x, y and z values to 0.
		///
		////////////////////////////////////////////////////////////
		explicit Vector3(void);

		////////////////////////////////////////////////////////////
		/// @brief Constructor for a Vector3 object with defined x, y and z values.
		///
		/// This constructor is used to set the three values of the
		/// Vector3 objects to user defined amounts.
		///
		/// @param x	The x value of the Vector3 object.
		///	@param y	The y value of the Vector3 object.
		///	@param z	The y value of the Vector3 object.
		///
		////////////////////////////////////////////////////////////
		explicit Vector3(T x, T y, T z);

		////////////////////////////////////////////////////////////
		/// @brief Constructor for a Vector3 object, generating values from anoher Vector3.
		///
		/// As there are numerous different type definitions and Vector3
		/// types, this constructor will convert from one Vector3 type to another.
		///
		/// @param vector	The different Vector3 type.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector3(const Vector3<U>& vector);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Vector3 object.
		////////////////////////////////////////////////////////////
		~Vector3(void) = default;

		//====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector3 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and return the result as a new Vector3 object.
		///
		/// @param vector   The Vector3 object to add.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator+(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector3 and a value.
		///
		/// This operator performs a member-wise addition of a Vector3
		/// and a value and returns the result as a new Vector3 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator+(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector3 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and return the result as a new Vector3 object.
		///
		/// @param vector   The vector to subtract.
		///
		/// @returns        A new Vector3 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector3 and a value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and a value and returns the result as a new Vector3 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A new Vector3 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector3 objects.
		///
		/// This operator performs a member-wise multiplication of two
		/// vectors and return the result as a new Vector3 object.
		///
		/// @param vector   The vector to multiply.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator*(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector3 and a value.
		///
		/// This operator performs a member-wise multiplication of a Vector3
		/// and a value and returns the result as a new Vector3 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator*(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector3 objects.
		///
		/// This operator performs a member-wise division of two
		/// vectors and return the result as a new Vector3 object.
		///
		/// @param vector   The vector to divide.
		///
		/// @returns        A new Vector3 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator/(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector3 and a value.
		///
		/// This operator performs a member-wise division of a Vector3
		/// and a value and returns the result as a new Vector3 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A new Vector3 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator/(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector3 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// @param vector   The vector to add.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator+=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector3 and value.
		///
		/// This operator performs a member-wise addition of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator+=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector3 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// @param vector   The vector to subtract.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator-=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector3 and value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator-=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector3 objects.
		///
		/// This operator performs a member-wise multiplication of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// @param vector   The vector to multiply.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator*=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector3 and value.
		///
		/// This operator performs a member-wise multiplication of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator*=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector3 objects.
		///
		/// This operator performs a member-wise division of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// @param vector   The vector to divide.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator/=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector3 and value.
		///
		/// This operator performs a member-wise division of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator/=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are the same, the Vector3 objects are equal.
		///
		/// @param vector   The Vector3 object to compare against.
		///
		/// @returns        True if the Vector3 objects are the same.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Non-Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are not the same, the Vector3 object are not equal.
		///
		/// @param vector   The Vector3 object to compare against.
		///
		/// @returns        True if the Vector3 objects are not the same.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Unary operation on a Vector3 object.
		///
		/// This will invert the x and y components from positive to negative
		/// values, and vice-versa.
		///
		/// @returns    An inverted Vector3 object.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Overload the output stream operator to print a Vector3
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// vector to the console window. The matrix will be printed in the
		/// following format: ( x, y, z ).
		///
		/// @param os       The output stream to stream into.
		/// @param vector   The vector to print to the console window.
		///
		/// @returns        The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Vector3& vector)
		{
			return os << "[ " << vector.x << ", " << vector.y << ", " << vector.z << " ]";
		}

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Calculates the squared length of the Vector3 object.
		///
		/// @return		The squared length of the Vector3.
		///
		////////////////////////////////////////////////////////////
		T magnitudeSqr(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the length of the Vector3 object.
		///
		/// @return		The length of the Vector3.
		///
		////////////////////////////////////////////////////////////
		T magnitude(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the unit length of the Vector3 object.
		///
		/// @return		The normalised Vector3 object.
		///
		////////////////////////////////////////////////////////////
		Vector3 normalised(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculate the cosine angle between two Vector3 objects.
		///
		/// The dot product is the value equal to the magnitudes/length of
		/// the two Vector3 objects multiplied together and then multiplied by the
		/// cosine of the angle between them.
		///
		/// @param u	The first vector.
		/// @param v	The second vector.
		///
		/// @return		The cosine angle between two Vector3 objects/
		///
		////////////////////////////////////////////////////////////
		static T dot(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// @brief Calculate the cross product of two Vector3 object.
		///
		/// The cross product is a mathematical function which uses two
		/// Vector3 objects and results in a third vector which is perpendicular
		/// to the Vector3 objects.
		///
		/// @param u	The first vector.
		/// @param v	The second vector.
		///
		/// @return		The Vector3 perpendicular to the two Vector3 objects.
		///
		////////////////////////////////////////////////////////////
		static Vector3 cross(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// @brief Gets the (degrees) angle between two Vector3 objects.
		///
		/// This will calculate the angle between two different Vector3 objects. The angle
		/// will be returned in degrees.
		///
		/// @param from		The vector where the angle measurement will begin.
		/// @param to		The vector where the angle measurement will end.
		///
		/// @return			The angle between the Vector3 objects in degrees.
		///
		////////////////////////////////////////////////////////////
		static T angle(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the squared euclidean distance between two different Vector3 objects.
		///
		/// @param from		The starting vector.
		/// @param to		The vector distance to measure.
		///
		/// @return			The squared euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distanceSqr(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the euclidean distance between two different Vector3 objects.
		///
		/// @param from		The starting vector.
		/// @param to		The vector distance to measure.
		///
		/// @return			The euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distance(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// @brief Gets the minimum values of two Vector3 objects.
		///
		/// This will get the lowest member values of the two Vector3
		/// objects and create a new Vector3 constructed of the low
		/// values.
		///
		/// @param u		The first vector.
		/// @param v		The second vector.
		///
		/// @return			The minimum x, y and z values of the two Vector3 objects.
		///
		////////////////////////////////////////////////////////////
		static Vector3 minimum(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// @brief Gets the maximum values of two Vector3 objects.
		///
		/// This will get the highest member values of the two Vector3
		/// objects and create a new Vector3 constructed of the high
		/// values.
		///
		/// @param u		The first vector.
		/// @param v		The second vector.
		///
		/// @return			The maximum x, y and z values of the two Vector3 objects.
		///
		////////////////////////////////////////////////////////////
		static Vector3 maximum(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// @brief Moves a Vector3 towards the target.
		///
		/// The method will return a Vector3 moving from the current
		/// Vector3 towards the target by the specified speed.
		///
		/// @param current	The current Vector3 to move from.
		/// @param target	The Vector3 to move towards.
		/// @param speed	The speed of movement.
		///
		/// @return			The moved Vector3.
		///
		////////////////////////////////////////////////////////////
		static Vector3 moveTowards(const Vector3& current, const Vector3& target, T speed);

		////////////////////////////////////////////////////////////
		/// @brief Vector3 linear interpolation.
		///
		/// Linearly interpolates between the current Vector3 and target
		/// by the specfied speed.
		///
		/// @param current	The vector being linearly interpolated from.
		/// @param target	The vector linearly interpolated towards.
		/// @param speed	The speed of the interpolation.
		///
		/// @return			The interpolated Vector3.
		///
		////////////////////////////////////////////////////////////
		static Vector3 lerp(const Vector3& current, const Vector3& target, T speed);

		//====================
		// Properties
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector3 to ( 0, 0, 0 ).
		///
		/// @return		A Vector3 object equal to ( 0, 0, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector3 zero(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector3 to ( 1, 1, 1 ).
		///
		/// @return		A Vector3 object equal to ( 1, 1, 1 ).
		///
		////////////////////////////////////////////////////////////
		static Vector3 one(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector3 to ( 1, 0, 0 ).
		///
		/// @return		A Vector3 object equal to ( 1, 0, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector3 right(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector3 to ( 0, 1, 0 ).
		///
		/// @return		A Vector3 object equal to ( 0, 1, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector3 up(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector3 to ( 0, 0, 1 ).
		///
		/// @return		A Vector3 object equal to ( 0, 0, 1 ).
		///
		////////////////////////////////////////////////////////////
		static Vector3 forward(void);
	};

	//====================
	// Additional includes
	//====================
	#include <jackal/math/vector3.inl>			// Method definitions.

	//====================
	// Type definitions
	//====================
	typedef Vector3<unsigned int> Vector3u;		///< Type definition for a Vector3 made up of unsigned integers.
	typedef Vector3<int>          Vector3i;		///< Type definition for a Vector3 made up of integers.
	typedef Vector3<float>        Vector3f;		///< Type definition for a Vector3 made up of floats.
	typedef Vector3<double>       Vector3d;		///< Type definition for a Vector3 made up of doubles.

} // namespace jackal

#endif//__JACKAL_VECTOR3_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Vector3
/// @ingroup math
///
/// jackal::Vector3 is a templated class responsible for
/// all Vector based mathematics in 3 dimensions. It is commonly
/// used throughout the engine for a variety of different tasks,
/// such as placement of game objects and vertex manipulation.
///
/// jackal::Vector3 also contains the most common mathematics
/// and algorithms associated with vectors, such as the dot 
/// product and normalisation. As the mathematics is used commonly
/// throughout the application, it is also exposed to the lua 
/// scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create two vectors to calculate the cross product.
/// Vector3f v1 = Vector3f::up();
/// Vector3f v2 = Vector3f::right();
///
/// // Calculate the cross product.
/// float cross = Vector3f::cross(up, right);
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create two vectors to calculate the cross product.
/// local v1 = Vector3.up()
/// local v2 = Vector3.right()
///
/// // Calculate the dot product.
/// local dot = Vector3.dot(up, right)
/// @endcode
///
////////////////////////////////////////////////////////////