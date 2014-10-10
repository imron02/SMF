#ifndef FRAME_H
#define FRAME_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/frame.h>
	#include <wx/menu.h>
	#include <wx/msgdlg.h>
	#include <wx/process.h>
	#include <wx/sizer.h>
	#include <wx/combobox.h>
	#include <wx/stattext.h>
	#include <wx/button.h>
#endif

#include <string.h>
#include <iostream>
#include <wx/volume.h>
#include <wx/aboutdlg.h>
#include "./resources/exit.xpm"
#include "./resources/about.xpm"
#include "./resources/aboutApp.xpm"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	
	// Destructor
	virtual ~MainFrame();

private:
	wxMenuBar* menuBar;
	wxMenu* file;
	wxMenu* about;
	wxMenuItem* quit;
	wxMenuItem* wxAbout;
	wxMenuItem* appAbout;
	wxComboBox* driveBox;
	wxStaticText* driveLabel;
	wxButton* buttonOk;
	wxButton* buttonQuit;

private:
	void ProcessFix(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnAboutApp(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_Ok = wxID_HIGHEST + 1,
		MENU_AppAbout
	};
};

#endif // FRAME_H