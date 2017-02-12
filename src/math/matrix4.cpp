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
// C++ includes
//====================
#include <cmath>                   // Trigonometry functions.

//====================
// Jackal includes
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

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				float sum = 0.0f;
				for (int k = 0; k < 4; k++)
				{
					sum = sum + m[i * 4 + k] * matrix.m[k * 4 + j];
				}
				result.m[i * 4 + j] = sum;
			}
		}

		return result;
	}

	////////////////////////////////////////////////////////////
	const Matrix4& Matrix4::operator*=(const Matrix4& matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					m[i * 4 + j] = m[i * 4 + j] + m[i * 4 + k] * matrix.m[k * 4 + j];
				}
			}
		}

		return *this;
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Vector4f Matrix4::getCol(unsigned int index) const
	{
		unsigned int pos = index * 4;
		return Vector4f(m[pos], m[pos + 1], m[pos + 2], m[pos + 3]);
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setCol(unsigned int index, const Vector4f& col)
	{
		this->setCol(index, col.x, col.y, col.z, col.w);
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setCol(unsigned int index, float m1, float m2, float m3, float m4)
	{
		unsigned int pos = index * 4;
		m[pos]     = m1;
		m[pos + 1] = m2;
		m[pos + 2] = m3;
		m[pos + 3] = m4;
	}

	////////////////////////////////////////////////////////////
	Vector4f Matrix4::getRow(unsigned int index) const
	{
		return Vector4f(m[index], m[index += 4], m[index += 4], m[index += 4]);
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setRow(unsigned int index, const Vector4f& row)
	{
		this->setRow(index, row.x, row.y, row.z, row.w);
	}

	////////////////////////////////////////////////////////////
	void Matrix4::setRow(unsigned int index, float m1, float m2, float m3, float m4)
	{
		m[index]      = m1;
		m[index += 4] = m2;
		m[index += 4] = m3;
		m[index += 4] = m4;
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::translation(const Vector3f& position)
	{
		return Matrix4::translation(position.x, position.y, position.z);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::translation(float x, float y, float z)
	{
		Matrix4 result;
		result.setCol(3, x, y, z, 1.0f);

		return result;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::roll(float degrees)
	{
		float radians = (3.14f / 180.0f) * degrees;
		
		Matrix4 result;
		result.setRow(1, 0.0f, cosf(radians), -sinf(radians), 0.0f);
		result.setRow(2, 0.0f, sinf(radians),  cosf(radians), 0.0f);

		return result;
	}
	
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::pitch(float degrees)
	{
		float radians = (3.14f / 180.0f) * degrees;

		Matrix4 result;
		result.setRow(0,  cosf(radians), 0.0f, sinf(radians), 0.0f);
		result.setRow(2, -sinf(radians), 0.0f, cosf(radians), 0.0f);

		return result;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::yaw(float degrees)
	{
		float radians = (3.14f / 180.0f) * degrees;

		Matrix4 result;
		result.setRow(0, cosf(radians), -sinf(radians), 0.0f, 0.0f);
		result.setRow(1, sinf(radians),  cosf(radians), 0.0f, 0.0f);

		return result;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::rotation(const Vector3f& rotation)
	{
		return Matrix4::rotation(rotation.x, rotation.y, rotation.z);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::rotation(float x, float y, float z)
	{
		return Matrix4::yaw(z) * Matrix4::pitch(y) * Matrix4::roll(x);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(const Vector3f& scale)
	{
		return Matrix4::scale(scale.x, scale.y, scale.z);
	}
	
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(float x, float y, float z)
	{
		Matrix4 result;
		result.m[0] = x;
		result.m[5] = y;
		result.m[10] = z;

		return result;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::scale(float scale)
	{
		return Matrix4::scale(scale, scale, scale);
	}

	//====================
	// Properties
	//====================
	////////////////////////////////////////////////////////////
	Matrix4 Matrix4::identity()
	{
		return Matrix4();
	}

} // namespace jackal