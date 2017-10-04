//Ata Hakçýl
#include <string>																	//includes and preproccessors
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>

#define SELECTED 11
#define OTHER 2

//////////////////////////////////////////////////////////////////////////////////////

bool draw_Menu();																	//function templates
void SetColor(int ForgC);
void Menu_Colors(int hover);
void submit_menu(int menu);

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
	Sleep(1000);
	draw_Menu();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
bool draw_Menu()
{	
	int menu = 50;
	int lastMenu = 50;
	system("cls");																	//initialize first menu
	Menu_Colors('2');
	for (int i=0;;i++)
	{
		menu = _getch();

		if (menu == 80&&((lastMenu == 49) || (lastMenu == 50))) menu=lastMenu+1; if (menu == 72&&((lastMenu == 50) || (lastMenu == 51))) menu = lastMenu - 1;							//arrow keys
		if (menu < 55) lastMenu = menu; else menu = lastMenu;
		system("cls");
		if (menu == 13)
		{
			submit_menu(lastMenu);														//submit last menu item
		}else Menu_Colors(menu);
	}

}

//////////////////////////////////////////////////////////////////////////////////////

void SetColor(int ForgC)													//change text color
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

//////////////////////////////////////////////////////////////////////////////////////

void Menu_Colors(int hover)
{
	switch (hover)
	{
	case '1':
	case 48:
		SetColor(OTHER);
		cout << "\n\n\n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		SetColor(SELECTED);
		cout << "                     (1) Start Hotspot                       \n";
		SetColor(OTHER);
		cout << "                     (2) Stop Hotspot                        \n";
		cout << "               (3) Change Name and Password                  \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		break;
	case '2':
		SetColor(OTHER);
		cout << "\n\n\n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                     (1) Start Hotspot                       \n";
		SetColor(SELECTED);
		cout << "                     (2) Stop Hotspot                        \n";
		SetColor(OTHER);
		cout << "               (3) Change Name and Password                  \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		break;
	case '3':
	case 52:
		SetColor(OTHER);
		cout << "\n\n\n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                     (1) Start Hotspot                       \n";
		cout << "                     (2) Stop Hotspot                        \n";
		SetColor(SELECTED);
		cout << "               (3) Change Name and Password                  \n";
		SetColor(OTHER);
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		cout << "                                                             \n";
		break;
	}	
}

void submit_menu(int menu)
{
	fstream passwordfile;															//open file to read/write last used password and id to remember
	passwordfile.open("SSID_Password.txt");

	case (menu)
}