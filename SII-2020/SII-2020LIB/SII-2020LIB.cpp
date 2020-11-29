#include <iostream>
#include <ctime>
extern "C"
{
	int __stdcall random(int max)
	{
		srand(time(NULL));
		return rand() % max;
	}
	int __stdcall ord(char ch)
	{
		return (int)ch;
	}
}