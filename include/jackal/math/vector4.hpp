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

#ifndef __JACKAL_VECTOR4_HPP__
#define __JACKAL_VECTOR4_HPP__

//====================
// C++ includes
//====================
#include <iostream> // Operator overloading for streams.
#include <cmath>    // Math operations.

namespace jackal
{
	template <typename T>
	class Vector4 final
	{
	public:
		//====================
		// Member variables
		//====================
		T x;	///< The x value.
		T y;	///< The y value.
		T z;	///< The z value.
		T w;	///< The w value.

	public:
		//====================
		// Ctor and Dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Vector4 object. 
		///
		/// The default constructor for the Vector4 object initialises
		/// all of the member variables to 0.
		///
		////////////////////////////////////////////////////////////
		explicit Vector4();

		////////////////////////////////////////////////////////////
		/// @brief Constructs a Vector4 object with defined x, y, z and w values.
		///
		/// This constructor initialises the elements of a Vector4 object
		/// to user defined values.
		///
		/// @param x    The x value of the Vector4 object.
		///	@param y    The y value of the Vector4 object.
		/// @param z    The z value of the Vector4 object.
		///	@param w    The w value of the Vector4 object.
		///
		////////////////////////////////////////////////////////////
		explicit Vector4(const T x, const T y, const T z, const T w);

		////////////////////////////////////////////////////////////
		/// @brief Constructor for a Vector4 object, generating values from anoher Vector4.
		///
		/// As there are numerous different type definitions and Vector4
		/// types, this constructor will convert from one Vector4 type to another.
		///
		/// @param vector	The different Vector4 type.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector4(const Vector4<U>& vector);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Vector4 object.
		////////////////////////////////////////////////////////////
		~Vector4(void) = default;

		//====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector4 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and return the result as a new Vector4 object.
		///
		/// @param vector   The Vector4 object to add.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator+(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector4 and a value.
		///
		/// This operator performs a member-wise addition of a Vector4
		/// and a value and returns the result as a new Vector4 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator+(const T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector4 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and return the result as a new Vector4 object.
		///
		/// @param vector   The Vector4 to subtract.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector4 and a value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and a value and returns the result as a new Vector4 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(const T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector4 objects.
		///
		/// This operator performs a member-wise multiplication of two
		/// vectors and return the result as a new Vector4 object.
		///
		/// @param vector   The Vector4 to multiply.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator*(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector4 and a value.
		///
		/// This operator performs a member-wise multiplication of a Vector4
		/// and a value and returns the result as a new Vector4 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator*(const T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector4 objects.
		///
		/// This operator performs a member-wise division of two
		/// vectors and return the result as a new Vector4 object.
		///
		/// @param vector   The Vector4 to divide.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator/(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector4 and a value.
		///
		/// This operator performs a member-wise division of a Vector4
		/// and a value and returns the result as a new Vector4 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A new Vector4 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator/(const T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector4 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// @param vector   The Vector4 to add.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator+=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector4 and value.
		///
		/// This operator performs a member-wise addition of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator+=(const T value);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector4 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// @param vector   The Vector4 to subtract.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator-=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector4 and value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator-=(const T value);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector4 objects.
		///
		/// This operator performs a member-wise multiplication of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// @param vector   The Vector4 to multiply.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator*=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector4 and value.
		///
		/// This operator performs a member-wise multiplication of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator*=(const T value);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector4 objects.
		///
		/// This operator performs a member-wise division of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// @param vector   The Vector4 to divide.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator/=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector4 and value.
		///
		/// This operator performs a member-wise division of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator/=(const T value);

		////////////////////////////////////////////////////////////
		/// @brief Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are the same, the Vector4 objects are equal.
		///
		/// @param vector   The Vector4 object to compare against.
		///
		/// @returns        True if the Vector4 objects are the same.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Non-Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are not the same, the Vector4 object are not equal.
		///
		/// @param vector   The Vector4 object to compare against.
		///
		/// @returns        True if the Vector4 objects are not the same.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Unary operation on a Vector4 object.
		///
		/// This will invert the x and y components from positive to negative
		/// values, and vice-versa.
		///
		/// @returns    An inverted Vector4 object.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Overload the output stream operator to print a Vector4
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// vector to the console window. The matrix will be printed in the
		/// following format: ( x, y, z, w ).
		///
		/// @param os       The output stream to stream into.
		/// @param vector   The vector to print to the console window.
		///
		/// @returns        The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Vector4& vector)
		{
			return os << "( " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " )";
		}

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Calculates the squared length of the Vector4 object.
		///
		/// @returns    The squared length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitudeSqr(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the length of the Vector4 object.
		///
		/// @returns    The length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitude(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the unit length of the Vector4 object.
		///
		/// A normalised vector is used to represent the direction of the
		/// vector with values ranging from 0 to 1.
		///
		/// @returns    The normalised Vector4 object.
		///
		////////////////////////////////////////////////////////////
		Vector4 normalised(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculate the cosine angle between two Vector4 objects.
		///
		/// The dot product is the value equal to the magnitudes/length of
		/// the two vectors multiplied together and then multiplied by the
		/// cosine of the angle between them.
		///
		/// @param u    The first vector.
		/// @param v    The second vector.
		///
		/// @returns    The cosine angle between two Vector4 objects.
		///
		////////////////////////////////////////////////////////////
		static T dot(const Vector4& u, const Vector4& v);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the squared euclidean distance between two different vectors.
		///
		/// @param from     The starting vector.
		/// @param to       The vector distance to measure.
		///
		/// @returns        The squared euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distanceSqr(const Vector4& from, const Vector4& to);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the euclidean distance between two different vectors.
		///
		/// @param from     The starting vector.
		/// @param to       The vector distance to measure.
		///
		/// @returns        The euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distance(const Vector4& from, const Vector4& to);

		////////////////////////////////////////////////////////////
		/// @brief Gets the minimum values of two Vector4 objects.
		///
		/// This will get the lowest member values of the two Vector
		/// objects and create a new Vector constructed of the low
		/// values.
		///
		/// @param u        The first vector.
		/// @param v        The second vector.
		///
		/// @returns        The minimum x and y values of the two vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector4 minimum(const Vector4& u, const Vector4& v);

		////////////////////////////////////////////////////////////
		/// @brief Gets the maximum values of two Vector4 objects.
		///
		/// This will get the highest member values of the two Vector
		/// objects and create a new Vector constructed of the high
		/// values.
		///
		/// @param u        The first vector.
		/// @param v        The second vector.
		///
		/// @returns        The maximum x and y values of the two Vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector4 maximum(const Vector4& u, const Vector4& v);

		////////////////////////////////////////////////////////////
		/// @brief Moves a Vector4 towards a target.
		///
		/// The method will return a Vector moving from the current
		/// Vector towards the target by the specified speed.
		///
		/// @param current  The current vector to move from.
		/// @param target   The vector to move towards.
		/// @param speed    The speed of movement.
		///
		/// @returns        The moved vector.
		///
		////////////////////////////////////////////////////////////
		static Vector4 moveTowards(const Vector4& current, const Vector4& target, const T speed);

		////////////////////////////////////////////////////////////
		/// @brief Vector4 linear interpolation.
		///
		/// Linearly interpolates between the current Vector4 and target
		/// by the specfied speed.
		///
		/// @param current  The vector being linearly interpolated from.
		/// @param target   The vector linearly interpolated towards.
		/// @param speed    The speed of the interpolation.
		///
		/// @returns        The interpolated Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector4 lerp(const Vector4& current, const Vector4& target, const T speed);

		//====================
		// Properties
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector4 to ( 0, 0, 0, 0 ).
		///
		/// @returns   A Vector4 object equal to ( 0, 0, 0, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector4 zero(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector4 to ( 1, 1, 1, 1 ).
		///
		/// @returns   A Vector4 object equal to ( 1, 1, 1, 1 ).
		///
		////////////////////////////////////////////////////////////
		static Vector4 one(void);
	};

	//====================
	// Additional Includes
	//====================
	#include <jackal/math/vector4.inl>

	//====================
	// Type Definitions
	//====================
	typedef Vector4<int>          Vector4i;    ///< A Vector4 object made of integers.
	typedef Vector4<unsigned int> Vector4u;    ///< A Vector4 object made of unsigned integers.
	typedef Vector4<float>        Vector4f;    ///< A Vector4 object made of floats.
	typedef Vector4<double>       Vector4d;    ///< A Vector4 object made of doubles.

}//namespace jackal

#endif//__JACKAL_VECTOR4_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Vector4
/// @ingroup math
///
/// jackal::Vector4 is a templated class responsible for
/// all Vector based mathematics in 4 dimensions. It is commonly
/// used throughout the engine for a variety of different tasks,
/// such as placement of HUD elements within a scene and accessing
/// multi-dimensional arrays.
///
/// jackal::Vector4 also contains the most common mathematics
/// and algorithms associated with vectors, such as the dot 
/// product and normalisation. As the mathematics is used commonly
/// throughout the application, it is also exposed to the lua 
/// scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Create two vectors to calculate the dot product.
/// Vector4f v1 = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
/// Vector4f v2 = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
///
/// // Calculate the dot product.
/// float dot = Vector4f::dot(up, right);
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create two vectors to calculate the cross product.
/// local v1 = Vector4(0.0, 1.0, 0.0, 1.0)
/// local v2 = Vector4(1.0, 0.0, 0.0, 1.0)
///
/// // Calculate the dot product.
/// local dot = Vector4.dot(v1, v2)
/// @endcode
///
////////////////////////////////////////////////////////////