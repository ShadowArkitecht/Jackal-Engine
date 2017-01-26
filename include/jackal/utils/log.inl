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
// Static variables
//====================
template <typename T> bool Log<T>::m_debugEnabled = true;
template <typename T> bool Log<T>::m_warningEnabled = true;
template <typename T> bool Log<T>::m_errorEnabled = true; 

//====================
// Ctor and dtor
//====================
////////////////////////////////////////////////////////////
template <typename T>
Log<T>::Log(const std::string& filename)
	: NonCopyable(), m_line(1), m_policy(), m_stream(), m_mutex()
{
	if (!m_policy.open(filename))
	{
		std::cout << "Failed to open log file: " << filename << std::endl;
	}
}

//====================
// Private methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
std::string Log<T>::getTimeStamp() const
{
	auto stamp = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(stamp);

	std::string str(std::ctime(&time));

	return str.substr(0, str.length() - 1);
}

////////////////////////////////////////////////////////////
template <typename T>
std::string Log<T>::formatStamp()
{
	std::ostringstream ss;
	ss.str(std::string());

	ss.fill('0');
	ss.width(7);

	ss << m_line++ << " < " << this->getTimeStamp() << " - ";

	ss.fill('0');
	ss.width(7);

	ss << std::clock() << " >~ ";
	return ss.str();
}

////////////////////////////////////////////////////////////
template <typename T>
void Log<T>::write()
{
	m_policy.write(this->formatStamp().append(m_stream.str()));
	// Clear the stream.
	m_stream.str(std::string());
	m_stream.clear();
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename Arg, typename... Args>
void Log<T>::write(Arg&& arg, Args&&... args)
{
	m_stream << arg << " ";
	this->write(args...);
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename Arg>
void Log<T>::function(std::stringstream& ss, Arg&& arg) const
{
	ss << arg << " )";
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename Arg, typename... Args>
void Log<T>::function(std::stringstream& ss, Arg&& arg, Args&&... args) const
{
	ss << arg << ", ";
	this->function(ss, args...);
}

//====================
// Methods
//====================
////////////////////////////////////////////////////////////
template <typename T>
template <typename... Args>
void Log<T>::debug(Args&&... args)
{
	if (m_debugEnabled)
	{
		m_mutex.lock();

		m_stream << "<DEBUG>: ";
		this->write(args...);

		m_mutex.unlock();
	}
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename... Args>
void Log<T>::warning(Args&&... args)
{
	if (m_warningEnabled)
	{
		m_mutex.lock();

		m_stream << "<WARNING>: ";
		this->write(args...);

		m_mutex.unlock();
	}
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename... Args>
void Log<T>::error(Args&&... args)
{
	if (m_errorEnabled)
	{
		m_mutex.lock();

		m_stream << "<ERROR>: ";
		this->write(args...);

		m_mutex.unlock();
	}
}

////////////////////////////////////////////////////////////
template <typename T>
std::string Log<T>::function(const std::string& func) const
{
	std::string result;
	result.append(func);
	result.append("()");

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename... Args>
std::string Log<T>::function(const std::string& func, Args&&... args) const
{
	std::stringstream ss;

	ss << func << "( ";
	this->function(ss, args...);
	
	return ss.str();
}