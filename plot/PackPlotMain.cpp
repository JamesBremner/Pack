#include <fstream>

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif



#include "PackPlotMain.h"



cBox::cBox( int w, int h, int l,
            int wl, int hl, int ll )
    : myWidth( w )
    , myHeight( h )
    , myLength( l )
    , WLoc( wl )
    , HLoc( hl )
    , LLoc( ll )
{

}
mpPolygon * cBox::Ploygon()
{
    mpPolygon * poly = new mpPolygon();
    std::vector< double > x { 0, myLength, myLength, 0 };
    std::vector< double > y { 0, 0, myWidth, myWidth };

    poly->setPoints( x, y );
    if( HLoc == 0 )
        poly->SetPen( wxPen(*wxBLACK, 3, wxSOLID) );
    else
        poly->SetPen( wxPen(*wxRED, 1, wxSOLID) );

    poly->SetCoordinateBase(LLoc,WLoc);
    return poly;

}

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(cFrame, wxFrame)
    EVT_CLOSE(cFrame::OnClose)
    EVT_MENU(idMenuQuit, cFrame::OnQuit)
    EVT_MENU(idMenuAbout, cFrame::OnAbout)
END_EVENT_TABLE()

cFrame::cFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

    LoadBoxes();

    myPlot = new mpWindow( this, -1,
                           wxPoint(0,0),
                           wxSize(200,200),
                           wxSUNKEN_BORDER );
    myPlot->LockAspect();

    for( auto& b : myBoxes )
    {
            myPlot->AddLayer( b.Ploygon() );
    }

    myPlot->EnableDoubleBuffer(true);
    myPlot->Fit();

}


cFrame::~cFrame()
{
}

void cFrame::LoadBoxes()
{
    std::string line;
    std::ifstream csv( "packit4me2.csv" );
    while ( std::getline( csv, line ).good() )
    {
        int w, h, l;
        char * c = (char*)line.c_str();
        w = atoi( c );
        while ( *c != ',')
            c++;
        c++;
        h = atoi( c );
        while ( *c != ',')
            c++;
        c++;
        l = atoi( c );

        int lw, lh, ll;
        while ( *c != ',')
            c++;
        c++;
        lw = atoi( c );
        while ( *c != ',')
            c++;
        c++;
        lh = atoi( c );
        while ( *c != ',')
            c++;
        c++;
        ll = atoi( c );

        myBoxes.push_back( cBox( w, h, l, lw, lh, ll ) );
    }
}

void cFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void cFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void cFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
