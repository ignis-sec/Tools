#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include <vector>
#include <Psapi.h>
#include <thread>
#include "ConsoleHandler.h"
using namespace std;

struct s_cell
{
DWORD addr;
int Val;
};
typedef struct s_cell cell;

void DrawMenu(ConsoleHandler Console);
LPVOID GetBaseAddress();
cell* getAllMatchingValues(int val);
void printAllMatching(ConsoleHandler Console, cell* Matches);
void CheckAllMatchingAgain();
int StringToWString(std::wstring &ws, const std::string &s);
void HandleInputs();

HWND G_wHandle;
HANDLE G_pHandle;
DWORD G_processID;
string windowNameSTR;
wstring windowNameWSTR;
LPVOID G_EntryP;
ConsoleHandler* G_Console;
int G_nAddr=0;
cell* G_matching;
int G_shift=2;



int main()
{
SetConsoleTitle(L"Memory Framework");
LPCSTR windowName;
cout << "Enter window name:";
cin >> windowNameSTR;
windowName = windowNameSTR.c_str();
StringToWString(windowNameWSTR, windowNameSTR);

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




return 0;
}

void DrawMenu(ConsoleHandler Console)
{
	char procID[10];
	sprintf(procID, "%d", G_processID);
	Console.drawScreen();
	Console.stringAtLocation("Arrow Keys Scroll ", 0, 0);
	Console.stringAtLocation("PROCESS NAME: ", 45, 1);
	Console.stringAtLocation(windowNameSTR, 59, 1);
	Console.stringAtLocation("PROCESS ID:", 49, 2);
	Console.stringAtLocation(procID, 60, 2);
	Console.stringAtLocation("Adress       Value", 3, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0x00, 3, 6, 32, 25);
	Console.stringAtLocation("Memory Value: ", 35, 5);
	Console.AttributeAtLocation(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 35, 6, 55, 6);
	Console.stringAtLocation("Memory Type: int(4)", 35, 7);
	
	G_EntryP=GetBaseAddress();
	G_matching = getAllMatchingValues(1);
	printAllMatching(Console, G_matching);
	Console.drawScreen();
	while (TRUE)
	{
		thread keepBufferAlive(Sleep, 50);
		thread matchCheck(CheckAllMatchingAgain);
		keepBufferAlive.join();
		matchCheck.join();
		HandleInputs();

	}
}

void HandleInputs()
{
	bool bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
	bool bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;

	if (bKeyUp && G_shift>0)
	{
		G_shift--;
	}
	if (bKeyDown && G_shift<G_nAddr-20)
	{
		G_shift++;
	}

}


void CheckAllMatchingAgain()
{
int i;
char Addr[10];
char val[10];
SIZE_T garbage;
int* buffer;
buffer = (int*)malloc(sizeof(int));
for (i = 0; i <20; i++)
{
	
	ReadProcessMemory(G_pHandle, (LPVOID)G_matching[i+G_shift].addr, buffer, sizeof(int), &garbage);
	sprintf(val, "%d",  *buffer);
	sprintf(Addr, "%x", G_matching[i + G_shift].addr);

	G_Console->stringAtLocation(Addr, 3, 6 + i);
	G_Console->stringAtLocation(val, 17, 6 + i);
	if (G_matching[i+ G_shift].Val != *buffer)
	{
		G_Console->AttributeAtLocation(BACKGROUND_RED,3,6+i,32,6+i);
	}
		
}

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
			wstring wstrModContain = windowNameWSTR;
			if (wstrModName.find(wstrModContain) != string::npos)
			{
					
				GetModuleInformation(G_pHandle, hMods[i], &ModInf, bytesReq);
				break;
			}
		}
	}
}
G_Console->stringAtLocation("Process Entry Point: ", 75, 5);
char Addr[50];
sprintf(Addr, "%x", ModInf.EntryPoint);
G_Console->stringAtLocation(Addr, 97, 5);
return ModInf.EntryPoint;
}

cell* getAllMatchingValues(int val)
{
cell Matches[1024];
int* curAdd = (int *)G_EntryP;
int* buffer;
buffer = (int*)malloc(sizeof(int));
SIZE_T garbage;
int i=0;
	
while (i<100)
{
	ReadProcessMemory(G_pHandle, curAdd, buffer, sizeof(int), &garbage);
	if (*buffer == val)
	{
		Matches[i].addr = (DWORD)curAdd;
		Matches[i].Val = val;
		i++;
		G_nAddr++;
		//G_Console->stringAtLocation("TEST", 1, 1);
			
	}
curAdd++;
}
return Matches;
}

void printAllMatching(ConsoleHandler Console, cell* Matches)
{
int i=0;
char Addr[10];
char val[10];
for(i= 0;i<20;i++)
{
	sprintf(Addr, "%d", Matches[i+ G_shift]);
	sprintf(val, "%d",  Matches[i+ G_shift].Val);
	Console.stringAtLocation(Addr, 3, 6 + i);
	Console.stringAtLocation(val, 17, 6 + i);
}
}

int StringToWString(std::wstring &ws, const std::string &s)
{
std::wstring wsTmp(s.begin(), s.end());

ws = wsTmp;

return 0;
}
