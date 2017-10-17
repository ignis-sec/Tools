#include <iostream>
#include <math.h>
#include <fstream>
#include "Main.h"
using namespace std;

void Encode(char  data[5], int b, std::ofstream &primefile);
void Decode();

int main(void)
{
	int maxNum;												//initialize variables
	bool *BinString;
	ofstream primefile;
	int c = 0;
	int i = 0;
	primefile.open("primes.dat");							//open encode file
		
	char data[5];

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
	for (unsigned int b = 2; b < maxNum; b++)
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
	cout << '\n';
	primefile.close();
	Decode();
	return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Encode(char  data[4], int b, std::ofstream &primefile)
{
	if (b < 256) data[0] = 1;
	else if (b < 65536) data[0] = 2;
	else if (b < 16777216) data[0] = 3;
	else data[0] = 4;
	data[1] = static_cast<unsigned char>(b & 0xFF);
	data[2] = static_cast<unsigned char>((b >> 8) & 0xFF);
	data[3] = static_cast<unsigned char>((b >> 16) & 0xFF);
	data[4] = static_cast<char>((b >> 24) & 0xFF);
	primefile.write(data, data[0]+1);
}

void Decode()
{
	cout << "Reading encoded file..\n\n\n";
	ifstream infile;
	infile.open("primes.dat");
	int i = 0;
	int decoded=0;
	char c = 0;
	int temp=1;
	bool bFirst = true;
	unsigned char data[4];
	while (infile.get(c))
	{
		if (i != 0 && data[0]>1)
		{
			if (i%data[0] == 0)
				for (int a = 0; a < data[0]; a++)
					decoded = decoded + data[a + 1] * pow(16, 2 * a);


		}
		else {
			data[0] = c;
			i++
		}
	
		
	}
	infile.close();
	cout << '\n';
	system("PAUSE");
	return ;
}
