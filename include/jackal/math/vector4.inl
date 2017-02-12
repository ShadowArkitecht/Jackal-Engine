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
Vector4<T>::Vector4(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>::Vector4(const T x, const T y, const T z, const T w)
	: x(x), y(y), z(z), w(w)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector4<T>::Vector4(const Vector4<U>& vector)
	: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)), w(static_cast<T>(vector.w))
{
}

//====================
// Operators
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& vector) const
{
	Vector4<T> result = *this;

	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;
	result.w = w + vector.w;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator+(const T value) const
{
	return this->operator+(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& vector) const
{
	Vector4<T> result = *this;

	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;
	result.w = w - vector.w;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator-(const T value) const
{
	return this->operator-(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator*(const Vector4<T>& vector) const
{
	Vector4<T> result = *this;

	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;
	result.w = w * vector.w;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator*(const T value) const
{
	return this->operator*(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator/(const Vector4<T>& vector) const
{
	Vector4<T> result = *this;

	result.x = x / vector.x;
	result.y = y / vector.y;
	result.z = z / vector.z;
	result.w = w / vector.w;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator/(const T value) const
{
	return this->operator/(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator+=(const T value)
{
	return this->operator+=(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator-=(const T value)
{
	return this->operator-=(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator*=(const T value)
{
	return this->operator*=(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector4<T>& Vector4<T>::operator/=(const T value)
{
	return this->operator/=(Vector4<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector4<T>::operator==(const Vector4<T>& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z) && (w == vector.w);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector4<T>::operator!=(const Vector4<T>& vector) const
{
	return !(*this == vector);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::operator-(void) const
{
	return Vector4<T>(-x, -y, -z, -w);
}

//====================
// Methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
T Vector4<T>::magnitudeSqr(void) const
{
	return ((x * x) + (y * y) + (z * z) + (w * w));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector4<T>::magnitude(void) const
{
	return static_cast<T>(sqrt(this->magnitudeSqr()));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::normalised(void) const
{
	return *this / this->magnitude();
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector4<T>::dot(const Vector4<T>& u, const Vector4<T>& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector4<T>::distanceSqr(const Vector4<T>& from, const Vector4<T>& to)
{
	return ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)) + ((to.z - from.z) * (to.z - from.z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector4<T>::distance(const Vector4<T>& from, const Vector4<T>& to)
{
	return static_cast<T>(sqrt(distanceSqr(from, to)));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::minimum(const Vector4<T>& u, const Vector4<T>& v)
{
	return Vector4<T>(std::min<T>(u.x, v.x),
					  std::min<T>(u.y, v.y),
					  std::min<T>(u.z, v.z),
					  std::min<T>(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::maximum(const Vector4<T>& u, const Vector4<T>& v)
{
	return Vector4<T>(std::max<T>(u.x, v.x),
					  std::max<T>(u.y, v.y),
					  std::max<T>(u.z, v.z),
					  std::max<T>(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::moveTowards(const Vector4<T>& current, const Vector4<T>& target, const T speed)
{
	return (current - target).normalised() * speed;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::lerp(const Vector4<T>& current, const Vector4<T>& target, const T speed)
{
	Vector4<T> cur = current * speed;
	Vector4<T> tar = target * (static_cast<T>(1) - speed);

	return cur + tar;
}

//====================
// Properties
//====================
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::zero(void)
{
	return Vector4<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Vector4<T>::one(void)
{
	return Vector4<T>(1, 1, 1, 1);
}