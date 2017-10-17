#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main(void)
{
	int maxNum;
	bool *BinString;
	ofstream primefile;
	int c = 0;

	primefile.open("primes.txt");
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
	for (int b = 2; b < maxNum; b++)
	{
		if (!(b % 1000000)) cout << b << " = " << b / 1000000 << "x 10^6 " << '\n';
		if (BinString[b] == 1)
		{
			c++;
			
			primefile << b << ", ";
		}
		for (int d = 2; d <= maxNum / b; d++)
		{
			BinString[b*d] = 0;
		}
	}
	return 0;
}