#include "MainForm.h"
#include <iostream>
#include <opencv2/opencv.hpp>




using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void Main(array<String^>^args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	testForm_opencv::MainForm form;
	Application::Run(%form);
}

