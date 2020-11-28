#include <iostream>
extern "C"
{
	int getmin(int count, int* arr)
	{
		int min = *arr;
		for (int i = 0; i < count; i++)
		{
			if (*(arr + i) < min)
				min = *(arr + i);
		}
		return min;
	}
	int getmax(int count, int* arr)
	{
		int max = *arr;
		for (int i = 0; i < count; i++)
		{
			if (*(arr + i) > max)
				max = *(arr + i);
		}
		return max;
	}
}