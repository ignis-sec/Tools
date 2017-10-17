#include <iostream>
#include <math.h>
#include <fstream>
#include "Main.h"
using namespace std;

void Encode(char  data[4], int b, std::ofstream &primefile);


int main(void)
{
	int maxNum;												//initialize variables
	bool *BinString;
	ofstream primefile;
	int c = 0;
	int i = 0;
	primefile.open("primes.dat");							//open encode file
		
	char data[4];

															//get max number
	cout << "Enter largest number to check:";
	cin >> maxNum;

															//malloc binary string
	BinString = (bool*)malloc(maxNum);

															//initialize the binary string
	BinString[0] = 0;
	BinString[1] = 0;
	for (int a = 2; a <= maxNum; a++)
	{
		BinString[a] = 1;
		
	}

															//loop and remove logic
	for (int b = 2; b < maxNum; b++)
	{
		if (!(b % 1000000)) cout << b << " = " << b / 1000000 << "x 10^6 " << '\n';
		if (BinString[b] == 1)
		{
			c++;
			
			Encode(data, b, primefile);
		}
		for (int d = 2; d <= maxNum / b; d++)
		{
			BinString[b*d] = 0;
		}
	}
	if (!(maxNum % 1000000)) cout << maxNum << " = " << maxNum / 1000000 << "x 10^6 " << '\n';		//report position
	return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Encode(char  data[4], int b, std::ofstream &primefile)
{
	data[0] = static_cast<char>(b & 0xFF);
	data[1] = static_cast<char>((b >> 8) & 0xFF);
	data[2] = static_cast<char>((b >> 16) & 0xFF);
	data[3] = static_cast<char>((b >> 24) & 0xFF);
	primefile.write(data, 4);
}
