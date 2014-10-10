#ifndef MAINAPP_H
#define MAINAPP_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/app.h>
#endif

class MainApp: public wxApp
{
public:
	virtual bool OnInit();
};

#endif // MAINAPP_H