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
#include <jackal/math/matrix4.hpp> // Matrix4 class declaration.

namespace jackal
{
	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Matrix4::Matrix4()
	{
		this->setRow(0, 1.0f, 0.0f, 0.0f, 0.0f);
		this->setRow(1, 0.0f, 1.0f, 0.0f, 0.0f);
		this->setRow(2, 0.0f, 0.0f, 1.0f, 0.0f);
		this->setRow(3, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	//====================
	// Operators
	//====================
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::operator*(const Matrix4& matrix) const
	{
		Matrix4 result = *this;

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][0] * matrix.m[0][j] +
					m[i][1] * matrix.m[1][j] +
					m[i][2] * matrix.m[2][j] +
					m[i][3] * matrix.m[3][j];
			}
		}

		return result;
	}

	////////////////////////////////////////////////////////////
	const Matrix4& Matrix4::operator*=(const Matrix4& matrix)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				m[i][j] = m[i][0] * matrix.m[0][j] +
					m[i][1] * matrix.m[1][j] +
					m[i][2] * matrix.m[2][j] +
					m[i][3] * matrix.m[3][j];
			}
		}

		return *this;
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Vector4f Matrix4::getRow(unsigned int index) const
	{
		return index <= 3 ? Vector4f(m[0][index], m[1][index], m[2][index], m[3][index]) : Vector4f::zero();
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setRow(unsigned int index, float m1, float m2, float m3, float m4)
	{
		m[0][index] = m1;
		m[1][index] = m2;
		m[2][index] = m3;
		m[3][index] = m4;
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setRow(unsigned int index, const Vector4f& row)
	{
		this->setRow(index, row.x, row.y, row.z, row.w);
	}

	////////////////////////////////////////////////////////////
	Vector4f Matrix4::getColumn(unsigned int index) const
	{
		return index <= 3 ? Vector4f(m[index][0], m[index][1], m[index][2], m[index][3]) : Vector4f::zero();
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setColumn(unsigned int index, float m1, float m2, float m3, float m4)
	{
		m[index][0] = m1;
		m[index][1] = m2;
		m[index][2] = m3;
		m[index][3] = m4;
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setColumn(unsigned int index, const Vector4f& column)
	{
		this->setColumn(index, column.x, column.y, column.z, column.w);
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::roll(float degrees)
	{
		const float theta = (3.14f / 180.0f) * degrees;
		Matrix4 matrix;

		matrix.setRow(1, 0.0f, cosf(theta), -sinf(theta), 0.0f);
		matrix.setRow(2, 0.0f, sinf(theta), cosf(theta), 0.0f);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::pitch(float degrees)
	{
		const float theta = (3.14f / 180.0f) * degrees;
		Matrix4 matrix;

		matrix.setRow(0,  cosf(theta), 0.0f, sinf(theta), 0.0f);
		matrix.setRow(2, -sinf(theta), 0.0f, cosf(theta), 0.0f);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::yaw(float degrees)
	{
		const float theta = (3.14f / 180.0f) * degrees;
		Matrix4 matrix;

		matrix.setRow(0, cosf(theta), -sinf(theta), 0.0f, 0.0f);
		matrix.setRow(1, sinf(theta), cosf(theta), 0.0f, 0.0f);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::translation(float x, float y, float z)
	{
		Matrix4 matrix;

		matrix.setRow(0, 1.0f, 0.0f, 0.0f, x);
		matrix.setRow(1, 0.0f, 1.0f, 0.0f, y);
		matrix.setRow(2, 0.0f, 0.0f, 1.0f, z);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::translation(const Vector3f& position)
	{
		return Matrix4::translation(position.x, position.y, position.z);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::rotation(float x, float y, float z)
	{
		return Matrix4::yaw(z) * Matrix4::pitch(y) * Matrix4::roll(x);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::rotation(const Vector3f& rotation)
	{
		return Matrix4::rotation(rotation.x, rotation.y, rotation.z);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(float x, float y, float z)
	{
		Matrix4 matrix;

		matrix.setRow(0, x,    0.0f, 0.0f, 0.0f);
		matrix.setRow(1, 0.0f, y,    0.0f, 0.0f);
		matrix.setRow(2, 0.0f, 0.0f, z,    0.0f);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(const Vector3f& scale)
	{
		return Matrix4::scale(scale.x, scale.y, scale.z);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(float u)
	{
		return Matrix4::scale(u, u, u);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::orthographic(float left, float right, float top, float bottom, float near, float far)
	{
		Matrix4 matrix;
		const float value = 2.0f;

		matrix.setRow(0, value / (right - left), 0.0f, 0.0f, -(right + left) / (right - left));
		matrix.setRow(1, 0.0f, value / (top - bottom), 0, -(top + bottom) / (top - bottom));
		matrix.setRow(2, 0.0f, 0.0f, value / (far - near), -(far + near) / (far - near));

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::perspective(float fov, float ratio, float near, float far)
	{
		const float halfFov = tanf((fov * (180.0f / 3.14f)) / 2.0f);
		const float range = near - far;

		Matrix4 matrix;

		matrix.setRow(0, 1.0f / (halfFov * ratio), 0.0f, 0.0f, 0.0f);
		matrix.setRow(1, 0.0f, 1.0f / halfFov, 0.0f, 0.0f);
		matrix.setRow(2, 0.0f, 0.0f, (-near - far) / range, 2.0f * far * near / range);
		matrix.setRow(3, 0.0f, 0.0f, 1.0f, 0.0f);

		return matrix;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::view(const Vector3f& forward, const Vector3f& up)
	{
		Vector3f f = forward.normalised();
		Vector3f u = up.normalised();

		u = Vector3f::cross(u, f);
		Vector3f v = Vector3f::cross(f, u);

		Matrix4 matrix;

		matrix.setRow(0, u.x, u.y, u.z, 0.0f);
		matrix.setRow(1, v.x, v.y, v.z, 0.0f);
		matrix.setRow(2, f.x, f.y, f.z, 0.0f);

		return matrix;
	}

	//====================
	// Properties
	//====================
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::identity()
	{
		return Matrix4();
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::zero()
	{
		Matrix4 matrix;

		for (unsigned int i = 0; i < 4; i++)
		{
			matrix.setRow(i, 0.0f, 0.0f, 0.0f, 0.0f);
		}

		return matrix;
	}
}