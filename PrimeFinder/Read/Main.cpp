#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

int main(void)
{
	cout << "Reading encoded file..\n\n\n";
	ifstream infile;
	infile.open("primes.dat", ios::binary);
	int i = 0;
	int decoded = 0;
	char c = 0;
	unsigned char data[5];
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	while (1)
	{
		infile.read(&c, 1);
		if (data[0] == 26)
		{
			decoded = data[1] + data[2] * 256 + data[3] * 65536 + data[4] * 16777216;
			cout << '\n';
			system("PAUSE");
			return 0;
		}
		if (data[0] == i - 1)
		{
			decoded = (int)data[1] + (int)data[2] * 256 + (int)data[3] * 65536 + (int)data[4] * 16777216;
			data[0] = c;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			data[4] = 0;
			cout << decoded << ",\t";

			i = 1;
		}
		else {
			data[i] = c;
			i++;

		}

	}

	cout << decoded;
	infile.close();
	cout << '\n';

	Sleep(10000);
	return 0;
}
