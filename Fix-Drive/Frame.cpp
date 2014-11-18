/*
|-------------------------------------------------------------------------------
| Name: Frame.cpp
| Author: Imron Rosdiana
| Modified by: 2014-11-18
| Created: 2014-10-05
| Copyright: (C) Copyright 2014, Imron Rosdiana
| Licence: GPL (General Public License) V.3
*/

#include "Frame.h"

using namespace std;

/*
|-------------------------------------------------------------------------------
| This application is using for fix hidden file/folder after malware attack.
| MainFrame constructor is to initialize main of view applications
| such as menubar, button, and status bar.
*/

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(300, 200),
wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
	SetIcon(wxICON(aaaaa));
	CreateStatusBar();

	menuBar = new wxMenuBar;
	file = new wxMenu;
	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl-Q"));
	quit->SetBitmap(exit_xpm);
	file->Append(quit);

	about = new wxMenu;
	wxAbout = new wxMenuItem(about, wxID_ABOUT, wxT("&About\tF1"));
	wxAbout->SetBitmap(about_xpm);
	about->Append(wxAbout);

	appAbout = new wxMenuItem(about, MENU_AppAbout, wxT("&About Application\tCtrl-H"), 
							  wxT("Show about an application"));
	appAbout->SetBitmap(aboutApp_xpm);
	about->Append(appAbout);

	menuBar->Append(file, wxT("&File"));
	menuBar->Append(about, wxT("&Help"));
	SetMenuBar(menuBar);

	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);

	driveLabel = new wxStaticText(panel, wxID_ANY, wxT("Drive Letters: "), 
								  wxDefaultPosition, wxSize(80, -1));

	// Get All Drive Letter
	wxArrayString volumes = wxFSVolume::GetVolumes();

	driveBox = new wxComboBox(panel, wxID_ANY, volumes[0], wxDefaultPosition, 
							  wxDefaultSize, volumes, wxCB_READONLY);
	hbox1->Add(driveLabel, 0);
	hbox1->Add(driveBox, 1);
	vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	buttonOk = new wxButton(panel, BUTTON_Ok, wxT("Ok"));
	buttonQuit = new wxButton(panel, wxID_EXIT, wxT("Quit"));
	hbox2->Add(buttonOk, 0);
	hbox2->Add(buttonQuit, 1);
	vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxTOP | wxRIGHT, 10);

	panel->SetSizer(vbox);

	Centre();
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_MENU(MENU_AppAbout, MainFrame::OnAboutApp)
	EVT_BUTTON(wxID_EXIT, MainFrame::OnQuit)
	EVT_BUTTON(BUTTON_Ok, MainFrame::ProcessFix)
wxEND_EVENT_TABLE()

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close(true);
}

/*
|-------------------------------------------------------------------------------
| This function is a main command to fix drive letter after malware attack
| by using command attrib -s -h -a /s /d <drive letter>:\*.*.
| If drive letter is not detected, so the apps popup alert.
*/

void MainFrame::ProcessFix(wxCommandEvent& event)
{
	string drive = driveBox->GetValue();

	// attrib -s -h -a /s /d <drive letter>:\*.*

	try {
		wxExecute("attrib -s -h -a /s /d " + drive + "*.*", wxEXEC_HIDE_CONSOLE);
		wxMessageBox(wxT("Success."), wxT("Message"), wxOK | wxICON_INFORMATION);
	}
	catch (exception& e) {
		cout << "The process failed:" << e.what();
	}
}

/*
|-------------------------------------------------------------------------------
| This is about wxwidgets. Wxwidgets is library for create this apps
| This applications using wxwidgets version 3.0.2, more info you can read
| in here https://www.wxwidgets.org
*/

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxT("This application using wxWidgets\n(c) 1999-2001 Vadim Zeitlin"),
		wxT("About wxWidgets"),
		wxOK | wxICON_INFORMATION);
}

/*
|-------------------------------------------------------------------------------
| This is about applications. Applications is created by Imron Rosdiana.
| You can follow me on twitter @imronrosdiana, or my site at 
| http://www.imron02.wordpress.com.
*/

void MainFrame::OnAboutApp(wxCommandEvent& event)
{
	wxAboutDialogInfo info;

	info.SetName(wxT("About Application"));
	info.SetVersion(wxT("1.0.0"));
	info.SetDescription(wxT("This application can show hidding folder after malware attack"));
	info.SetCopyright(wxT("(C) 2014 Imron02 dev"));
	info.AddDeveloper(wxT("Imron Rosdiana"));
	info.SetWebSite(wxT("http://www.imron02.wordpress.com"), wxT("Imron Rosdiana Site"));

	wxAboutBox(info, this);
}

MainFrame::~MainFrame() {}