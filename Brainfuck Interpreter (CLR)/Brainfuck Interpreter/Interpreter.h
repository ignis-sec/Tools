#pragma once
#include <string>
#include <vector>


class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_loopBuffer = new char[150];
		m_InputBuffer = new char[250];
	}
	int fillInputBuffer(char* input);
	int allocateCodeBuffer(int size);
	int runtime();
	void condenseCode();
	void fillCodeBuffer(std::string);
protected:
	std::vector<char> m_codeBuffer;
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

int Interpreter::runtime() {
	condenseCode();

	
	return 0;
}

void Interpreter::fillCodeBuffer(std::string code) {
	for (auto &c : code)
	{
		m_codeBuffer.push_back(c);
	}

}