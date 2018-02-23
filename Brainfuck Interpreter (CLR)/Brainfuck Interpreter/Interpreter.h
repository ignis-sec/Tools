#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#define MAX_BF_BUF 4096
class Interpreter {
public:
	Interpreter(Allocator *Alloc) {
		m_InputBuffer = new char[MAX_BF_BUF];
		m_codeBuffer = new char[MAX_BF_BUF];
		m_InputArray = new int[MAX_BF_BUF];
		memoryAllocator = Alloc;
		m_inputIndex = 0;
		m_step = 0;
	}
	~Interpreter() {
		free(m_InputBuffer);
		free(m_codeBuffer);
		free(m_InputArray);
	}
	int fillInputBuffer(std::string* input);//all of the functions are explained at the definition
	int runtime(std::string *code);
	void condenseCode();
	void fillCodeBuffer(std::string *code);
	std::string* getOutput() { return &m_outputBuffer; }
	std::string* getStredOutput() { return &m_outputStringBuffer; }
	int runStep(std::string *code);
	void ExecuteCommand(char c, int *i);
	void terminate() { delete this; }	//delet dis

	std::string m_outputBuffer;
	std::string m_outputStringBuffer;
protected:
	Allocator * memoryAllocator;//Allocator class is responsible of memory management.
	char * m_codeBuffer;		//this buffer keeps the code in textbox
	char *m_InputBuffer;		//this buffer keeps the inputs in textbox

	int m_step;					//used for debug mode. it is the current index in the 
	int *m_InputArray;			//this keeps the inputs from the textbox in int format
	int m_inputIndex;			//stores which input was used from stream
	bool m_skipFlag = false;	// if [ is read while data pointer is at 0, we have to skip the loop. This flag is turned to true
								//when situation mentioned above exists. interperation is stopped until a ] is found
	std::stack<int> m_loopStack;//used for nested loops
};

int Interpreter::fillInputBuffer(std::string* input)//this function fills the input buffer with textbox content
{
	const char* CInput = input->c_str();	//string conversions.
	std::stringstream Istrm(CInput);
	strcpy(m_InputBuffer, CInput);
	int i = 0;
	std::string segment;
	int intput;//aint no mistake in the name
	while (std::getline(Istrm, segment, ' '))	//this loop parses the input string into invidual integers. 0-9 are taken literally, while other
	{											//characters are converted to integers.
		if (segment[0] >= 48 && segment[0] <= 57)
			intput = std::stoi(segment);
		else intput = segment[0];
		m_InputArray[i] = intput;
		i++;
	}
	return 0;
}

void Interpreter::condenseCode() {				//this function porcalates anything that isnt a valid command key, (+-.,<>[])
	int index = 0;
	for (int i = 0; i < sizeof(m_codeBuffer); i++)
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
			m_codeBuffer[i] = ' ';			//first replace any useless character with whitespace
		}
		else index++;
	}
	for (int i = 0; i < sizeof(m_codeBuffer); i++)//then read through the array. if you find whitespace, move all contents forward 1 step back.
	{
		if (m_codeBuffer[i] == ' ')
		{
			for (int j = i; j < sizeof(m_codeBuffer) - 1; j++)
				m_codeBuffer[j] = m_codeBuffer[j + 1];
		}
	}

}

int Interpreter::runtime(std::string *code) {//main runtime frame
	fillCodeBuffer(code);
	//condenseCode();

	for (int i = 0; i < MAX_BF_BUF; i++) ///TODO dynamic code buffer size check
	{
		char c = m_codeBuffer[i];
		ExecuteCommand(c, &i);
	}

	return 0;
}

void Interpreter::fillCodeBuffer(std::string *code) {//this function fills the buffer with code from the textbox
	m_codeBuffer = new char[MAX_BF_BUF];
	for (int i = 0; i < code->size(); i++)
	{
		m_codeBuffer[i] = code->at(i);
	}
	m_codeBuffer[code->size()] = '\0';//append null terminator to the end

}

int Interpreter::runStep(std::string *code) {//executes only the current step

	fillCodeBuffer(code);
	condenseCode();

	char c = m_codeBuffer[m_step];
	ExecuteCommand(c, &m_step);

	m_step++;
	return 0;
}

void Interpreter::ExecuteCommand(char c, int *i) {

	if (!m_skipFlag)//use of this flag is explained at line 42
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
			if (memoryAllocator->getCurrentMemory() != 0)//if data pointer is not pointing to a 0 add this to the stack, if not skip until ]
				m_loopStack.push(*i);
			else m_skipFlag = true;
			break;
		case ']':
			if (memoryAllocator->getCurrentMemory() != 0)//if data pointer is not pointing to a 0 return to top of stack, if not continue
			{
				*i = m_loopStack.top();
			}
			else m_loopStack.pop(); //im not sure if this should be here
			break;
		case '.':
			m_outputBuffer += std::to_string(memoryAllocator->getCurrentMemory());//append output to output int buffer
			m_outputBuffer += " ";
			m_outputStringBuffer += memoryAllocator->getCurrentMemory();		  //append output to output char buffer
			m_outputStringBuffer += " ";
			break;
		case ',':
			memoryAllocator->setMemory(m_InputArray[m_inputIndex]);				//fill data pointers memory cell with current input
			m_inputIndex++;
			break;

		}
	else if (c == ']') m_skipFlag = false;	//if flag is true only check for ], if it is ] set flag to false, if not dont care
}