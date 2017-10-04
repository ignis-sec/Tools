//Ata Hakçýl
#include <string>																	//includes
#include <iostream>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////////////

void draw_Menu();																	//function templates


//////////////////////////////////////////////////////////////////////////////////////

using namespace std;																//namespace
//////////////////////////////////////////////////////////////////////////////////////
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
		return -1;
	}
	int linecount = 0;
	while (getline(driverDetails,line))												//search for  "Hosted network supported  : Yes"
	{																				//also check the wifi cards name
		if (line.compare("    Hosted network supported  : Yes") == 0)
		{
			cout << "Mobile Hotspot is supported. Continuing with mobile hotspot.\n";
			bCanStart = true;
		}

		linecount++;
		if (linecount == 4)
		{
			cardName.append(line);
		}
		
	}
	if (!bCanStart)																	//if cant start
	{
		cout << "Wireless card name:" << cardName << '\n';
		cout << "Wireless card is flagged as incompatible for hosted networks. Try Updating the drivers.\n";
		return -2;
	}

	draw_Menu();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
void draw_Menu()
{	
	fstream passwordfile;															//open file to read/write last used password and id to remember
	passwordfile.open(SSID_Password.txt);
	cout << "\n\n\n";
	cout << "                                                             \n";
	cout << "                                                             \n";
	cout << "                     (1) Start Hotspot                       \n";
	cout << "                     (2) Stop Hotspot                        \n";
	cout << "               (3) Change Name and Password                  \n";
	cout << "                                                             \n";
	cout << "                                                             \n";
	cout << "                                                             \n";
	cout << "                                                             \n";
	cout << "                                                             \n";
	char menu = getch();
	switch (menu)
	{
	case 1:
		
			
			break;
	case 2:
	
		break;
	case 3:

		break;
	}
}
