#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#define MAX_BF_BUF 250
class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_InputBuffer = new char[MAX_BF_BUF];
		m_codeBuffer = new char[MAX_BF_BUF];
		m_InputArray = new int[MAX_BF_BUF];
		memoryAllocator = Alloc;
		bForward = true;
		m_inputIndex = 0;
		m_step = 0;
	
	}
	~Interpreter() { 
		free(m_loopBuffer);
		free(m_InputBuffer);
		free(m_codeBuffer);
		free(m_InputArray);
	}
	int fillInputBuffer(std::string* input);
	int allocateCodeBuffer(int size);
	int runtime(std::string *code);
	void condenseCode();
	void fillCodeBuffer(std::string *code);
	std::string* getOutput() { return &m_outputBuffer; }
	std::string* getStredOutput() { return &m_outputStringBuffer; }
	int runStep(std::string *code);
	void ExecuteCommand(char c, int i);


	void terminate() { delete this; }

	std::string m_outputBuffer;
	std::string m_outputStringBuffer;

protected:
	Allocator * memoryAllocator;
	bool bForward;
	char * m_codeBuffer;
	char *m_loopBuffer;
	char *m_InputBuffer;

	int m_step;
	int *m_InputArray;
	int m_inputIndex;
	int m_inputMax;
	
	std::stack<int> m_loopStack;
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
		ExecuteCommand(c,i);
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

int Interpreter::runStep(std::string *code) {

	fillCodeBuffer(code);
	condenseCode();
	char c = m_codeBuffer[m_step];
	ExecuteCommand(c,m_step);
	
	m_step++;
	return 0;
}

void Interpreter::ExecuteCommand(char c,int i) {
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
		m_loopStack.push(i);
		break;
	case ']':
		if (memoryAllocator->getCurrentMemory() != 0)
		{
			i = m_loopStack.top();
		}
		else m_loopStack.pop();
		break;
	case '.':
		m_outputBuffer += std::to_string(memoryAllocator->getCurrentMemory());
		m_outputBuffer += " ";
		m_outputStringBuffer += (char)memoryAllocator->getCurrentMemory();
		m_outputStringBuffer += " ";
		break;
	case ',':
		memoryAllocator->setMemory(m_InputArray[m_inputIndex]);
		m_inputIndex++;
		break;

	}
}