#include "MainApp.h"
#include "Frame.h"

bool MainApp::OnInit()
{
	MainFrame *mainFrame = new MainFrame(wxT("Fix Drive"));
	mainFrame->Show(true);
	mainFrame->SetStatusText(wxT("Welcome to fix drive application"));

	return true;
}

wxIMPLEMENT_APP(MainApp);
