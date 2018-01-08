#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include "ConsoleHandler.h"
using namespace std;


void DrawMenu(ConsoleHandler Console);

int main()
{
	SetConsoleTitle(L"Memory Framework");
	wstring windowNameSTR;
	LPCWSTR windowName;
	cout << "Enter window name:";
	wcin >> windowNameSTR;
	windowName = windowNameSTR.c_str();
	ConsoleHandler Console(120, 30);
	HWND wHandle = FindWindowW(NULL, windowName);
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


	DrawMenu(Console);



	return 0;
}

void DrawMenu(ConsoleHandler Console)
{
	Console.drawScreen();
	Console.stringAtLocation("Adress      Value", 3, 5);

	Sleep(3000);
}


