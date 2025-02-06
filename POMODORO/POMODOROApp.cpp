/***************************************************************
 * Name:      POMODOROApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * Created:   2024-12-29
 * Copyright: Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * License:
 **************************************************************/

#include "POMODOROApp.h"

//(*AppHeaders
#include "POMODOROMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(POMODOROApp);

bool POMODOROApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	POMODORODialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
