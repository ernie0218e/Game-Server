// Server.cpp: ��Ҫ�����n��

#include "stdafx.h"
#include "Form1.h"

using namespace Server;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �����κο����֮ǰ���Ȇ��� Windows XP ҕ�X��Ч��
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ������ҕ���K����
	Application::Run(gcnew Form1());
	return 0;
}
