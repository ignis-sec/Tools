#include <iostream>
#include "Easysort.h"
#include <Windows.h>

#define SIZE 500000

using namespace std;

int main(void)
{
///////////////////////////////////////////////////////////////
	int *arr;								//initialize array
	double timetaken;						//
	arr = (int*)malloc(SIZE * sizeof(int));//
	for (int i = 0; i < SIZE; i++)			//
	{										//
		arr[i] = rand() % SIZE;			//
	}										//
//////////////////////////////////////////////

	//timetaken=Bubble_Sort(arr, SIZE);
	//timetaken = Selection_Sort(arr, SIZE);
	//timetaken = Insertion_Sort(arr, SIZE);
	//timetaken = Merge_Sort(arr, 0, SIZE-1);
	//timetaken = Quick_Sort(arr, 0, SIZE-1);
	timetaken = Shell_Sort(arr,SIZE);


	cout << "took " << timetaken << " seconds\n";
	cout << "First 100 elements:\n";
	Sleep(1000);
	for (int i = 0; i < 100; i++)
		cout << arr[i] << '\n';
	
		

	system("PAUSE");
	return 0;
}