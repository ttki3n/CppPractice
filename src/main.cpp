//*
#include "Utils/Log.h"
#include "Utils/Logger.h"
#include <iostream>

int main()
{
	LOG_INFO("Starting session %  %", 1 , "vkl");

	LOG_INFO("% world% %\n", "Hello", '!', 123);

	LOG_INFO("Ending session");
	int a;
	std::cin >> a;
}
