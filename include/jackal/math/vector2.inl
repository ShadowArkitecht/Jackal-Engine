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
// Ctor and dtor
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)) 
{
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(T x, T y)
	: x(static_cast<T>(x)), y(static_cast<T>(y)) 
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& vector)
	: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) 
{
}

//====================
// Operators
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vector) const 
{
	Vector2<T> result = *this;

	result.x = x + vector.x;
	result.y = y + vector.y;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator+(T value) const 
{
	return this->operator+(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vector) const 
{
	Vector2<T> result = *this;

	result.x = x - vector.x;
	result.y = y - vector.y;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator-(T value) const 
{
	return this->operator-(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& vector) const 
{
	Vector2<T> result = *this;

	result.x = x * vector.x;
	result.y = y * vector.y;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator*(T value) const 
{
	return this->operator*(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& vector) const 
{
	Vector2<T> result = *this;

	result.x = x / vector.x;
	result.y = y / vector.y;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator/(T value) const 
{
	return this->operator/(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vector) 
{
	x += vector.x;
	y += vector.y;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator+=(T value) 
{
	return this->operator+=(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& vector) 
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator-=(T value) 
{
	return this->operator-=(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& vector) 
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator*=(T value) 
{
	return this->operator*=(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& vector) 
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector2<T>& Vector2<T>::operator/=(T value)
{
	return this->operator/=(Vector2<T>(value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& vector) const 
{
	return (x == vector.x) && (y == vector.y);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& vector) const 
{
	return !(*this == vector);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator-(void) const 
{
	return Vector2<T>(-x, -y);
}

//====================
// Methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::magnitudeSqr(void) const 
{
	return ((x * x) + (y * y));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::magnitude(void) const 
{
	return static_cast<T>(sqrt(this->magnitudeSqr()));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::normalised(void) 
{
	return *this / this->magnitude();
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::rotate(const Vector2& position, T angle) 
{
	Vector2<T> result;

	T cosine = static_cast<T>(cosf(static_cast<float>(angle)));
	T sine = static_cast<T>(sinf(static_cast<float>(angle)));

	result.x = position.x * cosine - position.y * sine;
	result.y = position.x * sine + position.y * cosine;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::dot(const Vector2<T>& u, const Vector2<T>& v) 
{
	return ((u.x * v.x) + (u.y * v.y));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::angle(const Vector2<T>& from, const Vector2<T>& to) 
{
	// calculate the cosine angle between the two points
	T dot = Vector2<T>::dot(from, to);
	// calculate the combined magnitude
	T mag = from.magnitude() * to.magnitude();
	// Returns the cosine of the equation
	T angle = static_cast<T>(acos(dot / mag));

	T PI = static_cast<T>(3.14f);

	return angle * (static_cast<T>(180.0f) / PI);
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::distanceSqr(const Vector2<T>& from, const Vector2<T>& to) 
{
	return ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::distance(const Vector2<T>& from, const Vector2<T>& to) 
{
	return static_cast<T>(sqrt(distanceSqr(from, to)));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::minimum(const Vector2<T>& u, const Vector2<T>& v) 
{
	return Vector2<T>(std::min<T>(u.x, v.x), std::min<T>(u.y, v.y));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::maximum(const Vector2<T>& u, const Vector2<T>& v) 
{
	return Vector2<T>(std::max<T>(u.x, v.x), std::max<T>(u.y, v.y));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::moveTowards(const Vector2<T>& current, const Vector2<T>& target, T speed)
{
	return (current - target).normalised() * speed;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::lerp(const Vector2<T>& current, const Vector2<T>& target, T speed) 
{
	Vector2<T> cur = current * speed;
	Vector2<T> tar = target * (static_cast<T>(1) - speed);

	return cur + tar;
}

//====================
// Properties
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::zero(void) 
{
	return Vector2<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::one(void) 
{
	return Vector2<T>(1, 1);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::right(void) 
{
	return Vector2<T>(1, 0);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::up(void) 
{
	return Vector2<T>(0, 1);
}