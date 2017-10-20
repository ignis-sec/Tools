#include <iostream>
#include <algorithm>
#include "Easysort.h"

using namespace std;

int main(void)
{
	int *arr;
	arr = (int*)malloc(10 * sizeof(int));
	arr[0] = 15;
	arr[1] = 21;
	arr[2] = 53;
	arr[3] = 5;
	arr[4] = 23;
	arr[5] = 65;
	arr[6] = 12;
	arr[7] = 27;
	arr[8] = 45;
	arr[9] = 5;
	arr[10] = 8;


	Bubble_Sort(&arr, 9);

	for (int i = 0; i < 9; i++)
		cout << arr[i] << '\n';
		

	system("PAUSE");
	return 0;
}