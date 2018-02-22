#pragma once
#include <string>
#include <vector>


class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_loopBuffer = new char[150];
		m_InputBuffer = new char[250];
		m_codeArr = new char[250];
		memAllocator = Alloc;
	}
	int fillInputBuffer(char* input);
	int allocateCodeBuffer(int size);
	int runtime(std::string code);
	void condenseCode();
	void fillCodeBuffer(std::string);
protected:
	Allocator * memAllocator;
	std::vector<char> m_codeBuffer;
	char * m_codeArr;
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
	for (auto &c : m_codeBuffer)
	{
		if (c != '+' ||
			c != '-' ||
			c != '>' ||
			c != '<' ||
			c != '[' ||
			c != ']' ||
			c != '.' ||
			c != ',') {
			m_codeBuffer.erase(m_codeBuffer.begin() + index);
		}else index++;	
	}

}

int Interpreter::runtime(std::string code) {
	fillCodeBuffer(code);
	condenseCode();

	for (auto c : m_codeBuffer)
	{
		switch (c)
		{
		case '+':
			memAllocator->ValueUp();
			break;
		case '-':
			memAllocator->ValueDown();
			break;
		case '<':
			memAllocator->MemoryUp();
			break;
		case '>':
			memAllocator->MemoryDown();
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
	*/
	return 0;
}

void Interpreter::fillCodeBuffer(std::string code) {
	m_codeBuffer.clear();
	strcpy(m_codeArr, code.c_str());
	for (auto &c : code)
	{
		m_codeBuffer.push_back(c);
	}

}