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
// Ctor and Dtor
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>::Vector3(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>::Vector3(T x, T y, T z)
	: x(x), y(y), z(z)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector3<T>::Vector3(const Vector3<U>& vector)
	: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z))
{
}

//====================
// Operators
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator+(T value) const
{
	return this->operator+(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(T value) const
{
	return this->operator-(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator*(T value) const
{
	return this->operator*(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x / vector.x;
	result.y = y / vector.y;
	result.z = z / vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator/(T value) const
{
	return this->operator/(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator+=(T value)
{
	return this->operator+=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator-=(T value)
{
	return this->operator-=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator*=(T value)
{
	return this->operator*=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator/=(T value)
{
	return this->operator/=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& vector) const
{
	return !(*this == vector);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(void) const
{
	return Vector3<T>(-x, -y, -z);
}

//====================
// Methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::magnitudeSqr(void) const
{
	return ((x * x) + (y * y) + (z * z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::magnitude(void) const
{
	return static_cast<T>(sqrt(this->magnitudeSqr()));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::normalised(void) const
{
	return *this / this->magnitude();
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::dot(const Vector3<T>& u, const Vector3<T>& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>((u.y * v.z) - (u.z * v.y),
					  (u.z * v.x) - (u.x * v.z),
					  (u.x * v.y) - (u.y * v.x));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::angle(const Vector3<T>& from, const Vector3<T>& to)
{
	T dot = Vector3<T>::dot(from, to);
	T mag = from.magnitude() * to.magnitude();

	T angle = static_cast<T>(acos(dot / mag));

	T PI = static_cast<T>(3.14f);

	return angle * (static_cast<T>(180.0f) / PI);
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::distanceSqr(const Vector3<T>& from, const Vector3<T>& to)
{
	return ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)) + ((to.z - from.z) * (to.z - from.z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::distance(const Vector3<T>& from, const Vector3<T>& to)
{
	return static_cast<T>(sqrt(distanceSqr(from, to)));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::minimum(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>(std::min<T>(u.x, v.x),
					  std::min<T>(u.y, v.y),
					  std::min<T>(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::maximum(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>(std::max<T>(u.x, v.x),
					  std::max<T>(u.y, v.y),
					  std::max<T>(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::moveTowards(const Vector3<T>& current, const Vector3<T>& target, T speed)
{
	return (current - target).normalised() * speed;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::lerp(const Vector3<T>& current, const Vector3<T>& target, T speed)
{
	Vector3<T> cur = current * speed;
	Vector3<T> tar = target * (static_cast<T>(1) - speed);

	return cur + tar;
}

//====================
// Properties
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::zero(void)
{
	return Vector3<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::one(void)
{
	return Vector3<T>(1, 1, 1);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::right(void)
{
	return Vector3<T>(1, 0, 0);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::up(void)
{
	return Vector3<T>(0, 1, 0);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::forward(void)
{
	return Vector3<T>(0, 0, 1);
}