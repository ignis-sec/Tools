#pragma once
#include <vector>


class Allocator {
public:
	Allocator() {
		m_memory.push_back(0);
		m_index = 0;
		}
	int MemoryUp();		//>
	int MemoryDown();	//<
	int ValueUp();		//+
	int ValueDown();	//-
	


protected:
	std::vector<char> m_memory;
	unsigned int m_index;

};

int Allocator::MemoryUp() { ///TODO check for max size of vector
	m_index++;
	if (m_index >= m_memory.size())
	{
		m_memory.push_back(0);
	}
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

	m_memory.at(m_index)++;
	return 0;
}
int Allocator::ValueDown() {
	if (m_memory.at(m_index) > 0) {
		m_memory.at(m_index)--;
		return 0;
	}
	return 1;
}