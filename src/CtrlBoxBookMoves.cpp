/****************************************************************************
 * Control - A CtrlBox, subclassed for book moves user interaction
 *  (i.e. the green book moves box under the move list)
 *  Author:  Bill Forster
 *  Licence: See licencing information in ChessPosition.cpp
 *  Copyright 2010, Triple Happy Ltd.  All rights reserved.
 ****************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "wx/wx.h"
#include "Objects.h"
#include "GameLogic.h"
#include "DebugPrintf.h"
#include "CtrlBoxBookMoves.h"

//temp
extern bool view_flags_book_moves;

IMPLEMENT_CLASS( CtrlBoxBookMoves, CtrlBox2 )
BEGIN_EVENT_TABLE( CtrlBoxBookMoves, CtrlBox2 )
    EVT_MOTION (CtrlBoxBookMoves::OnMouseMove)
END_EVENT_TABLE()

// Initialise the box
CtrlBoxBookMoves::CtrlBoxBookMoves
(
    wxWindow *parent,
    wxWindowID id,
    const wxPoint& point,
    const wxSize& size
)   : CtrlBox2 ( parent, id, point, size, wxBORDER_SIMPLE )
{
}

//CtrlBoxBookMoves::~CtrlBoxBookMoves()
//{
//}

void CtrlBoxBookMoves::OnMouseMove( wxMouseEvent &event )
{
    wxPoint point = event.GetPosition();
    //todo only if book moves
    if( view_flags_book_moves )
    {
        DebugPrintf(( "Book move point.x=%d, point.y=%d\n", point.x, point.y ));
        objs.gl->BookHover( point );
    }
}
