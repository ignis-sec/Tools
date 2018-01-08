#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include <vector>
#include <Psapi.h>
#include "ConsoleHandler.h"
using namespace std;


void DrawMenu(ConsoleHandler Console);
LPVOID GetBaseAddress();
DWORD* getAllMatchingValues(int val);
void printAllMatching(ConsoleHandler Console, DWORD* Matches);

HWND G_wHandle;
HANDLE G_pHandle;
DWORD G_processID;
string windowNameSTR;
LPVOID G_EntryP;
ConsoleHandler* G_Console;

int main()
{
	SetConsoleTitle(L"Memory Framework");
	LPCSTR windowName;
	cout << "Enter window name:";
	cin >> windowNameSTR;
	windowName = windowNameSTR.c_str();
	ConsoleHandler Console(120, 30);
	G_Console = &Console;
	G_wHandle = FindWindowA(NULL, windowName);
	if (G_wHandle == NULL)
	{
		cout << "Cannot find window\n";
		return EXIT_FAILURE;
	}
	
	G_processID;
	GetWindowThreadProcessId(G_wHandle, &G_processID);
	G_pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, G_processID);

	if (G_processID == NULL)
	{
		cout << "Cannot obtain process ID\n";
		return EXIT_FAILURE;
	}
	cout << "Found Process at process ID: " << G_processID << "\n";


	DrawMenu(Console);
	while (1)
	{
		Console.drawScreen();
		Sleep(30);
	}


	return 0;
}

void DrawMenu(ConsoleHandler Console)
{
	char procID[10];
	sprintf(procID, "%d", G_processID);
	Console.drawScreen();
	Console.stringAtLocation("PROCESS NAME: ", 45, 1);
	Console.stringAtLocation(windowNameSTR, 59, 1);
	Console.stringAtLocation("PROCESS ID:", 49, 2);
	Console.stringAtLocation(procID, 60, 2);
	Console.stringAtLocation("Adress       Value", 3, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 3, 6, 21, 26);
	Console.stringAtLocation("Memory Value: ", 35, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 35, 6, 55, 6);
	Console.stringAtLocation("Memory Type: int(4)", 35, 7);
	
	LPVOID G_EntryP=GetBaseAddress();
	DWORD* matching = getAllMatchingValues(0);
	printAllMatching(Console, matching);



	Console.drawScreen();
	
}


LPVOID GetBaseAddress()
{
	LPTSTR Image;
	Image = (LPTSTR)malloc(50);
	HMODULE hMods[1024];
	GetProcessImageFileName(G_pHandle, Image, 50);
	DWORD bytesReq=0;
	MODULEINFO ModInf;

	if (EnumProcessModules(G_pHandle, hMods, sizeof(hMods), &bytesReq))	//get module info from image
	{
		for (int i = 0; i < (bytesReq / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(G_pHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				wstring wstrModName = szModName;
				//you will need to change this to the name of the exe of the foreign process
				wstring wstrModContain = L"ControlCenter";
				if (wstrModName.find(wstrModContain) != string::npos)
				{
					
					GetModuleInformation(G_pHandle, hMods[i], &ModInf, bytesReq);
					break;
				}
			}
		}
	}
	
	return ModInf.EntryPoint;
}

DWORD* getAllMatchingValues(int val)
{
	DWORD Matches[1024];
	LPVOID curAdd = G_EntryP;
	LPVOID buffer[4];
	SIZE_T garbage;
	int i=0;
	for (;;)
	{
		ReadProcessMemory(G_pHandle, curAdd, buffer, sizeof(int), &garbage);
		if ((int)buffer == val)
		{
			Matches[i] = (DWORD)curAdd;
			curAdd = &curAdd+4;
			G_Console->stringAtLocation("TEST", 1, 1);
			i++;
		}
	}
	return Matches;
}

void printAllMatching(ConsoleHandler Console, DWORD* Matches)
{
	int i=0;
	char Addr[10];
	while (Matches[i] != NULL)
	{
		sprintf(Addr, "%d", Matches[i]);
		Console.stringAtLocation(Addr, 3, 6 + i);
	}
}
