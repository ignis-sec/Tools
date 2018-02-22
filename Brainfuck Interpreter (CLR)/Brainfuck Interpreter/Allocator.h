#pragma once
#include <vector>


class Allocator {
public:
	Allocator(){
		m_index = 1;
		m_maxUsed = 1;
		m_memory = new char[30];
		}
	int MemoryUp();		//>
	int MemoryDown();	//<
	int ValueUp();		//+
	int ValueDown();	//-
	int returnMax() { return m_maxUsed; }
	char getMemory(int index){
		return m_memory[index];
	}


protected:
	int m_maxUsed;
	char* m_memory;
	unsigned int m_index=0;

};

int Allocator::MemoryUp() { ///TODO check for max size of vector
	m_index++;
	if (m_index > m_maxUsed) m_maxUsed = m_index;
	return 0;
}
int Allocator::MemoryDown() {
	
	if (m_index > 0) {
		m_index--;
		return 0;
	}
	return 1;
}

int Allocator::ValueUp() {

	m_memory[m_index]++;
	return 0;
}
int Allocator::ValueDown() {
	if (m_memory[m_index] > 0) {
		m_memory[m_index]++;
		return 0;
	}
	return 1;
}