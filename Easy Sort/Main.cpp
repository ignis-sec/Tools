#include <iostream>
#include "Easysort.h"
#include <Windows.h>

#define SIZE 15000


using namespace std;

int main(void)
{
///////////////////////////////////////////////////////////////
	int *arr;								//initialize array with random noise
	double timetaken;						//
	arr = (int*)malloc(SIZE * sizeof(int));	//
	for (int i = 0; i < SIZE; i++)			//
	{										//
		arr[i] = rand() % SIZE;				//
	}										//
////////////////////////////////////////////// 
//												    		   15k     20k     25k
	//timetaken = Bubble_Sort(arr, SIZE);			    	//4.731,  8.358,  13.346
	//timetaken = Selection_Sort(arr, SIZE);	     		//0.311,  0.533,  0.857
	//timetaken = Insertion_Sort(arr, SIZE);	     		//0.168,  0.295,  0.469
	//timetaken = Merge_Sort(arr, 0, SIZE-1);    			//0.019,  0.026,  0.030
	//timetaken = Quick_Sort(arr, 0, SIZE-1);    			//0.013,  0.019,  0.023
	//timetaken = Shell_Sort(arr,SIZE);						//0.003,  0.005,  0.005
	//timetaken = T_Quick_Sort(arr, 0, SIZE-1);    			//
	timetaken = Bubble_Sort(arr, SIZE);

	cout << "took " << timetaken << " seconds\n";
	cout << "First 100 elements:\n";
	Sleep(1000);
	//print arrays first 100 index to be sure
	for (int i = 0; i < 100; i++)
		cout << arr[i] << '\n';
	
	free(arr);
	system("PAUSE");
	return 0;
}