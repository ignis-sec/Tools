#pragma once
#include <string>
#include <vector>


class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_loopBuffer = new char[15];
		m_InputBuffer = new char[25];
		m_codeBuffer = new char[25];
		memoryAllocator = Alloc;
	}
	int fillInputBuffer(char* input);
	int allocateCodeBuffer(int size);
	int runtime(std::string *code);
	void condenseCode();
	void fillCodeBuffer(std::string *code);
protected:
	Allocator * memoryAllocator;

	char * m_codeBuffer;
	char *m_loopBuffer;
	char *m_InputBuffer;
};

int Interpreter::fillInputBuffer(char* input)
{
	if (sizeof(input) <= 250) {
		strcpy(m_InputBuffer, input);
		return 0;
	}
	else return 1;
}

int Interpreter::allocateCodeBuffer(int size) {
	if (size <= 0) return 1;
}

void Interpreter::condenseCode() {
	int index = 0;
	for (int i=0;i<sizeof(m_codeBuffer);i++)
	{
		char c = m_codeBuffer[i];
		if (c != '+' &&
			c != '-' &&
			c != '>' &&
			c != '<' &&
			c != '[' &&
			c != ']' &&
			c != '.' &&
			c != ',') {
			m_codeBuffer[i] = ' ';
		}else index++;	
	}
	for (int i = 0; i < sizeof(m_codeBuffer); i++)
	{
		if (m_codeBuffer[i] == ' ')
		{
			for (int j = i; j < sizeof(m_codeBuffer) - 1; j++)
				m_codeBuffer[j] = m_codeBuffer[j + 1];
		}
	}

}

int Interpreter::runtime(std::string *code) {
	fillCodeBuffer(code);
	condenseCode();

	for (int i = 0; i<150; i++) ///TODO dynamic code buffer size check
	{
		char c = m_codeBuffer[i];
		switch (c)
		{
		case '+':
			memoryAllocator->ValueUp();
			break;
		case '-':
			memoryAllocator->ValueDown();
			break;
		case '<':
			memoryAllocator->MemoryDown();
			break;
		case '>':
			memoryAllocator->MemoryUp();
			break;
		case '[':

			break;
		case ']':

			break;
		case '.':

			break;
		case ',':

			break;

		}
	}
	
	return 0;
}

void Interpreter::fillCodeBuffer(std::string *code) {
	m_codeBuffer = new char[250];
	//strcpy(m_codeArr, code->c_str());
	for (int i=0;i<code->size();i++)
	{
		m_codeBuffer[i] = code->at(i);
	}
	m_codeBuffer[code->size()] = '\0';

}