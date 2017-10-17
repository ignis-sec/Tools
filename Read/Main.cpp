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
	int decoded;
	char c = 0;
	unsigned char data[4];
	while (infile.get(c))
	{
		data[i % 4] = c;

		if (i % 4 == 0 && i > 4)
		{
			decoded = data[0] + data[1] * 256 + data[2] * 65536 + data[3] * 16777216;
			cout << decoded << ",\t";
			//cout << data[0] << data[1] << data[2] << data[3] << ",\t";
		}
		i++;
	}
	infile.close();
	cout << '\n';
	system("PAUSE");
	return 0;
}
