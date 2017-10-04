#include <string>																	//includes
#include <iostream>
#include <fstream>



using namespace std;																//namespace

int main(int argc, char* argv)
{
	string line;																	//variables
	string cardName;
	bool bCanStart=false;


	ofstream logfile;																//create log file for error debugging.
	cout << "Creating log file at errors.log...\n";
	logfile.open("errors.log");
	
	cout << "Extracting Driver Details to driver.txt...\n";							//get driver details to check hotspot validity.
	system("netsh wlan show drivers > driver.txt");
	
	ifstream driverDetails;															//read driver.txt
	driverDetails.open("driver.txt");
	if (!driverDetails) 
	{
		logfile << "Cannot open driver.txt, shutting down.";
		cout << "Cannot open driver.txt, shutting down.";
	}
	
	while (getline(driverDetails,line))												//search for  "Hosted network supported  : Yes"
	{
		if (line.compare("    Hosted network supported  : Yes") == 0) cout << "Mobile Hotspot is supported.Continuing with mobile hotspot.\n";
		if (line.find("Driver") == 1) 
		{ 
			line.substr(sizeof("Driver                    :")); 
			cardName.append(line); 
		}
		bool bCanStart = true;
	}
	cout << "Wireless card name:" << cardName <<'\n';

	return 0;
}

