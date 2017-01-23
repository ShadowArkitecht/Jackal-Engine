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

#ifndef __JACKAL_SINGLETON_HPP__
#define __JACKAL_SINGLETON_HPP__

//====================
// Jackal includes
//====================
#include <jackal/utils/non_copyable.hpp> // Singleton objects should only be referred by reference, not copied.

namespace jackal
{
	template <typename T>
	class Singleton : NonCopyable
	{
	protected:
		//====================
		// Protected ctor
		//====================
		//////////////////////////////////////////////////////////// 
		/// @brief Default constructor of a Singleton instance.
		///
		/// The singleton constructor is never accessible outside the
		/// scope of itself or its children, this is to prevent multiple
		/// instances of this object from occuring. A singleton should
		/// only consist of a single instance.
		///
		//////////////////////////////////////////////////////////// 
		explicit Singleton();

	public:
		//====================
		// Dtor
		//====================
		//////////////////////////////////////////////////////////// 
		/// @brief Default virtual destructor of a Singleton instance.
		//////////////////////////////////////////////////////////// 
		virtual ~Singleton() = default;

		//====================
		// Getters and setters
		//====================
		//////////////////////////////////////////////////////////// 
		/// @brief Retrieves the static instance of this Singleton.
		///
		/// This method is used to access the single instance object of this
		/// Singleton. None of the objects functionality can be
		/// accessed without this method. This method ensures that
		/// only a single instance of this object persists throughout
		/// the applications runtime. 
		///
		/// @returns  The static instance of this singleton.
		///
		//////////////////////////////////////////////////////////// 
		static T& getInstance();
	};

	//====================
	// Ctor
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	Singleton<T>::Singleton()
		: NonCopyable()
	{
	}

	//====================
	// Getters and setters
	//====================
	////////////////////////////////////////////////////////////
	template <typename T>
	T& Singleton<T>::getInstance() 
	{
		static T instance;
		return instance;
	}

} // namespace jackal 


////////////////////////////////////////////////////////////
/// @author Benjamin Carter
///
/// @class jackal::Singleton
/// @ingroup utils
///
/// The Singleton class is a templated class that is designed to 
/// be inherited from by child objects. It follows the gang-of-four
/// Singleton design pattern for retaining a single instance of a
/// specified object.
///
/// Singletons are used throughout the application as manager classes
/// in order to ease with communication between different modules. Most
/// modules within the engine will have a accompanied manager. This class
/// inherits from the NonCopyable class, which prevents objects being assigned
/// the instance, it must be purely referenced. As the class is predominantly 
/// designed for internal use, only a select few methods are exposed to the lua 
/// scripting interface.
///
/// If the user wishes to extend from this template, it must be declared 
/// as a friend within the child objects scope.
///
/// C++ Code example:
/// @code
/// // This is an example class on using the template to create a new
/// // singleton object.
/// class CustomSingleton : public jackal::Singleton<CustomSingleton> 
/// {
///		friend class jackal::Singleton<CustomSingleton>;
/// public:
/// 	void print() { std::cout << "hello, world!" << std::endl; }
/// };
///
/// // The methods within the class can only be accessed by using the 
/// // instance getter method.
/// CustomSingleton::getInstance().print();
/// @endcode
///
////////////////////////////////////////////////////////////	

#endif//__JACKAL_SINGLETON_HPP__