/***************************************************************
 * Name:      dxfv_wxWidgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2014-06-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "PackPlotApp.h"
#include "PackPlotMain.h"

IMPLEMENT_APP(dxfv_wxWidgetsApp);

bool dxfv_wxWidgetsApp::OnInit()
{
    cFrame* frame = new cFrame(0L, _("Pack Plot"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
