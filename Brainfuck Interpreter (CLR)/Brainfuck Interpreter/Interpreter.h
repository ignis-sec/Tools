#pragma once
#include <string>
#include <vector>
#include <sstream>

class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_loopBuffer = new char[15];
		m_InputBuffer = new char[25];
		m_codeBuffer = new char[25];
		m_InputArray = new int[25];
		m_outputBuffer = new char[25];
		m_outputBuffer = (char*)calloc(25, sizeof(char));
		memoryAllocator = Alloc;
		bForward = true;
		m_inputIndex = 0;
	
	}
	int fillInputBuffer(std::string* input);
	int allocateCodeBuffer(int size);
	int runtime(std::string *code);
	void condenseCode();
	void fillCodeBuffer(std::string *code);
	std::string* getOutput() { return &m_outputBuffer; }

	std::string m_outputBuffer;
protected:
	Allocator * memoryAllocator;
	bool bForward;
	char * m_codeBuffer;
	char *m_loopBuffer;
	char *m_InputBuffer;

	int *m_InputArray;
	int m_inputIndex;
	int m_inputMax;
};

int Interpreter::fillInputBuffer(std::string* input)
{
	const char* CInput = input->c_str();
	std::stringstream Istrm(CInput);
	strcpy(m_InputBuffer, CInput);
	int i=0;
	std::string segment;
	int intput;
	while (std::getline(Istrm, segment, ' '))
	{
		if(segment[0]>=48 && segment[0]<=57)
			intput = std::stoi(segment);
		else intput = segment[0];
		m_InputArray[i] = intput;
		i++;
	}
	m_inputMax = i;
	return 0;
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
			m_outputBuffer += std::to_string(memoryAllocator->getCurrentMemory());
			m_outputBuffer += " ";
			break;
		case ',':
			memoryAllocator->setMemory(m_InputArray[m_inputIndex]);
			m_inputIndex++;
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