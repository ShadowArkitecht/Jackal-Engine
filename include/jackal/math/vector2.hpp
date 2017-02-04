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

#ifndef __JACKAL_VECTOR2_HPP__
#define __JACKAL_VECTOR2_HPP__

//====================
// C++ includes
//====================
#include <cmath>        // Needed for trigonometry functions i.e sin, cos.
#include <algorithm>    // Finding minimum and maximum.
#include <iostream>     // operator<< overloading.

namespace jackal
{
	template <typename T>
	class Vector2 final
	{
	public:
        //====================
		// Member Variables
		//====================
		T x; ///< The x (right) value.
		T y; ///< The y (up) value.

	public:
        //====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Vector2 object.
		///
		/// When the default constructor for the Vector2 object is called, 
		/// it sets the x and y values to 0.
		///
		////////////////////////////////////////////////////////////
		explicit Vector2(void);

		////////////////////////////////////////////////////////////
		/// @brief Constructor for a Vector2 object with defined x and y values.
		///
		/// This constructor is used to set the two values of the
		/// Vector2 objects to user defined amounts.
		///
		/// @param x	The x value of the Vector2 object.
		///	@param y	The y value of the Vector2 object.
		///
		////////////////////////////////////////////////////////////
		explicit Vector2(T x, T y);

		////////////////////////////////////////////////////////////
		/// @brief Constructor for a Vector2 object, generating values from anoher Vector2.
		///
		/// As there are numerous different type definitions and Vector2
		/// types, this constructor will convert from one Vector2 type to another.
		///
		/// @param vector	The different Vector2 type.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Vector2 object.
		////////////////////////////////////////////////////////////
		~Vector2(void) = default;

        //====================
		// Operators
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector2 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and return the result as a new Vector2 object.
		///
		/// @param vector   The Vector2 object to add.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator+(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector2 and a value.
		///
		/// This operator performs a member-wise addition of a Vector2
		/// and a value and returns the result as a new Vector2 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator+(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector2 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and return the result as a new Vector2 object.
		///
		/// @param vector   The vector to subtract.
		///
		/// @returns        A new Vector2 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator-(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector2 and a value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and a value and returns the result as a new Vector2 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A new Vector2 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator-(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector2 objects.
		///
		/// This operator performs a member-wise multiplication of two
		/// vectors and return the result as a new Vector2 object.
		///
		/// @param vector   The vector to multiply.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator*(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector2 and a value.
		///
		/// This operator performs a member-wise multiplication of a Vector2
		/// and a value and returns the result as a new Vector2 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator*(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector2 objects.
		///
		/// This operator performs a member-wise division of two
		/// vectors and return the result as a new Vector2 object.
		///
		/// @param vector   The vector to divide.
		///
		/// @returns        A new Vector2 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator/(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector2 and a value.
		///
		/// This operator performs a member-wise division of a Vector2
		/// and a value and returns the result as a new Vector2 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A new Vector2 object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator/(T value) const;

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between two Vector2 objects.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and applies the result to the current Vector2 object.
		///
		/// @param vector   The vector to add.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator+=(const Vector2& vector);

		////////////////////////////////////////////////////////////
		/// @brief Addition operator between a Vector2 and value.
		///
		/// This operator performs a member-wise addition of a vector
		/// and value and applies the result to the current Vector2 object.
		///
		/// @param value    The value to add.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator+=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between two Vector2 objects.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and applies the result to the current Vector2 object.
		///
		/// @param vector   The vector to subtract.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator-=(const Vector2& vector);

		////////////////////////////////////////////////////////////
		/// @brief Subtraction operator between a Vector2 and value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and value and applies the result to the current Vector2 object.
		///
		/// @param value    The value to subtract.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator-=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between two Vector2 objects.
		///
		/// This operator performs a member-wise multiplication of two vectors
		/// and applies the result to the current Vector2 object.
		///
		/// @param vector   The vector to multiply.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator*=(const Vector2& vector);

		////////////////////////////////////////////////////////////
		/// @brief Multiplication operator between a Vector2 and value.
		///
		/// This operator performs a member-wise multiplication of a vector
		/// and value and applies the result to the current Vector2 object.
		///
		/// @param value    The value to multiply.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator*=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between two Vector2 objects.
		///
		/// This operator performs a member-wise division of two vectors
		/// and applies the result to the current Vector2 object.
		///
		/// @param vector   The vector to divide.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator/=(const Vector2& vector);

		////////////////////////////////////////////////////////////
		/// @brief Division operator between a Vector2 and value.
		///
		/// This operator performs a member-wise division of a vector
		/// and value and applies the result to the current Vector2 object.
		///
		/// @param value    The value to divide.
		///
		/// @returns        A reference to the current Vector2 object.
		///
		////////////////////////////////////////////////////////////
		const Vector2& operator/=(T value);

		////////////////////////////////////////////////////////////
		/// @brief Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are the same, the Vector2 objects are equal.
		///
		/// @param vector   The Vector2 object to compare against.
		///
		/// @returns        True if the Vector2 objects are the same.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Non-Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are not the same, the Vector2 object are not equal.
		///
		/// @param vector   The Vector2 object to compare against.
		///
		/// @returns        True if the Vector2 objects are not the same.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Vector2& vector) const;

		////////////////////////////////////////////////////////////
		/// @brief Unary operation on a Vector2 object.
		///
		/// This will invert the x and y components from positive to negative
		/// values, and vice-versa.
		///
		/// @returns    An inverted Vector2 object.
		///
		////////////////////////////////////////////////////////////
		Vector2 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Overload the output stream operator to print a Vector2
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// vector to the console window. The matrix will be printed in the
		/// following format: ( x, y )
		///
		/// @param os       The output stream to stream into.
		/// @param vector   The vector to print to the console window.
		///
		/// @returns        The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) 
		{
			return os << "( " << vector.x << ", " << vector.y << " )";
		}

        //====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Calculates the squared length of the Vector2 object.
		///
		/// @returns    The squared length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitudeSqr(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the length of the Vector2 object.
		///
		/// @returns    The length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitude(void) const;

		////////////////////////////////////////////////////////////
		/// @brief Calculates the unit length of the Vector2 object.
		///
        /// A normalised vector is used to represent the direction of the
        /// vector with values ranging from 0 to 1.
        ///
		/// @returns    The normalised Vector2 object.
		///
		////////////////////////////////////////////////////////////
		Vector2 normalised(void);

		////////////////////////////////////////////////////////////
		/// @brief Rotates the vector by the specified angle.
		///
		/// Rotates the vector by the angle specified, the angle is
		/// in degrees.
		///
		/// @param position The position of the Vector2 to rotate.
		/// @param angle    The angle to rotate the Vector2 by.
		///
        /// @returns        The rotated Vector2 object.
        ///
		////////////////////////////////////////////////////////////
		static Vector2 rotate(const Vector2& position, T angle);

		////////////////////////////////////////////////////////////
		/// @brief Calculate the cosine angle between two Vector2 objects.
		///
		/// The dot product is the value equal to the magnitudes/length of
		/// the two vectors multiplied together and then multiplied by the
		/// cosine of the angle between them.
		///
		/// @param u    The first vector.
		/// @param v    The second vector.
		///
		/// @returns    The cosine angle between two Vector2 objects.
		///
		////////////////////////////////////////////////////////////
		static T dot(const Vector2& u, const Vector2& v);

		////////////////////////////////////////////////////////////
		/// @brief Gets the (degrees) angle between two Vector2 objects.
		///
		/// This will calculate the angle between two different vectors. The angle
		/// will be returned in degrees.
		///
		/// @param from     The vector where the angle measurement will begin.
		/// @param to       The vector where the angle measurement will end.
		///
		/// @returns        The angle between the vectors in degrees.
		///
		////////////////////////////////////////////////////////////
		static T angle(const Vector2& from, const Vector2& to);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the squared euclidean distance between two different vectors.
		///
		/// @param from     The starting vector.
		/// @param to       The vector distance to measure.
		///
		/// @returns        The squared euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distanceSqr(const Vector2& from, const Vector2& to);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the euclidean distance between two different vectors.
		///
		/// @param from     The starting vector.
		/// @param to       The vector distance to measure.
		///
		/// @returns        The euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distance(const Vector2& from, const Vector2& to);

		////////////////////////////////////////////////////////////
		/// @brief Gets the minimum values of two Vector2 objects.
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
		static Vector2 minimum(const Vector2& u, const Vector2& v);

		////////////////////////////////////////////////////////////
		/// @brief Gets the maximum values of two Vector2 objects.
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
		static Vector2 maximum(const Vector2& u, const Vector2& v);

		////////////////////////////////////////////////////////////
		/// @brief Moves a Vector2 towards a target.
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
		static Vector2 moveTowards(const Vector2& current, const Vector2& target, T speed);

		////////////////////////////////////////////////////////////
		/// @brief Vector2 linear interpolation.
		///
		/// Linearly interpolates between the current Vector2 and target
		/// by the specfied speed.
		///
		/// @param current  The vector being linearly interpolated from.
		/// @param target   The vector linearly interpolated towards.
		/// @param speed    The speed of the interpolation.
		///
		/// @returns        The interpolated Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector2 lerp(const Vector2& current, const Vector2& target, T speed);

        //====================
		// Properties
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector2 to ( 0, 0 ).
		///
		/// @returns   A Vector2 object equal to ( 0, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector2 zero(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector2 to ( 1, 1 ).
		///
		/// @returns   A Vector2 object equal to ( 1, 1 ).
		///
		////////////////////////////////////////////////////////////
		static Vector2 one(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector2 to ( 1, 0 ).
		///
		/// @returns   A Vector2 object equal to ( 1, 0 ).
		///
		////////////////////////////////////////////////////////////
		static Vector2 right(void);

		////////////////////////////////////////////////////////////
		/// @brief Convenience method for initialising a Vector2 to ( 0, 1 ).
		///
		/// @returns   A Vector2 object equal to ( 0, 1 ).
		///
		////////////////////////////////////////////////////////////
		static Vector2 up(void);
	};

    //====================
    // Additional includes
    //====================
    #include <jackal/math/vector2.inl>         // The Vector2 declarations.

    //====================
    // Type definitions
    //====================
	typedef Vector2<int>          Vector2i;    ///< A Vector2 object made of integers.
	typedef Vector2<unsigned int> Vector2u;    ///< A Vector2 object made of unsigned integers.
	typedef Vector2<float>        Vector2f;    ///< A Vector2 object made of floats.
    typedef Vector2<double>       Vector2d;    ///< A Vector2 object made of doubles.

} // namespace jackal

#endif//__JACKAL_VECTOR2_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Vector2
/// @ingroup math
///
/// jackal::Vector2 is a templated class responsible for
/// all Vector based mathematics in 2 dimensions. It is commonly
/// used throughout the engine for a variety of different tasks,
/// such as placement of HUD elements within a scene and accessing
/// multi-dimensional arrays.
///
/// jackal::Vector2 also contains the most common mathematics
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
/// Vector2f v1 = Vector2f::up();
/// Vector2f v2 = Vector2f::right();
///
/// // Calculate the dot product.
/// float dot = Vector2f::dot(up, right);
/// @endcode
///
/// Lua Code example:
/// @code
/// -- Create two vectors to calculate the cross product.
/// local v1 = Vector2.up()
/// local v2 = Vector2.right()
///
/// // Calculate the dot product.
/// local dot = Vector2.dot(up, right)
/// @endcode
///
////////////////////////////////////////////////////////////