#include <iostream>
#include <math.h>

using namespace std;

int main(void)
{
	int maxNum;
	bool *BinString;

	//get max number
	cout << "Enter largest number to check:";
	cin >> maxNum;


	//malloc binary string
	BinString = (bool*)malloc(maxNum);


	//initialize
	BinString[0] = 0;
	BinString[1] = 0;
	for (int a = 2; a <= maxNum; a++)
	{
		BinString[a] = 1;

	}

	//loop and remove








	return 0;
}