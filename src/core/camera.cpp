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
// Jackal includes
//====================
#include <jackal/core/camera.hpp>      // Camera class declaration.
#include <jackal/utils/log.hpp>        // Logging camera creation.
#include <jackal/core/config_file.hpp> // Loading camera variables from a ConfigFile.

namespace jackal
{
	//====================
	// Static variables
	//====================
	Camera* Camera::m_pMain = nullptr;           // A reference to the main Camera.
	static DebugLog log("logs/engine_log.txt");  // Logging warnings and errors.

	//====================
	// Ctor and dtor
	//====================
	////////////////////////////////////////////////////////////
	Camera::Camera()
		: m_transform(), m_fov(0.0f), m_size(), m_planes()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	Camera& Camera::getMain()
	{
		return *m_pMain;
	} 

	////////////////////////////////////////////////////////////
	Transform& Camera::getTransform()
	{
		return m_transform;
	}

	////////////////////////////////////////////////////////////
	float Camera::getFieldOfView() const
	{
		return m_fov;
	}

	////////////////////////////////////////////////////////////
	void Camera::setFieldOfView(float fov)
	{
		m_fov = fov;
	}

	////////////////////////////////////////////////////////////
	Vector2f Camera::getSize() const
	{
		return m_size;
	}

	////////////////////////////////////////////////////////////
	void Camera::setSize(const Vector2f& size)
	{
		m_size = size;
	}

	////////////////////////////////////////////////////////////
	float Camera::getNearPlane() const
	{
		return m_planes.x;
	}

	////////////////////////////////////////////////////////////
	float Camera::getFarPlane() const
	{
		return m_planes.y;
	}

	////////////////////////////////////////////////////////////
	void Camera::setPlanes(float near, float far)
	{
		m_planes.x = near;
		m_planes.y = far;
	}

	////////////////////////////////////////////////////////////
	void Camera::setPlanes(const Vector2f& plane)
	{
		m_planes = plane;
	}

	////////////////////////////////////////////////////////////
	Matrix4 Camera::getView() const
	{
		return Matrix4::translation(-m_transform.getPosition()) * Matrix4::view(Vector3f::forward(), Vector3f::up());
	}

	////////////////////////////////////////////////////////////
	Matrix4 Camera::getProjection() const
	{
		return Matrix4::perspective(m_fov, m_size.x / m_size.y, m_planes.x, m_planes.y);
	}

	////////////////////////////////////////////////////////////
	Matrix4 Camera::getViewProjection() const
	{
		return this->getView() * this->getProjection();
	}

	//====================
	// Methods
	//====================
	////////////////////////////////////////////////////////////
	void Camera::create(const ConfigFile& config)
	{
		float fov = config.get<float>("Camera.field_of_view");
		Vector2f size = config.get<Vector2f>("Camera.size");
		Vector2f planes = config.get<Vector2f>("Camera.planes");

		this->create(fov, size, planes.x, planes.y);
	}

	////////////////////////////////////////////////////////////
	void Camera::create(float fov, const Vector2f& size, float nearPlane, float farPlane)
	{
		m_fov = fov;
		m_size = size;
		m_planes.x = nearPlane;
		m_planes.y = farPlane;

		if (!m_pMain)
		{
			m_pMain = this;
		}

		log.debug(log.function(__FUNCTION__, fov, size, nearPlane, farPlane), "Created successfully.");
	}
	
} // namespace jackal