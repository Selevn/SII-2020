#include <iostream>
#include <ctime>
extern "C"
{
	int __stdcall RandUint(int max)
	{
		srand(time(NULL));
		return rand() % max;
	}
	int __stdcall Ord(char ch)
	{
		return (int)ch;
	}
}