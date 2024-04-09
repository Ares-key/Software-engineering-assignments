#include <stdio.h>
#include <Windows.h>

int find_max_add(int n, int a[])
{
	int sum = 0, max = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		if (max < sum)
			max = sum;
		if (sum < 0)
			sum = 0;
	}
	return max;
}

int main()
{
	
	return 0;
}