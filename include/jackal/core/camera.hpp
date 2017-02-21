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

#ifndef __JACKAL_CAMERA_HPP__
#define __JACKAL_CAMERA_HPP__

//====================
// Jackal includes
//====================
#include <jackal/math/transform.hpp> // Camera's translation, rotation and scale.
#include <jackal/math/vector2.hpp>   // Storing the size and planes of the Camera.
#include <jackal/math/matrix4.hpp>   // Storing the view and projection as matrices.

namespace jackal
{	
	//====================
	// Jackal forward declarations
	//====================
	class ConfigFile;
	class Window;

	class Camera final
	{
	private:	
		//====================
		// Member variables
		//====================
		static Camera* m_pMain;     ///< A reference to the current main camera.
		Transform      m_transform; ///< The translation and rotation of the camera.
		float          m_fov;       ///< Field of view of the camera.
		Vector2f       m_size;      ///< The rendering size definition.
		Vector2f       m_planes;    ///< Far and near clipping planes.

	public:
		//====================
		// Ctor and dtor
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Default constructor for the Camera object.
		///
		/// The default constructor will set all of the member variables
		/// to a default state. The camera is not useable in this current 
		/// state, a subsequent call to Camera::create needs to be invoked
		/// for correct camera behaviour.
		///
		////////////////////////////////////////////////////////////
		explicit Camera();

		////////////////////////////////////////////////////////////
		/// @brief Default destructor for the Camera object.
		////////////////////////////////////////////////////////////
		~Camera() = default;

		//====================
		// Getters and setters
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Retrieves the current main camera of the application.
		///
		/// The main camera is a globally accessible object that retains
		/// the current main camera of the application. When a camera is first
		/// initialised and created, if no previous camera has been defined, it
		/// will be designated at the main camera. The main camera can be changed
		/// by invoking the Camera::setMain method.
		///
		/// @returns The current main camera of the application.
		///
		////////////////////////////////////////////////////////////
		static Camera& getMain();

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the transform of the Camera object.
		///
		/// The Transform is used to manipulate the position and rotation
		/// of the Camera object. The transform can be manipulated to
		/// simulate movement within a 3D scene. A reference to the 
		/// Transform is returned so that the object can be manipulated
		/// directly.
		///
		/// @returns The Transform of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform();

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the current field of view of the Camera object.
		///
		/// The field of view controls the view radius that the camera
		/// will display within a scene, the larger the value, the more
		/// of the scene can be seen (too high of a value will begin to distort
		/// the view).
		///
		/// @returns The current field of view of the camera.
		///
		////////////////////////////////////////////////////////////
		float getFieldOfView() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the new field of view of the Camera object.
		///
		/// The field of view controls the view radius that the camera
		/// will display within a scene, the larger the value, the more
		/// of the scene can be seen (too high of a value will begin to distort
		/// the view).
		///
		/// @param fov The new field of view for the camera.
		///
		////////////////////////////////////////////////////////////
		void setFieldOfView(float fov);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the size of the camera.
		///
		/// The size refers to the rendering dimensions of the camera, by
		/// default they are set to the same size as the main window. If the
		/// size is changed, specific parts of the window will not render
		/// elements. 
		///
		/// @returns The current dimensions of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Vector2f getSize() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the new dimensions of the camera.
		///
		/// The size refers to the rendering dimensions of the camera, by
		/// default they are set to the same size as the main window. If the
		/// size is changed, specific parts of the window will not render
		/// elements. 
		///
		/// @param size The new dimensions of the Camera.
		///
		////////////////////////////////////////////////////////////
		void setSize(const Vector2f& size);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the near clipping plane of the Camera.
		///
		/// The near clipping plane controls the minimum distance from
		/// the camera that an object will render. If the value is too small,
		/// it can result in strange behaviour when rendering objects, it is
		/// recommended to go no longer than 1.0.
		///
		/// @returns The near clipping plane.
		///
		////////////////////////////////////////////////////////////
		float getNearPlane() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the far clipping plane of the Camera.
		///
		/// The far clipping plane controls the maximum distance from
		/// the camera that an object will render. If the value is too large,
		/// it may result in performance issues, it is reccomended to not exceed
		/// values of 1000.0.
		///
		/// @returns The far clipping plane.
		///
		////////////////////////////////////////////////////////////
		float getFarPlane() const;

		////////////////////////////////////////////////////////////
		/// @brief Sets the near and far clipping planes of the Camera object.
		///
		/// The clipping planes control the distances that objects will render. The 
		/// minimum controls how close objects will stop rendering, and vice versa
		/// for the far clipping plane.
		///
		/// @param near  The new value for the near clipping plane.
		/// @param far   The new value for the far clipping plane.
		///
		////////////////////////////////////////////////////////////
		void setPlanes(float near, float far);

		////////////////////////////////////////////////////////////
		/// @brief Sets the near and far clipping planes of the Camera object.
		///
		/// The clipping planes control the distances that objects will render. The 
		/// minimum controls how close objects will stop rendering, and vice versa
		/// for the far clipping plane.
		///
		/// @param plane The new values for the planes (x for near plane, y for far plane).
		///
		////////////////////////////////////////////////////////////
		void setPlanes(const Vector2f& plane);

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the view of the Camera object.
		///
		/// The view returns a specific matrix responsible for viewing
		/// objects within a 3D scene from the camera position and perspective.
		/// Combined with the Camera objects projection matrix, this will
		/// display objects within a 3D environment. The view matrix is constructed
		/// of the camera's position and it's local forward and up vectors.
		///
		/// @returns The view matrix of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Matrix4 getView() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the perspective projection of the Camera object.
		///
		/// The projection returns a specific matrix that constructs
		/// a perspective matrix from the values stored within the Camera
		/// object. Combined with the camera's view matrix, it will provide
		/// the user with a view into a 3D scene and can be translated within
		/// to provide camera movement and rotation.
		///
		/// @returns The perspective projection matrix of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Matrix4 getProjection() const;

		////////////////////////////////////////////////////////////
		/// @brief Retrieves the view projection matrix of the Camera object.
		///
		/// This method is a convenience method that returns the result of
		/// the multiplication of the camera's view and perspective projection
		/// matrices.
		///
		/// @returns The perspective view projection matrix of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Matrix4 getViewProjection() const;

		//====================
		// Methods
		//====================
		////////////////////////////////////////////////////////////
		/// @brief Creates and initialises the member variables of the Camera object.
		///
		/// Before the camera can be used within the application, it must be
		/// created. This create method will utilise variables declared within
		/// the external config file for setting the variables of the camera, such
		/// as size and field of view. When this method is invoked and successful,
		/// the camera can be used within the application.
		///
		/// @param config  The external config file to read the values from.
		///
		////////////////////////////////////////////////////////////
		void create(const ConfigFile& config);

		////////////////////////////////////////////////////////////
		/// @brief Creates and initialises the member variables of the Camera object.
		///
		/// Before the camera can be used within the application, it must be
		/// created. This create method will utilise variables declared explicitly
		/// within its arguments to construct the camera.
		///
		/// @param fov        The field of view of the camera.
		/// @param size       The rendering dimensions.
		/// @param nearPlane  The near clipping plane.
		/// @param farPlane   The far clipping plane.
		///
		////////////////////////////////////////////////////////////
		void create(float fov, const Vector2f& size, float nearPlane, float farPlane);
	};

} // namespace jackal

#endif//__JACKAL_CAMERA_HPP__

////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Camera
/// @ingroup core
///
/// The jackal::Camera is a simple wrapper class that is responsible
/// for providing the user's view into the 3D game world. It contains
/// utility methods for returning the view and perspective matrices
/// aswell as translation and rotation through its Transform member
/// variable.
///
/// The jackal::Camera also provides a static getter method for
/// globally retrieving the currently set main camera, for 
/// convenience instead of passing the camera around several
/// different methods and functions. Before the application can be
/// used, the camera must be initialised with either values from a
/// configuration file or implicitly. 
///
/// As the camera should be manipulated by the user, it's methods
/// and properties are exposed to the lua scripting interface.
///
/// C++ Code example:
/// @code
/// using namespace jackal;
///
/// // Load a configuration file and utilise the vfs.
/// ConfigFile config;
/// config.open("~config/main.jcfg");
///
/// // Create a Camera object and load the variables from the config file.
/// Camera camera;
/// camera.create(config);
///
/// // In other part of the code.
/// // Translate the camera by the global forward of the scene.
/// Camera::getMain().getTransform().translate(Vector3f::forward() * 5.0f * Time::getDeltaTime());
///
/// @endcode
///
/// Lua Code example:
/// @code
/// -- The camera would have already been created by the C++ side.
/// -- Translate the camera by the forward of the scene.
/// Camera.main.transform:translate(Vector3.forward() * 5.0 * Time.get_deltatime());
/// @endcode
///
////////////////////////////////////////////////////////////