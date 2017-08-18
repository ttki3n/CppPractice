#include "Utils/Logger.h"

#include <iostream>
#include <ctime>
namespace Utils
{

Logger::Logger()
{

}

Logger::Logger(unsigned int lvl, unsigned int policy, const std::string& filename)
	:m_logLevel(lvl),
	m_logPolicy(policy)
{
	OpenFile(filename);
}

Logger::~Logger()
{
	CloseFile();
}

template<typename... Args>
void Logger::Write(unsigned int lvl, const char* fmt, Args... args)
{
	if (lvl >= m_logLevel)
	{
		std::lock_guard<std::mutex> lock(m_writeMutex);
		m_logStream << GetLineHeader();
		switch (lvl)
		{
		case LVL_INFO:
			m_logStream << "<INFO> :";
			break;
		case LVL_DEBUG:
			m_logStream << "<DEBUG> :";
			break;
		}

		WriteImpl(fmt, args...);

	}
}

void Logger::WriteImpl(const char* fmt)
{
	m_logStream << fmt;
	m_logStream << '\n';
	// print to console
	std::cout << m_logStream.str();

	//write file
	if (m_ofStreamPtr)
	{
		(*m_ofStreamPtr) << m_logStream.str();
		m_ofStreamPtr->flush();
	}
	//clear
	m_logStream.str("");
}

template<typename T, typename... TArgs>
void Logger::WriteImpl(const char* fmt, T p1, TArgs... p2)
{
	for (; *fmt != '\0'; fmt++)
	{
		if (*fmt == '%')
		{
			m_logStream << p1;
			WriteImpl(fmt + 1, p2...); // recursive
			return;
		}
		m_logStream << *fmt;
	}
}

void Logger::OpenFile(const std::string& filename)
{
	m_ofStreamPtr = std::make_unique<std::ofstream>();
	m_ofStreamPtr->open(filename.c_str(), std::ios_base::binary | std::ios_base::out);
	if (!m_ofStreamPtr->is_open())
	{
		throw(std::runtime_error("LOGGER: Unable to open an output stream"));
	}
}

void Logger::CloseFile()
{
	if (m_ofStreamPtr)
	{
		m_ofStreamPtr->close();
	}
}

void Logger::SetLogLevel(unsigned int lvl)
{
	m_logLevel = lvl;
}

void Logger::SetLogPolicy(unsigned int policy)
{
	m_logPolicy = policy;
}

std::string Logger::GetTime()
{
	std::string time_str;
	time_t raw_time;
	time(&raw_time);
	time_str = ctime(&raw_time);
	//without the newline character
	return time_str.substr(0, time_str.size() - 1);
}

std::string Logger::GetLineHeader()
{
	std::stringstream header;
	std::time_t result = std::time(nullptr);

	header.str("");
	//header.fill('0');
	//header.width(7);
	header << " < " << GetTime() << " - ";
	//header.fill('0');
	//header.width(7);
	header << clock() << " >  ";
	return header.str();
}

}