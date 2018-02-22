#include "Interpreter.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BrainfuckInterpreter::Interpreter form;
	Application::Run(%form);


}