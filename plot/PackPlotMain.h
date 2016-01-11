/***************************************************************
 * Name:      dxfv_wxWidgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-06-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DXFV_WXWIDGETSMAIN_H
#define DXFV_WXWIDGETSMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PackPlotApp.h"
#include "mathplot.h"

class cBox
{
    public:
    int myWidth;
    int myHeight;
    int myLength;
    int WLoc;
    int HLoc;
    int LLoc;

    cBox( int w, int h, int l,
         int wl, int hl, int ll );

    mpPolygon * Ploygon();
};

class cFrame: public wxFrame
{
    public:
        cFrame(wxFrame *frame, const wxString& title);
        ~cFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };

        mpWindow * myPlot;
        std::vector< cBox > myBoxes;

        void LoadBoxes();

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // DXFV_WXWIDGETSMAIN_H
