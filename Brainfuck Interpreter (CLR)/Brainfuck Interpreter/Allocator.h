#pragma once

#define MAX_MEM_BUF 4096

class Allocator {
public:
	Allocator(){
		m_dataPointerIndex = 0;
		m_maxUsed = 0;
		m_memory = new char[MAX_MEM_BUF];
		m_memory = (char*)calloc(MAX_MEM_BUF, sizeof(char));
		}
	~Allocator() {
		free(m_memory);
	}

	int MemoryUp();				//>
	int MemoryDown();			//<
	int ValueUp();				//+
	int ValueDown();			//-
	int setMemory(int input);	//,
	char getCurrentMemory();	//.

	char getMemory(int index){	//used for printing memory to the textbox
		return m_memory[index];
	}

	int returnMax() { return m_maxUsed; }
	void terminate() { delete this; }

protected:
	int m_maxUsed;
	char* m_memory;
	unsigned int m_dataPointerIndex=0;
};

int Allocator::MemoryUp() {//>
	m_dataPointerIndex++;
	if (m_dataPointerIndex > m_maxUsed) m_maxUsed = m_dataPointerIndex;
	return 0;
}
int Allocator::MemoryDown() {//<
	
	if (m_dataPointerIndex > 0) {
		m_dataPointerIndex--;
		return 0;
	}
	return 1;
}

int Allocator::ValueUp() {//+

	m_memory[m_dataPointerIndex]++;
	return 0;
}
int Allocator::ValueDown() {//-
	if (m_memory[m_dataPointerIndex] > 0) {
		m_memory[m_dataPointerIndex]--;
		return 0;
	}
	return 1;
}

int Allocator::setMemory(int input)//,
{
	if (input == -842150451) m_memory[m_dataPointerIndex] = 0;//program returns -51 if there isnt an input
	else m_memory[m_dataPointerIndex] = input;
	return 0;
}

char Allocator::getCurrentMemory()//.
{
	return m_memory[m_dataPointerIndex];
}