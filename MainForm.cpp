#include "MainForm.h"

int main(array<System::String^>^ args)
{
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
    Forms::MainForm form;
    System::Windows::Forms::Application::Run(% form);
    return 0;
}
