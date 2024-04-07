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

void Test1()  //均衡情况
{
	printf("Test 1:\n");
	int a[6] = { -2,11,-4,13,-5,-2 }, n = 6;
	printf("Sequence:%d", a[0]);
	for (int i = 1; i < n; i++)
		printf(",%d", a[i]);
	printf("\nAnswer:");
	printf("%d\n\n", find_max_add(n, a));
	return;
}

void Test2()  //全是负数
{
	printf("Test 2:\n");
	int a[6] = { -2,-11,-4,-13,-5,-2 }, n = 6;
	printf("Sequence:%d", a[0]);
	for (int i = 1; i < n; i++)
		printf(",%d", a[i]);
	printf("\nAnswer:");
	printf("%d\n\n", find_max_add(n, a));
	return;
}

void Test3()  //全是正数
{
	printf("Test 3:\n");
	int a[6] = { 2,11,4,13,5,2 }, n = 6;
	printf("Sequence:%d", a[0]);
	for (int i = 1; i < n; i++)
		printf(",%d", a[i]);
	printf("\nAnswer:");
	printf("%d\n\n", find_max_add(n, a));
	return;
}

int main()
{
	Test1();
	Test2();
	Test3();
	system("pause");
	return 0;
}