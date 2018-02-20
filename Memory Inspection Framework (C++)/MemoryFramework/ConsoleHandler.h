#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class ConsoleHandler {
public:
	ConsoleHandler(int nScreenWidth, int nScreenHeight);
	void drawPartialScreen(short startX, short startY, short endX, short endY);
	void drawScreen();
	void stringAtLocation(string S, short x, short y);
	void AttributeAtLocation(WORD Attribute, short startX, short startY, short endX, short endY);
	INPUT_RECORD* Inputs();
	HANDLE getHandle() { return hConsole; }

private:
	CHAR_INFO *m_screenChar;
	HANDLE hConsole;
	int m_nScreenWidth;
	int m_nScreenHeight;

};

ConsoleHandler::ConsoleHandler(int nScreenWidth, int nScreenHeight)
{
	m_screenChar = new CHAR_INFO[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++)
	{
		m_screenChar[i].Char.AsciiChar = ' ';
		m_screenChar[i].Attributes = BACKGROUND_BLUE | 0x07;
	}
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	m_nScreenHeight = nScreenHeight;
	m_nScreenWidth = nScreenWidth;
}

void ConsoleHandler::drawPartialScreen(short startX, short startY, short endX, short endY)
{
	SMALL_RECT rect = { startX,startY,endX,endY };
	WriteConsoleOutputA(hConsole, m_screenChar, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { startX,startY }, &rect);
}

void ConsoleHandler::drawScreen()
{
	SMALL_RECT rect = { 0,0,(short)m_nScreenWidth,(short)m_nScreenHeight };
	WriteConsoleOutputA(hConsole, m_screenChar, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &rect);
}

void ConsoleHandler::stringAtLocation(string S, short x, short y)
{
	for (unsigned i = 0; i<S.length(); ++i)
	{
		m_screenChar[y*m_nScreenWidth + x + i].Char.AsciiChar= S.at(i);
	}
	drawPartialScreen(x,y,x+S.length(),y);
}

void ConsoleHandler::AttributeAtLocation(WORD Attribute, short startX, short startY, short endX, short endY)
{
	for (unsigned i = startX; i <= endX; ++i)
		for (unsigned j = startY; j <= endY; ++j)
		{
			m_screenChar[j*m_nScreenWidth + i].Attributes = Attribute;
		}
	drawPartialScreen(startX, startY, endX, endY);
}
