#include <string>																	//includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;																//namespace

int main(int argc, char* argv)
{
	ofstream logfile;																//create log file for error debugging.
	cout << "Creating log file at errors.log...\n";
	logfile.open("errors.log");
	
	cout << "Extracting Driver Details to driver.cfg...\n";							//get driver details to check hotspot validity.
	system("netsh wlan show drivers > driver.cfg");
	
	ofstream driverDetails;															//read driver.txt
	driverDetails.open("driver.cfg");
	if (!driverDetails) 
	{
		logfile.write("Cannot open driver.cfg");
		cout << "Cannot open driver.cfg, shutting down.";
	}
	
/*
	string line;																	//search for  "Hosted network supported  : Yes"
	unsigned int curLine = 0;
	while (istream::getline(driverDetails,line)) { 
		curLine++;
		if (line.find(search, 0) != string::npos) {
			cout << "found: " << search << "line: " << curLine << endl;
		}
	}
	*/

	return 0;
}

