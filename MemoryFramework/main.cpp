#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include "ConsoleHandler.h"
using namespace std;


void DrawMenu(ConsoleHandler Console,DWORD processID, string windowNameSTR);

int main()
{
	SetConsoleTitle(L"Memory Framework");
	string windowNameSTR;
	LPCSTR windowName;
	cout << "Enter window name:";
	cin >> windowNameSTR;
	windowName = windowNameSTR.c_str();
	ConsoleHandler Console(120, 30);
	HWND wHandle = FindWindowA(NULL, windowName);
	if (wHandle == NULL)
	{
		cout << "Cannot find window\n";
		return EXIT_FAILURE;
	}
	
	DWORD processID;
	GetWindowThreadProcessId(wHandle, &processID);
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	if (processID == NULL)
	{
		cout << "Cannot obtain process ID\n";
		return EXIT_FAILURE;
	}
	cout << "Found Process at process ID: " << processID << "\n";


	DrawMenu(Console, processID,windowNameSTR);



	return 0;
}

void DrawMenu(ConsoleHandler Console,DWORD processID, string windowNameSTR)
{
	char procID[10];
	sprintf(procID, "%d", processID);
	Console.drawScreen();
	Console.stringAtLocation("PROCESS NAME: ", 45, 1);
	Console.stringAtLocation(windowNameSTR, 59, 1);
	Console.stringAtLocation("PROCESS ID:", 47, 2);
	Console.stringAtLocation(procID, 55, 2);
	Console.stringAtLocation("Adress       Value", 3, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 3, 6, 21, 26);
	Console.stringAtLocation("Memory Value: ", 35, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 35, 6, 55, 6);
	Console.stringAtLocation("Memory Type: int(4)", 35, 5);
	




	Console.drawScreen();
	

	Sleep(15000);
}


