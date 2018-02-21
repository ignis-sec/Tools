#include <iostream>
#include <string>
#include <Windows.h>

int main(int argc, char* argv[]) {
	char drive;
	std::string command = "manage-bde -lock ";
	const char* c_command;
	if(argc!=1)
		drive = argv[1][0];
	else 
	{
		std::cout << "Enter drive letter:";
		std::cin >> drive;
	}
	command.push_back(drive);
	command.push_back(':');
	command.append(" -ForceDismount");
	c_command = command.c_str();
	system(c_command);
	system("PAUSE");
	return 0;
}