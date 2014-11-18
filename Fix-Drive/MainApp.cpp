/*
|-------------------------------------------------------------------------------
| Name: MainApp.cpp
| Author: Imron Rosdiana
| Modified by: 2014-11-18
| Created: 2014-10-05
| Copyright: (C) Copyright 2014, Imron Rosdiana
| Licence: GPL (General Public License) V.3
*/

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
