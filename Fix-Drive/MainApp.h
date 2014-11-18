/*
|-------------------------------------------------------------------------------
| Name: MainApp.h
| Author: Imron Rosdiana
| Modified by: 2014-11-18
| Created: 2014-10-05
| Copyright: (C) Copyright 2014, Imron Rosdiana
| Licence: GPL (General Public License) V.3
*/

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