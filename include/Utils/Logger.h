#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <memory>
namespace Utils
{

class Logger
{
public:

	enum LOG_LEVEL
	{
		LVL_INFO = 0,
		LVL_DEBUG,
		LVL_WARNING,
		LVL_ERROR
	};

	enum LOG_POLICY
	{
		LOGTO_CONSOLE = 0,
		LOGTO_FILE ,
		LOGTO_CONSOLE_AND_FILE
	};
	Logger();
	Logger(unsigned int lvl, unsigned int policy, const std::string& filename);
	~Logger();

	void OpenFile(const std::string& filename);
	void CloseFile();
	
	void SetLogLevel(unsigned int lvl);
	void SetLogPolicy(unsigned int policy);	
	
	template<typename... Args>
	void Write(unsigned int lvl, const char* fmt, Args... args);

	void WriteImpl(const char* fmt);
	template<typename T, typename... TArgs>
	void WriteImpl(const char* fmt, T p1, TArgs... p2); // recursive variadic function
	std::string GetTime();
	std::string GetLineHeader();
protected:
	unsigned int m_logLevel;
	unsigned int m_logPolicy;
	std::stringstream m_logStream;
	std::unique_ptr<std::ofstream> m_ofStreamPtr;
	std::mutex m_writeMutex;

};

}

#include "Logger.inl"