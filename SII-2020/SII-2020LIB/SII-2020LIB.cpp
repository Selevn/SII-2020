#include <iostream>
#include <ctime>
extern "C"
{
	unsigned int __stdcall random(unsigned int max)
	{
		srand(time(NULL));
		if (max == 0)
			return 1;
		return (unsigned int)rand() % max;
	}
	unsigned int __stdcall ord(char ch)
	{
		return (unsigned int)ch;
	}
	unsigned char __stdcall chr(unsigned int number)
	{
		return (unsigned char)number;
	}

	unsigned char* __stdcall strConcat(void *a, void* b)
	{
		char* first = (char*)a;
		char* second = (char*)b;
		int size = 0;
		if (first != NULL)
			size += strlen(first);
		if (second != NULL)
			size += strlen(second);
		unsigned char* out = (unsigned char*)calloc(size+1, sizeof(unsigned char));
		if (first != NULL)
			for (int i = 0; i < strlen(first); i++)
				out[i] = first[i];
		if (second != NULL)
			for (int i = size-strlen(second),j=0; i < size+1; j++,i++)
				out[i] = second[j];
		out[size+1] = '\0';
		return out;
	}


	void __stdcall outputuint(unsigned int a)
	{
		std::cout << a << std::endl;
	}
	void __stdcall outputchar(char a)
	{
		std::cout << a <<std::endl;
	}
	void __stdcall outputstr(void* in)
	{
		char *a = (char*)in;
		setlocale(0, "");
		if(a != NULL)
			std::cout << a << std::endl;
	}

}