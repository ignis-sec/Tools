#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	cout << "Reading encoded file..\n\n\n";
	ifstream infile;
	infile.open("primes.dat");
	int i = 0;
	int decoded;
	char c = 0;
	char data[4];
	while (infile.get(c))
	{
		data[i%4] = c;
		
		if (i % 4 == 0 && i > 4)
		{
			decoded = data[0] + data[1] * 16 * 16 + data[2] * 16 * 16 * 16 * 16 + data[3] * 16 * 16 * 16 * 16 * 16 * 16;
			cout << decoded << ",\t";
		}
		i++;
	}
	infile.close();
	cout << '\n';
	system("PAUSE");
	return 0;
}