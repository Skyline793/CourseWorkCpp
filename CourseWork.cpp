#include "SeaBattle.h"
#include <Windows.h>

using namespace CourseWork;
[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew SeaBattle);
	return 0;
}