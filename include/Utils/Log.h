#pragma once

#include "Logger.h"

namespace Utils
{
	// default instance of logger
class SimpleLogger: public Logger
{
public:
	static SimpleLogger& GetInstance()
	{
		static SimpleLogger ins(Logger::LVL_INFO, Logger::LOGTO_CONSOLE_AND_FILE, "log.txt");			
		return ins;
	}
	SimpleLogger(SimpleLogger const&) = delete;
	void operator=(SimpleLogger const&) = delete;
	

private:
	SimpleLogger() {}
	SimpleLogger(Logger::LOG_LEVEL lvl, Logger::LOG_POLICY p, const std::string& filename)
		:Logger(lvl, p, filename)
	{}



};


}
static Utils::Logger _log(Utils::Logger::LVL_INFO, Utils::Logger::LOGTO_CONSOLE_AND_FILE, "log.txt");




#define LOG_LOG(lvl, fmt, ...) \
	_log.Write(lvl, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
	LOG_LOG(Utils::Logger::LVL_INFO, fmt, ##__VA_ARGS__)