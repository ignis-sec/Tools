#include <iostream>
#include "Easysort.h"
#include <Windows.h>

using namespace std;

int main(void)
{
///////////////////////////////////////////////////////////////
	int *arr;								//initialize array
	double timetaken;						//
	arr = (int*)malloc(12000 * sizeof(int));//
	for (int i = 0; i < 12000; i++)			//
	{										//
		arr[i] = rand() % 20000;			//
	}										//
//////////////////////////////////////////////

	//timetaken=Bubble_Sort(arr, 12000);
	//timetaken = Selection_Sort(arr, 12000);
	//timetaken = Insertion_Sort(arr, 12000);
	//timetaken = Merge_Sort(arr, 0, 11119);
	timetaken = Quick_Sort(arr, 0, 11119);










	cout << "took " << timetaken << " seconds\n";
	cout << "First 100 elements:\n";
	Sleep(1000);
	for (int i = 0; i < 100; i++)
		cout << arr[i] << '\n';
	
		

	system("PAUSE");
	return 0;
}