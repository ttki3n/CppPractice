#include <iostream>

#include "Utils/Logger.h"

#include "A.h"
int main()
{
	LOG_INFO("Starting session");

	LOG_INFO("% world% %\n", "Hello", '!', 123);

	ABase ia;

	LOG_INFO("Ending session");
	int a;
	std::cin >> a;
}
