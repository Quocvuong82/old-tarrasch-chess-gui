/****************************************************************************
 * Control - A coloured rectangular box, subclass for user interaction
 *           This is an alternative implementation to CtrlBox2
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#ifndef CTRL_BOX2_H
#define CTRL_BOX2_H
#include "wx/wx.h"
#include "wx/textctrl.h"
//#include "wx/richtext/richtextctrl.h"

class CtrlBox2 : public wxTextCtrl
{
    DECLARE_CLASS( CtrlBox2 )
    DECLARE_EVENT_TABLE()

public:
	// Constructor
	CtrlBox2( wxWindow *parent,
             wxWindowID id,
             const wxPoint& point,
             const wxSize& size,
             long  style=wxBORDER_SIMPLE );

    // Write txt
    void SetTxt( const wxString &txt, bool redraw=true );

private:
    wxString txt;
    void OnMouseLeftDown( wxMouseEvent & event );
    void OnSetCursor( wxSetCursorEvent & event );

public:
    bool     hack_its_a_clock;
    wxRect   r;
    //void OnPaint(wxPaintEvent& WXUNUSED(evt));
    void OnEraseBackGround(wxEraseEvent& WXUNUSED(event) ) {};
};

#endif  // CTRL_BOX2
