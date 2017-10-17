#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(void)
{
	cout << "Reading encoded file..\n\n\n";
	ifstream infile;
	infile.open("primes.dat");
	int i = 0;
	int decoded = 0;
	char c = 0;
	unsigned char data[5];
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	//infile.seekg(1, infile.beg);
	while (infile.good())
	{
		infile.get(c);
		if (data[0] == i - 1)
		{
			decoded = data[1] + data[2] * 256 + data[3] * 65536 + data[4] * 16777216;

			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			data[4] = 0;
			cout << decoded << ",\t";
			data[0] = c;
			i = 1;
		}
		else {
			data[i] = c;
			i++;
		}

	}
	decoded = data[1] + data[2] * 256 + data[3] * 65536 + data[4] * 16777216;
	cout << decoded;
	infile.close();
	cout << '\n';
	system("PAUSE");
	return 0;
}
