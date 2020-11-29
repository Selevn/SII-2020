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
	void __stdcall outputuint(unsigned int a)
	{
		std::cout << a << std::endl;
	}
	void __stdcall outputchar(char a)
	{
		std::cout << a <<std::endl;
	}
	void __stdcall outputstr(char* a)
	{
		std::cout << a << std::endl;
	}



}